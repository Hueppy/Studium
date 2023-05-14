house(Color, Nationality, Cigarettes, Drink, Pet).

right_of(A, B, L) :- append(_, [B, A| _], L).
left_of(A, B, L)  :- append(_, [A, B| _], L).

adjacent(A, B, L) :- right_of(A, B, L); left_of(A, B, L).

houses(H) :- length(H, 5),
    member(    house(red,    england,   _,            _,           _  ), H),
    member(    house(_,      spanish,   _,            _,           dog), H),
    H = [      house(_,      norwegian, _,            _,           _  ), _, _, _, _],
    member(    house(yellow, _,         kools,        _,           _), H),
    adjacent(  house(_,      _,         _,            _,           fish), 
               house(_,      _,         chesterfield, _,           _), H), 
    adjacent(  house(_,      norwegian, _,            _,           fish), 
               house(blue,   _,         _,            _,           _), H), 
    member(    house(_,      _,         winston,      _,           snail), H),
    member(    house(_,      _,         luckystrike,  orangejuice, _), H),
    member(    house(_,      ukrainian, _,            tea,         _), H),
    member(    house(_,      japanese,  parliaments,  _,           _), H),
    adjacent(  house(_,      _,         _,            _,           horse), 
               house(_,      _,         kools,        _,           _), H), 
    member(    house(green,  _,         _,            coffee,      _), H),
    right_of(  house(green,  _,         _,            _,           _), 
               house(ivory,  _,         _,            _,           _), H), 
    H = [_, _, house(_,      _,         _,            milk,        _), _, _],
    member(    house(_,      _,         _,            water,       _), H),
    member(    house(_,      _,         _,            _,           zebra), H).

pet(Pet, House) :- houses(H), 
    House = house(_, _, _, _, Pet),
    member(House, H).

drink(Drink, House) :- houses(H), 
    House = house(_, _, _, Drink, _),
    member(House, H).