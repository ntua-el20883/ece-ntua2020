
          
          
exception Break

(* Define a simple queue structure *)
structure Queue = struct
    type 'a queue = 'a list ref * 'a list ref
    fun newQueue () = (ref [], ref [])
    fun enqueue ((front, back), x) = back := x :: !back
    fun dequeue (q as (front, back)) =
        case !front of
             [] => (case rev (!back) of
                         [] => raise Empty
                       | x::xs => (front := xs; back := []; x))
           | x::xs => (front := xs; x)
    fun isEmpty (front, back) = null (!front) andalso null (!back)
end

(* Directions in order of (N, S, W, E, NE, NW, SE, SW) *)
val dRow = [~1, 1, 0, 0, ~1, ~1, 1, 1]
val dCol = [0, 0, ~1, 1, 1, ~1, 1, ~1]
val directionNames = ["N", "S", "W", "E", "NE", "NW", "SE", "SW"]

fun moves filePath =
    let
        (* Read the file and parse the grid *)
        val fileContent = TextIO.inputAll (TextIO.openIn filePath)
        val lines = String.tokens (fn c => c = #"\n") fileContent
        val N = valOf (Int.fromString (hd lines))
        val grid = map (fn line => map (fn x => valOf (Int.fromString x)) (String.tokens (fn c => c = #" ") line)) (tl lines)
        
        (* Initialize BFS variables *)
        val visited = Array.tabulate (N, fn _ => Array.array (N, false))
        val prevRow = Array.tabulate (N, fn _ => Array.array (N, ~1))
        val prevCol = Array.tabulate (N, fn _ => Array.array (N, ~1))
        
        (* Check if coordinates are within bounds *)
        fun isInBounds (row, col) = row >= 0 andalso row < N andalso col >= 0 andalso col < N
        
        (* Reconstruct the path from the BFS results *)
        fun reconstructPath (endRow, endCol) =
            let
                fun loop (row, col, path) =
                    if row = 0 andalso col = 0 then
                        path
                    else
                        let
                            val prevRowIdx = Array.sub (Array.sub (prevRow, row), col)
                            val prevColIdx = Array.sub (Array.sub (prevCol, row), col)
                            val direction = List.find (fn d => row = prevRowIdx + List.nth (dRow, d) andalso col = prevColIdx + List.nth (dCol, d)) (List.tabulate (8, fn x => x))
                            val path = List.nth (directionNames, valOf direction) :: path
                        in
                            loop (prevRowIdx, prevColIdx, path)
                        end
            in
                "[" ^ String.concatWith "," (loop (endRow, endCol, [])) ^ "]"
            end

        (* BFS implementation *)
        fun bfs () =
            let
                val queue = Queue.newQueue ()
                val _ = Queue.enqueue (queue, (0, 0))
                val _ = Array.update (Array.sub (visited, 0), 0, true)
                
                fun bfsLoop () =
                    if Queue.isEmpty queue then
                        "IMPOSSIBLE"
                    else
                        let
                            val (curRow, curCol) = Queue.dequeue queue
                            
                            (* If we reach the bottom-right corner, reconstruct the path *)
                            val _ = if curRow = N - 1 andalso curCol = N - 1 then
                                        raise Break
                                    else
                                        ()
                            
                            fun tryDirection d =
                                let
                                    val newRow = curRow + List.nth (dRow, d)
                                    val newCol = curCol + List.nth (dCol, d)
                                in
                                    if isInBounds (newRow, newCol) andalso not (Array.sub (Array.sub (visited, newRow), newCol)) andalso List.nth (List.nth (grid, newRow), newCol) < List.nth (List.nth (grid, curRow), curCol) then
                                        let
                                            val _ = Queue.enqueue (queue, (newRow, newCol))
                                            val _ = Array.update (Array.sub (visited, newRow), newCol, true)
                                            val _ = Array.update (Array.sub (prevRow, newRow), newCol, curRow)
                                            val _ = Array.update (Array.sub (prevCol, newRow), newCol, curCol)
                                        in
                                            ()
                                        end
                                    else
                                        ()
                                end
                            val _ = app tryDirection (List.tabulate (8, fn x => x))
                        in
                            bfsLoop ()
                        end
            in
                (* Handle edge case where no path exists *)
                (bfsLoop () handle Break => reconstructPath (N - 1, N - 1))
            end

    in
        print (bfs () ^ "\n")
    end
                