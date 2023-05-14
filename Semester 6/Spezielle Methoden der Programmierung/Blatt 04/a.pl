on(a, b).
on(b, table).
on(c, d).
on(d, table).
on(e, table).
on(f, g).
on(g, h).
on(h, table).

top(X) :- on(X,_), \+(on(_,X)).

subtower(table, []).
subtower(H, [H|T]) :- on(H, X), subtower(X, T).

tower([H|T]) :- top(H), subtower(H, [H|T]).

higher([_], []).
higher([_|_], []).
higher([X|T1], [Y|T2]) :- subtower(X, [X|T1]), subtower(Y, [Y|T2]), higher(T1, T2).

highest(X) :- tower(X), \+(higher(_, X)).