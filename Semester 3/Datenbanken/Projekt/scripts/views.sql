drop view PERSONAL_ENTSORGUNG;
drop view PERSONAL_FÜHRUNG;
drop view PERSONAL_INSTANDHALTUNG;
drop view PERSONAL_OVERVIEW;
drop view PERSONAL_SAMMLUNG;
drop view PERSONAL_VERWALTUNG;
drop view depot_overview;


create view personal_overview
as select personal.id_personal,
personal.chef_id_personal,
personal.name_personal as Name,
personal.vorname_personal as Vorname,
personal.geburtstag_personal as Geburtstag,
personal.FUEHRERSCHEIN_PERSONAL as Fuehrerschein,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer, 
adresse.plz_adresse as Postleitzahl,
adresse.adressenzusatz_adresse as Adressenzusatz,
adresse.land_adresse as Land,
personalart.name_personalart as Personalart,
personalart.beschreibung_personalart as Beschreibung_Personalart
from personal,adresse,personalart
where personal.id_adresse=adresse.id_adresse
and personal.id_personalart=personalart.id_personalart;

create view personal_verwaltung
as select personal.id_personal,
personal.chef_id_personal,
personal.name_personal as Name,
personal.vorname_personal as Vorname,
personal.geburtstag_personal as Geburtstag,
personal.FUEHRERSCHEIN_PERSONAL as Fuehrerschein,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer, 
adresse.plz_adresse as Postleitzahl,
adresse.adressenzusatz_adresse as Adressenzusatz,
adresse.land_adresse as Land,
personalart.name_personalart as Personalart,
personalart.beschreibung_personalart as Beschreibung_Personalart
from personal,adresse,personalart
where personal.id_adresse=adresse.id_adresse
and personal.id_personalart=personalart.id_personalart
and personalart.name_personalart in ('Verwaltung');


create view personal_entsorgung
as select personal.id_personal,
personal.chef_id_personal,
personal.name_personal as Name,
personal.vorname_personal as Vorname,
personal.geburtstag_personal as Geburtstag,
personal.FUEHRERSCHEIN_PERSONAL as Fuehrerschein,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer, 
adresse.plz_adresse as Postleitzahl,
adresse.adressenzusatz_adresse as Adressenzusatz,
adresse.land_adresse as Land,
personalart.name_personalart as Personalart,
personalart.beschreibung_personalart as Beschreibung_Personalart
from personal,adresse,personalart
where personal.id_adresse=adresse.id_adresse
and personal.id_personalart=personalart.id_personalart
and personalart.name_personalart in ('Entsorgung');

create view personal_sammlung
as select personal.id_personal,
personal.chef_id_personal,
personal.name_personal as Name,
personal.vorname_personal as Vorname,
personal.geburtstag_personal as Geburtstag,
personal.FUEHRERSCHEIN_PERSONAL as Fuehrerschein,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer, 
adresse.plz_adresse as Postleitzahl,
adresse.adressenzusatz_adresse as Adressenzusatz,
adresse.land_adresse as Land,
personalart.name_personalart as Personalart,
personalart.beschreibung_personalart as Beschreibung_Personalart
from personal,adresse,personalart
where personal.id_adresse=adresse.id_adresse
and personal.id_personalart=personalart.id_personalart
and personalart.name_personalart in ('Sammlung');

create view personal_instandhaltung
as select personal.id_personal,
personal.chef_id_personal,
personal.name_personal as Name,
personal.vorname_personal as Vorname,
personal.geburtstag_personal as Geburtstag,
personal.FUEHRERSCHEIN_PERSONAL as Fuehrerschein,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer, 
adresse.plz_adresse as Postleitzahl,
adresse.adressenzusatz_adresse as Adressenzusatz,
adresse.land_adresse as Land,
personalart.name_personalart as Personalart,
personalart.beschreibung_personalart as Beschreibung_Personalart
from personal,adresse,personalart
where personal.id_adresse=adresse.id_adresse
and personal.id_personalart=personalart.id_personalart
and personalart.name_personalart in ('Instandhaltung');

create view personal_führung
as select personal.id_personal,
personal.chef_id_personal,
personal.name_personal as Name,
personal.vorname_personal as Vorname,
personal.geburtstag_personal as Geburtstag,
personal.FUEHRERSCHEIN_PERSONAL as Fuehrerschein,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer, 
adresse.plz_adresse as Postleitzahl,
adresse.adressenzusatz_adresse as Adressenzusatz,
adresse.land_adresse as Land,
personalart.name_personalart as Personalart,
personalart.beschreibung_personalart as Beschreibung_Personalart
from personal,adresse,personalart
where personal.id_adresse=adresse.id_adresse
and personal.id_personalart=personalart.id_personalart
and personalart.name_personalart in ('Führung');

create view depot_overview
as select depot.id_depot,
depot.name_depot,
depot.groesse_depot,
depot.lagerkapazitat_depot,
DEPOTERWEITERUNG.ID_DEPOTERWEITERUNG,
DEPOTERWEITERUNG.NAME_DEPOTERWEITERUNG，
DEPOTERWEITERUNG.ZUSATZBESCHREIBUNG_D_E,
DEPOTERWEITERUNG.AUSLASTUNG_D_ERWEITERUNG,
DEPOTERWEITERUNGART.NAME_DEPOTERWEITERUNGART,
DEPOTERWEITERUNGART.BESCHREIBUNG_D_ART,
DEPOTERWEITERUNGART.GROE_E_D_ART
from depot,DEPOTERWEITERUNG,DEPOTERWEITERUNGART
where depot.id_depot=DEPOTERWEITERUNG.id_depot
and DEPOTERWEITERUNG.ID_DEPOTERWEITERUNGART=DEPOTERWEITERUNGART.ID_DEPOTERWEITERUNGART;

-- create view fahrzeuge_overview
