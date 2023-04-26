trans_a_b([], []).
trans_a_b([a|Xs], [b|Ys]) :- trans_a_b(Xs, Ys).
trans_a_b([X|Xs], [X|Ys]) :- X \= a, trans_a_b(Xs, Ys).

takeout(_, [], []).
takeout(X, [X|Ls], R) :- takeout(X, Ls, R).
takeout(X, [Y|Ls], [Y|Rs]) :- X \= Y, takeout(X, Ls, Rs).

accRev([], A, A).
accRev([H|T], A, R) :- accRev(T, [H|A], R).

rev(L,R) :- accRev(L,[],R).

palindrom(L) :- rev(L, L).