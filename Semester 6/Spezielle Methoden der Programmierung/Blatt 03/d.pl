state(westernAustralia).
state(northernTerritory).
state(queensland).
state(newSouthWales).
state(victoria).
state(southAustralia).
state(tasmania).

neighbor(westernAustralia, northernTerritory).
neighbor(westernAustralia, southAustralia).

neighbor(northernTerritory, westernAustralia).
neighbor(northernTerritory, queensland).
neighbor(northernTerritory, southAustralia).

neighbor(queensland, northernTerritory).
neighbor(queensland, newSouthWales).
neighbor(queensland, southAustralia).

neighbor(newSouthWales, southAustralia).
neighbor(newSouthWales, queensland).
neighbor(newSouthWales, victoria).

neighbor(victoria, newSouthWales).
neighbor(victoria, southAustralia).

neighbor(southAustralia, westernAustralia).
neighbor(southAustralia, northernTerritory).
neighbor(southAustralia, queensland).
neighbor(southAustralia, newSouthWales).
neighbor(southAustralia, victoria).

coloring(State, Color) :- state(State), color(Color).

check_coloring(State, Color) :- coloring(State, Color), !, coloring(X, Color), not(neighbor(State, X)).

%conflict(A, B, Color) :- neighbor(A, B), color(A, Color), coloring(B; Color).

color(red).
color(green).
color(blue).

diffx(X, Y) :- color(X), color(Y), X \== Y.

map_coloring(WA, NT, SA, NSW, V, Q, T) :-
     diffx(WA, NT), diffx(WA, SA), diffx(NT, SA), diffx(NT, Q), diffx(Q, SA),
     diffx(Q, NSW), diffx(NSW, SA), diffx(NSW, V), diffx(V, SA), diffx(T, V).

