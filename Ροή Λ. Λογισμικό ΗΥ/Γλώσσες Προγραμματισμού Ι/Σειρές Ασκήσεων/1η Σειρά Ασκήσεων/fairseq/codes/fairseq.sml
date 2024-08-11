(* Import necessary libraries *)
structure TextIO = TextIO
structure List = List

(* Function to calculate the minimal difference using dynamic programming *)
fun minimalDifference numbers =
    let
        val totalSum = foldl op+ 0 numbers
        val halfSum = totalSum div 2
        val dp = Array.array (halfSum + 1, false)
        val _ = Array.update (dp, 0, true)  (* Zero sum is always possible *)

        fun updateDp num =
            let
                fun go j =
                    if j >= num then
                        (if Array.sub (dp, j - num) then
                            Array.update (dp, j, true)
                         else ();
                         go (j - 1))
                    else ()
            in
                go halfSum
            end

        val _ = List.app updateDp numbers

        fun findBestX i bestX =
            if i > halfSum then bestX
            else if Array.sub (dp, i) then findBestX (i + 1) i
                 else findBestX (i + 1) bestX

        val bestX = findBestX 0 0
    in
        abs (2 * bestX - totalSum)
    end


(* Function to read data from a file, compute the minimal difference, and print the result *)
fun fairseq (filename : string) =
    let
        val inFile = TextIO.openIn filename
        val N = Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) inFile)
        val numbers = List.tabulate (N, fn _ => Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) inFile))
        val _ = TextIO.closeIn inFile
        val result = minimalDifference numbers
    in
        print (Int.toString result ^ "\n")
    end

(* Function to read data from file and compute result *)
fun main (filename : string) =
    let
        val inFile = TextIO.openIn filename
        val N = Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) inFile)
        val numbers = List.tabulate (N, fn _ => Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) inFile))
        val _ = TextIO.closeIn inFile
        val result = minimalDifference numbers
    in
        print (Int.toString result ^ "\n")
    end