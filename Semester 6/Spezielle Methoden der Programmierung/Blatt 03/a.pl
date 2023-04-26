buch('1984', 'George Orwell', 'Dystopie').
buch('Eine Studie in Scharlachrot', 'Arthur Conan Doyle', 'Krimi').
buch('Die Drei ??? und der Super-Papagei', 'Robert Arthur', 'Krimi').
buch('Hitchhikers Guide to the Galaxy', 'Douglas Adams', 'Science Fiction').

autor(Autor, Titel) :- buch(Titel, Autor, _).
krimi(Autor, Titel) :- buch(Titel, Autor, 'Krimi').