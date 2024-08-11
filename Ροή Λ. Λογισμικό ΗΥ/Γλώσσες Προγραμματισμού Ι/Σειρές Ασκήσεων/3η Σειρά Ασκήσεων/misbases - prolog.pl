base(Num,Base,Dig):-
    Base>0,
    Base>Num,
    Dig=Num.

base(Num,Base,Dig):-
    R is div(Num,Base),
    Dig is mod(Num,Base),
    base(R,Base,Dig).
    
find_base(Num, Base) :-
    between(2, Num, Base),
    base(Num, Base, _),
    !.

minbases([],[]).
minbases([Num|Nums],[Base|Bases]):-
    find_base(Num,Base),
    minbases(Nums,Bases).        