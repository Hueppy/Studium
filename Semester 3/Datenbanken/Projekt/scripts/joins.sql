select personal.id_personal,
personal.chef_id_personal,
personal.name_personal as Name,
personal.vorname_personal as Vorname,
personal.geburtstag_personal as Geburtstag,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer, 
adresse.plz_adresse as Postleitzahl,
adresse.adressenzusatz_adresse as Adressenzusatz,
adresse.land_adresse as Land,
personalart.name_personalart as Personalart,
personalart.beschreibung_personalart as Beschreibung_Personalart
from PERSONAL 
join ADRESSE using(id_adresse)
join PERSONALART using(id_personalart);


select route.id_route,
route.beschreibung_route,
route.art_route,
route.id_depot,
-- adresse
depot.name_depot,
route.id_personal,
personal.name_personal,
personal.vorname_personal,
route.id_fremdbetrieb,
fremdbetrieb.name_fremdbetrieb,
route.id_fahrzeug,
fahrzeug.model_fahrzeug
from ROUTE
join DEPOT using(id_depot)
join PERSONAL using(id_personal)
join FREMDBETRIEB using(id_fremdbetrieb)
join FAHRZEUG using(id_fahrzeug);