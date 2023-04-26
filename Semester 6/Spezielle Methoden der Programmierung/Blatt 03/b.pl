istHauptstadtVon(berlin, deutschland).
istHauptstadtVon(paris, frankreich).
istHauptstadtVon(wien, oesterreich).
istHauptstadtVon(rom, italien).
istHauptstadtVon(amsterdam, niederlande).
istHauptstadtVon(tokyo, japan).
istHauptstadtVon(seol, suedkorea).
istHauptstadtVon(canberra, australien).
istHauptstadtVon(kapstadt, suedAfrika).

liegtImKontinent(deutschland, europa).
liegtImKontinent(frankreich, europa).
liegtImKontinent(oesterreich, europa).
liegtImKontinent(italien, europa).
liegtImKontinent(niederlande, europa).
liegtImKontinent(japan, asien).
liegtImKontinent(suedkorea, asien).
liegtImKontinent(australien, australien).
liegtImKontinent(suedAfrika, afrika).

stadtLiegtInKontinent(Stadt, Kontinent) :- istHauptstadtVon(Stadt, X), liegtImKontinent(X, Kontinent).
stadtLiegtInEuropa(Stadt) :- stadtLiegtInKontinent(Stadt, europa).
stadtLiegtInAfrika(Stadt) :- stadtLiegtInKontinent(Stadt, afrika).

liegenImGleichenKontinent(StadtA, StadtB) :- stadtLiegtInKontinent(StadtA, X), stadtLiegtInKontinent(StadtB, X).
