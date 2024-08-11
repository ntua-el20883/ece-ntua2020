% Read the grid from the file and parse it
read_grid(File, N, Grid) :-
    open(File, read, Stream),
    read_line_to_codes(Stream, Line),
    number_codes(N, Line),
    read_lines(Stream, N, Grid),
    close(Stream).

% Read N lines of the grid
read_lines(Stream, N, Grid) :-
    read_lines(Stream, N, [], Grid).

read_lines(_, 0, Grid, Grid).
read_lines(Stream, N, Acc, Grid) :-
    N > 0,
    read_line_to_codes(Stream, Line),
    atom_codes(Atom, Line),
    atomic_list_concat(Atoms, ' ', Atom),
    maplist(atom_number, Atoms, Row),
    N1 is N - 1,
    read_lines(Stream, N1, [Row|Acc], Grid).

% Define possible moves and their coordinate changes
move(n,  (-1,  0)).
move(s,  ( 1,  0)).
move(w,  ( 0, -1)).
move(e,  ( 0,  1)).
move(ne, (-1,  1)).
move(nw, (-1, -1)).
move(se, ( 1,  1)).
move(sw, ( 1, -1)).

% Check if a move is within the grid bounds and leads to a cell with fewer cars
valid_move(Grid, (X, Y), Move, (NX, NY)) :-
    move(Move, (DX, DY)),
    NX is X + DX,
    NY is Y + DY,
    nth0(X, Grid, Row),
    nth0(Y, Row, Cars),
    NX >= 0, NY >= 0,
    length(Grid, N),
    NX < N, NY < N,
    nth0(NX, Grid, NRow),
    nth0(NY, NRow, NCars),
    NCars < Cars.

% Breadth-first search to find the shortest path
bfs(Grid, [[(X, Y)|Path]|_], [(X, Y)|Path], _) :-
    length(Grid, N),
    X =:= N - 1,
    Y =:= N - 1.
bfs(Grid, [[(X, Y)|Path]|Paths], Solution, Visited) :-
    findall(
        [(NX, NY), (X, Y)|Path],
        (valid_move(Grid, (X, Y), Move, (NX, NY)),
         \+ member((NX, NY), Visited)),
        NewPaths),
    append(Paths, NewPaths, NextPaths),
    bfs(Grid, NextPaths, Solution, [(X, Y)|Visited]).

% Convert the path of coordinates to moves
path_to_moves(_, [], []).
path_to_moves((PX, PY), [(NX, NY)|Path], [Move|Moves]) :-
    move(Move, (DX, DY)),
    NX is PX + DX,
    NY is PY + DY,
    path_to_moves((NX, NY), Path, Moves).

% Main predicate to find moves
moves(File, Moves) :-
    read_grid(File, N, Grid),
    bfs(Grid, [[(0, 0)]], Path, []),
    reverse(Path, RevPath),
    RevPath = [_|CoordPath],
    path_to_moves((0, 0), CoordPath, Moves).
