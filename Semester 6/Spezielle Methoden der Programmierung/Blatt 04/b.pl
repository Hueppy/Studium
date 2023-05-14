sum([], X) :- X = 0.
sum([L|Ls], X) :- sum(Ls, Y), X is Y + L.

addone([], []).
addone([X|Xs], [Y|Ys]) :- addone(Xs, Ys), succ(X, Y).

max([X], X).
max([L|Ls], Z) :- max(Ls, Z), Z > L; Z = L.

pivot(_, [],    [],    []).
pivot(H, [X|T], [X|L], G)     :- X =< H, pivot(H, T, L, G).
pivot(H, [X|T], L,     [X|G]) :- X  > H, pivot(H, T, L, G).

qsort([], A, A).
qsort([H|T], A, Sorted) :- pivot(H, T, L1, L2), 
    qsort(L1, A,      S1), 
    qsort(L2, [H|S1], Sorted).

permutation(L, M) :- qsort(L, [], X), qsort(M, [], X).