-- Wertstoff Bestimmungen
select wertstoff.name_wertstoff as Wertstoff,
wertstofftyp.name_wertstofftyp as Typ,
entsorgungsbestimmung.name_entsorgungsbestimmung as Entsorgung,
transportvorschrift.name_transportvorschrift as Transportvorschrift
from wertstoff
join wertstofftyp on wertstoff.id_wertstofftyp = werTstofftyp.id_wertstofftyp
join entsorgungsbestimmung on wertstoff.id_entsorgungsbestimmung = entsorgungsbestimmung.id_entsorgungsbestimmung
join transportvorschrift on wertstoff.id_transportvorschrift= transportvorschrift.id_transportvorschrift;

-- Wertstoff Bestimmungen
select wertstoff.name_wertstoff as Name,
werTstofftyp.name_wertstofftyp as Typ,
wertstoff.recyclebar_wertstoff,
wertstoff.beschreibung_wertstoff,
wertstoff.menge_wertstoff
from wertstoff
join werTstofftyp on wertstoff.id_wertstofftyp = werTstofftyp.id_wertstofftyp
order by wertstofftyp.name_wertstofftyp;


select route.beschreibung_route,
fremdbetrieb.name_fremdbetrieb as fremdbetrieb,
personal.name_personal as Personal,
wertstoff.name_wertstoff as Wertstoff,
transportvorschrift.name_transportvorschrift as Vorschrift,
entsorgungsbestimmung.name_entsorgungsbestimmung as Entsorgung
from route 
left join fremdbetrieb on route.id_fremdbetrieb = fremdbetrieb.id_fremdbetrieb
left join personal on route.id_personal = personal.id_personal
join routewertstoff on route.id_route = routewertstoff.id_route
join wertstoff on routewertstoff.id_wertstoff= wertstoff.id_wertstoff
join transportvorschrift on wertstoff.id_transportvorschrift = transportvorschrift.id_transportvorschrift
join entsorgungsbestimmung on wertstoff.id_entsorgungsbestimmung= entsorgungsbestimmung.id_entsorgungsbestimmung;

-- Person hat Verkäufe
select personal.name_personal,
personal.vorname_personal,
personal.id_Personal 
from Personal
left join verkauf on personal.id_personal= verkauf.id_personal
WHERE verkauf.id_verkauf is not null;

-- Verkäufe an Privat
select personal.name_Personal||' '||personal.vorname_personal  as Verkaeufer,
menge_verkauf as Menge,
gesamtpreis_verkauf as Preis,
wertstoff.name_wertstoff as Wertstoff,
adresse.strassenname_adresse || ' ' || adresse.hausnummer_adresse || ' '|| adresse.plz_adresse   as Verkaufsort
from verkauf 
JOIN wertstoffverkauf on verkauf.id_verkauf = wertstoffverkauf.id_verkauf
join wertstoff on wertstoffverkauf.id_wertstoff =  wertstoff.id_wertstoff
join Depot on verkauf.id_depot = depot.id_depot
join adresse on depot.id_adresse = adresse.id_adresse
join personal on verkauf.id_personal= personal.id_personal
WHERE verkauf.id_fremdbetrieb is null;

-- Routen nach Gefahrenstufe
select route.beschreibung_Route,
wertstoff.id_wertstoffgefahrenstufe
from route
join routewertstoff on route.id_route=routewertstoff.id_route
join wertstoff on routewertstoff.id_wertstoff= wertstoff.id_wertstoff
order by wertstoff.id_wertstoffgefahrenstufe;

-- Fuhrpark übersicht einzeln
select name_fahrzeug as Fahrzeugname,
model_fahrzeug as Modell,
fuehrerschein_fahrzeug as BenoetigterFuehrerschein
from fahrzeug 
LEFT join fuhrpark on fahrzeug.id_fuhrpark =fuhrpark.id_fuhrpark
WHERE fuhrpark.name_fuhrpark = 'Biocontainer'; -- <-- Parameter


-- Route Ablauf Übersicht Alle
select 
adresseroute.id_route as Route,
ADRESSEROUTE.NUMMER_ADRESSEROUTE as Nummer,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer,
adresse.adressenzusatz_adresse as Zusatz,
adresse.plz_adresse as PLZ,
adresse.land_adresse as Land
from ADRESSEROUTE
join adresse on ADRESSEROUTE.id_adresse = adresse.id_adresse
join route on ADRESSEROUTE.id_route = route.id_route
order by route.id_route, adresseroute.NUMMER_ADRESSEROUTE;

--  Route Ablauf Übersicht einzeln
select 
ADRESSEROUTE.NUMMER_ADRESSEROUTE as Nummer,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer,
adresse.adressenzusatz_adresse as Zusatz,
adresse.plz_adresse as PLZ,
adresse.land_adresse as Land
from ADRESSEROUTE
join adresse on ADRESSEROUTE.id_adresse = adresse.id_adresse
join route on ADRESSEROUTE.id_route = route.id_route
where adresseroute.id_route = 1 -- <---- Parameter
order by adresseroute.NUMMER_ADRESSEROUTE;



-- Routenübersicht - Firmenintern
select route.id_route as ID,
route.beschreibung_route as Beschreibung,
route.art_route as Art,
wertstoff.id_wertstoff,
wertstoff.name_wertstoff as Wertstoff,
transportvorschrift.name_transportvorschrift as Transportvorschrift,
transportvorschrift.beschreibung_t_vorschrift as Transportvorschrift_Beschreibung,
depot.name_depot as Depotname,
adresse.strassenname_adresse as Straße,
adresse.hausnummer_adresse as Hausnummer,
adresse.adressenzusatz_adresse as Zusatz,
adresse.plz_adresse as PLZ,
adresse.land_adresse as Land,
personal.name_Personal||' '||personal.vorname_personal as Fahrer,
fahrzeug.name_fahrzeug as Fahrzeug,
fahrzeug.model_fahrzeug as Fahrzeugmodell,
fuhrpark.name_fuhrpark as FahrzeugStandort
from route
join routewertstoff on route.id_route = routewertstoff.id_route
join wertstoff on routewertstoff.id_wertstoff = wertstoff.id_wertstoff
join transportvorschrift on wertstoff.id_transportvorschrift = transportvorschrift.id_transportvorschrift
join depot on route.id_depot = depot.id_depot
join adresse on depot.id_adresse = adresse.id_adresse
join personal on route.id_personal = personal.id_personal
join fahrzeug on route.id_fahrzeug = fahrzeug.id_fahrzeug
join fuhrpark on fahrzeug.id_fuhrpark = fuhrpark.id_fuhrpark
where route.id_fremdbetrieb is NULL
order by route.id_route;