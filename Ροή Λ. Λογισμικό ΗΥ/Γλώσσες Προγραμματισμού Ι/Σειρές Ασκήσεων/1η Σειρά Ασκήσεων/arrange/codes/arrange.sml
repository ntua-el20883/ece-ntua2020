datatype tree = Empty | Node of int * tree * tree;

(* Helper function to compare two lists lexicographically *)
fun lexCompare ([], []) = EQUAL
  | lexCompare ([], _::_) = LESS
  | lexCompare (_::_, []) = GREATER
  | lexCompare (x::xs, y::ys) =
      if x < y then LESS
      else if x > y then GREATER
      else lexCompare (xs, ys);

(* Recursive function to parse the tree from a list of integers *)
fun readTree lst =
    case lst of
         0::rest => (Empty, rest)
       | v::rest => 
           let 
               val (leftTree, rest1) = readTree rest
               val (rightTree, rest2) = readTree rest1
           in
               (Node(v, leftTree, rightTree), rest2)
           end
       | _ => (Empty, [])

(* Function to determine the minimal lexicographic in-order traversal *)
fun minInOrder Empty = []
  | minInOrder (Node(v, left, right)) =
    let
        val leftSeq = minInOrder left
        val rightSeq = minInOrder right
        val normal = leftSeq @ [v] @ rightSeq
        val swapped = rightSeq @ [v] @ leftSeq
    in
        if lexCompare(normal, swapped) = LESS then normal else swapped
    end;

(* Main function to read from file, process, and print the result *)
fun arrange filename =
    let
        val inFile = TextIO.openIn filename
        val N = Option.valOf (TextIO.inputLine inFile)
        val treeData = Option.valOf (TextIO.inputLine inFile)
        val treeList = List.map Int.fromString (String.tokens (fn c => c = #" ") treeData)
        val cleanList = List.mapPartial (fn SOME x => SOME x | NONE => NONE) treeList
        val (tree, _) = readTree cleanList
        val result = minInOrder tree
    in
        TextIO.closeIn inFile;
        (* Print the result *)
        List.app (fn x => (print (Int.toString x ^ " "))) result;
        print "\n"
    end;
