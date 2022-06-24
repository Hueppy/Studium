/*==============================================================*/
/* DBMS name:      ORACLE Version 19c                           */
/* Created on:     06.12.2021 13:24:42                          */
/*==============================================================*/


alter table ADRESSEROUTE
   drop constraint FK_ADRESSER_BESCHREIB_ROUTE;

alter table ADRESSEROUTE
   drop constraint FK_ADRESSER_VERFUGT_U_ADRESSE;

alter table DEPOT
   drop constraint FK_DEPOT_BESCHREIB_ADRESSE;

alter table DEPOTERWEITERUNG
   drop constraint FK_DEPOTERW_DEPOTERWE_DEPOTERW;

alter table DEPOTERWEITERUNG
   drop constraint FK_DEPOTERW_ERWEITERT_DEPOT;

alter table FAHRZEUG
   drop constraint FK_FAHRZEUG_FUHRPARKF_FUHRPARK;

alter table FAHRZEUG
   drop constraint FK_FAHRZEUG_FUEHRERSCHEIN;

alter table FREMDBETRIEB
   drop constraint FK_FREMDBET_BESCHREIB_ADRESSE;

alter table FUHRPARK
   drop constraint FK_FUHRPARK_BESCHREIB_ADRESSE;

alter table PERSONAL
   drop constraint FK_PERSONAL_ADRESSEPE_ADRESSE;

alter table PERSONAL
   drop constraint FK_PERSONAL_PERSONALP_PERSONAL;

alter table PERSONAL
   drop constraint FK_PERSONAL_PERSONALART;

alter table PERSONAL
   drop constraint FK_PERSONAL_FUEHRERSCHEIN;

alter table ROUTE
   drop constraint FK_ROUTE_ROUTEDEPO_DEPOT;

alter table ROUTE
   drop constraint FK_ROUTE_ROUTEFAHR_FAHRZEUG;

alter table ROUTE
   drop constraint FK_ROUTE_ROUTEFREM_FREMDBET;

alter table ROUTE
   drop constraint FK_ROUTE_ROUTEPERS_PERSONAL;

alter table ROUTEWERTSTOFF
   drop constraint FK_ROUTEWER_TRANSPORT_WERTSTOF;

alter table ROUTEWERTSTOFF
   drop constraint FK_ROUTEWER_WIRD_TRAN_ROUTE;

alter table VERKAUF
   drop constraint FK_VERKAUF_PERSONALV_PERSONAL;

alter table VERKAUF
   drop constraint FK_VERKAUF_VERKAUFDE_DEPOT;

alter table VERKAUF
   drop constraint FK_VERKAUF_VERKAUFFR_FREMDBET;

alter table WERTSTOFF
   drop constraint FK_WERTSTOF_ENTSORGUN_ENTSORGU;

alter table WERTSTOFF
   drop constraint FK_WERTSTOF_TRANSPORT_TRANSPOR;

alter table WERTSTOFF
   drop constraint FK_WERTSTOF_WERTSTOFFG_WERTSTOF;

alter table WERTSTOFF
   drop constraint FK_WERTSTOF_WERTSTOFFW_WERTSTOFF;

alter table WERTSTOFF
   drop constraint FK_WERTSTOF_WERTSTOFF_WERTSTOF;

alter table WERTSTOFFVERKAUF
   drop constraint FK_WERTSTOF_BEINHALTE_WERTSTOF;

alter table WERTSTOFFVERKAUF
   drop constraint FK_WERTSTOF_WIRD_VERK_VERKAUF;

alter table WERTSTOFFDEPOT
   drop constraint FK_WERTSTOFFD_WERTSTOFF;

alter table WERTSTOFFDEPOT
   drop constraint FK_WERTSTOFFD_DEPOT;

drop table ADRESSE cascade constraints;

drop index BESCHREIBT4_FK;

drop index VERFUGT_UBER5_FK;

drop table ADRESSEROUTE cascade constraints;

drop index BESCHREIBT_FK;

drop table DEPOT cascade constraints;

drop index DEPOTERWEITERUNG_D_ART_FK;

drop table DEPOTERWEITERUNG cascade constraints;

drop table DEPOTERWEITERUNGART cascade constraints;

drop table ENTSORGUNGSBESTIMMUNG cascade constraints;

drop index FUHRPARKFAHRZEUG_FK;

drop table FAHRZEUG cascade constraints;

drop index BESCHREIBT3_FK;

drop table FREMDBETRIEB cascade constraints;

drop index BESCHREIBT2_FK;

drop table FUHRPARK cascade constraints;

drop index PERSONALPERSONAL_FK;

drop index ADRESSEPERSONAL_FK;

drop index PERSONALPERSONALART_FK;

drop table PERSONAL cascade constraints;

drop table PERSONALART cascade constraints;

drop index ROUTEFREMDBETRIEB_FK;

drop index ROUTEDEPOT_FK;

drop index ROUTEPERSONAL_FK;

drop index ROUTEFAHRZEUG_FK;

drop table ROUTE cascade constraints;

drop index TRANSPORTIERT_FK;

drop index WIRD_TRANSPORTIERT_IN_FK;

drop table ROUTEWERTSTOFF cascade constraints;

drop table TRANSPORTVORSCHRIFT cascade constraints;

drop index PERSONALVERKAUF_FK;

drop index VERKAUFDEPOT_FK;

drop index VERKAUFFREMDBETRIEB_FK;

drop table VERKAUF cascade constraints;

drop table WERTSTOFFTYP cascade constraints;

drop table FUEHRERSCHEIN cascade constraints;

drop index WERTSTOFFWERTSTOFF_FK;

drop index TRANSPORTVORSCHRIFTWERTSTOFF_FK;

drop index ENTSORGUNGSB_WERTSTOFF_FK;

drop index WERTSTOFFGEFAHRENSTUFE_FK;

drop index WERTSTOFFWERTSTOFFTYP_FK;

drop table WERTSTOFF cascade constraints;

drop table WERTSTOFFGEFAHRENSTUFE cascade constraints;

drop index WIRD_VERKAUFT_FK;

drop index BEINHALTET_FK;

drop table WERTSTOFFVERKAUF cascade constraints;

drop table WERTSTOFFDEPOT cascade constraints;

/*==============================================================*/
/* Table: ADRESSE                                               */
/*==============================================================*/
create table ADRESSE (
   ID_ADRESSE           INTEGER               not null,
   STRASSENNAME_ADRESSE VARCHAR2(1024)        not null,
   HAUSNUMMER_ADRESSE   INTEGER,
   PLZ_ADRESSE          INTEGER,
   ADRESSENZUSATZ_ADRESSE VARCHAR2(1024),
   LAND_ADRESSE         VARCHAR2(1024),
   constraint PK_ADRESSE primary key (ID_ADRESSE)
);

/*==============================================================*/
/* Table: ADRESSEROUTE                                          */
/*==============================================================*/
create table ADRESSEROUTE (
   ID_ADRESSE           INTEGER               not null,
   ID_ROUTE             INTEGER               not null,
   NUMMER_ADRESSEROUTE  INTEGER               not null,
   constraint PK_ADRESSEROUTE primary key (ID_ADRESSE, ID_ROUTE, NUMMER_ADRESSEROUTE)
);

/*==============================================================*/
/* Index: VERFUGT_UBER5_FK                                      */
/*==============================================================*/
create index VERFUGT_UBER5_FK on ADRESSEROUTE (
   ID_ADRESSE ASC
);

/*==============================================================*/
/* Index: BESCHREIBT4_FK                                        */
/*==============================================================*/
create index BESCHREIBT4_FK on ADRESSEROUTE (
   ID_ROUTE ASC
);

/*==============================================================*/
/* Table: DEPOT                                                 */
/*==============================================================*/
create table DEPOT (
   ID_DEPOT             INTEGER               not null,
   ID_ADRESSE           INTEGER               not null,
   NAME_DEPOT           VARCHAR2(1024)        not null,
   GROESSE_DEPOT        FLOAT,
   LAGERKAPAZITAT_DEPOT INTEGER,
   constraint PK_DEPOT primary key (ID_DEPOT)
);

/*==============================================================*/
/* Index: BESCHREIBT_FK                                         */
/*==============================================================*/
create index BESCHREIBT_FK on DEPOT (
   ID_ADRESSE ASC
);

/*==============================================================*/
/* Table: DEPOTERWEITERUNG                                      */
/*==============================================================*/
create table DEPOTERWEITERUNG (
   ID_DEPOTERWEITERUNG  INTEGER               not null,
   ID_DEPOT             INTEGER               not null,
   ID_DEPOTERWEITERUNGART INTEGER               not null,
   NAME_DEPOTERWEITERUNG VARCHAR2(1024)        not null,
   ZUSATZBESCHREIBUNG_D_E CLOB,
   AUSLASTUNG_D_ERWEITERUNG INTEGER,
   constraint PK_DEPOTERWEITERUNG primary key (ID_DEPOTERWEITERUNG)
);

/*==============================================================*/
/* Index: DEPOTERWEITERUNG_D_ART_FK                             */
/*==============================================================*/
create index DEPOTERWEITERUNG_D_ART_FK on DEPOTERWEITERUNG (
   ID_DEPOTERWEITERUNGART ASC
);

/*==============================================================*/
/* Table: DEPOTERWEITERUNGART                                   */
/*==============================================================*/
create table DEPOTERWEITERUNGART (
   ID_DEPOTERWEITERUNGART INTEGER               not null,
   NAME_DEPOTERWEITERUNGART VARCHAR2(1024)        not null,
   PREIS_DEPOTERWEITERUNGART INTEGER,
   BESCHREIBUNG_D_ART   CLOB,
   GROE_E_D_ART         INTEGER,
   constraint PK_DEPOTERWEITERUNGART primary key (ID_DEPOTERWEITERUNGART)
);

/*==============================================================*/
/* Table: ENTSORGUNGSBESTIMMUNG                                 */
/*==============================================================*/
create table ENTSORGUNGSBESTIMMUNG (
   ID_ENTSORGUNGSBESTIMMUNG INTEGER               not null,
   NAME_ENTSORGUNGSBESTIMMUNG VARCHAR2(1024)        not null,
   BESCHREIBUNG_E_BESTIMMUNG CLOB,
   constraint PK_ENTSORGUNGSBESTIMMUNG primary key (ID_ENTSORGUNGSBESTIMMUNG)
);

/*==============================================================*/
/* Table: FAHRZEUG                                              */
/*==============================================================*/
create table FAHRZEUG (
   ID_FAHRZEUG          INTEGER               not null,
   ID_FUHRPARK          INTEGER,
   NAME_FAHRZEUG        VARCHAR2(1024)        not null,
   MODEL_FAHRZEUG       VARCHAR2(1024),
   TANKGROESSE_FAHRZEUG INTEGER,
   KAUFPREIS_FAHRZEUG   INTEGER,
   FUEHRERSCHEIN_FAHRZEUG VARCHAR2(1024),
   constraint PK_FAHRZEUG primary key (ID_FAHRZEUG)
);

/*==============================================================*/
/* Index: FUHRPARKFAHRZEUG_FK                                   */
/*==============================================================*/
create index FUHRPARKFAHRZEUG_FK on FAHRZEUG (
   ID_FUHRPARK ASC
);

/*==============================================================*/
/* Table: FREMDBETRIEB                                          */
/*==============================================================*/
create table FREMDBETRIEB (
   ID_FREMDBETRIEB      INTEGER               not null,
   ID_ADRESSE           INTEGER               not null,
   NAME_FREMDBETRIEB    VARCHAR2(1024),
   BESCHREIBUNG_FREMDBETRIEB CLOB,
   constraint PK_FREMDBETRIEB primary key (ID_FREMDBETRIEB)
);

/*==============================================================*/
/* Index: BESCHREIBT3_FK                                        */
/*==============================================================*/
create index BESCHREIBT3_FK on FREMDBETRIEB (
   ID_ADRESSE ASC
);

/*==============================================================*/
/* Table: FUHRPARK                                              */
/*==============================================================*/
create table FUHRPARK (
   ID_FUHRPARK          INTEGER               not null,
   ID_ADRESSE           INTEGER               not null,
   NAME_FUHRPARK        VARCHAR2(1024)        not null,
   BESCHREIBUNG_FUHRPARK CLOB,
   STELLPLAETZE_FUHRPARK INTEGER,
   constraint PK_FUHRPARK primary key (ID_FUHRPARK)
);

/*==============================================================*/
/* Index: BESCHREIBT2_FK                                        */
/*==============================================================*/
create index BESCHREIBT2_FK on FUHRPARK (
   ID_ADRESSE ASC
);

/*==============================================================*/
/* Table: PERSONAL                                              */
/*==============================================================*/
create table PERSONAL (
   ID_PERSONAL          INTEGER               not null,
   ID_ADRESSE           INTEGER,
   CHEF_ID_PERSONAL     INTEGER,
   NAME_PERSONAL        VARCHAR2(1024)        not null,
   VORNAME_PERSONAL     VARCHAR2(1024),
   GEBURTSTAG_PERSONAL  DATE,
   ID_PERSONALART       INTEGER,
   FUEHRERSCHEIN_PERSONAL VARCHAR2(1024),
   GEHALT_PERSONAL_MONAT      INTEGER,
   constraint PK_PERSONAL primary key (ID_PERSONAL)
);

/*==============================================================*/
/* Index: PERSONALPERSONALART_FK                                */
/*==============================================================*/
create index PERSONALPERSONALART_FK on PERSONAL (
   ID_PERSONALART ASC
);

/*==============================================================*/
/* Index: ADRESSEPERSONAL_FK                                    */
/*==============================================================*/
create index ADRESSEPERSONAL_FK on PERSONAL (
   ID_ADRESSE ASC
);

/*==============================================================*/
/* Index: PERSONALPERSONAL_FK                                   */
/*==============================================================*/
create index PERSONALPERSONAL_FK on PERSONAL (
   CHEF_ID_PERSONAL ASC
);

/*==============================================================*/
/* Table: PERSONALART                                           */
/*==============================================================*/
create table PERSONALART (
   ID_PERSONALART       INTEGER               not null,
   NAME_PERSONALART     VARCHAR2(1024)        not null,
   BESCHREIBUNG_PERSONALART CLOB,
   constraint PK_PERSONALART primary key (ID_PERSONALART)
);

/*==============================================================*/
/* Table: ROUTE                                                 */
/*==============================================================*/
create table ROUTE (
   ID_ROUTE             INTEGER               not null,
   ID_DEPOT             INTEGER               not null,
   ID_PERSONAL          INTEGER,
   ID_FREMDBETRIEB      INTEGER,
   ID_FAHRZEUG          INTEGER,
   BESCHREIBUNG_ROUTE   CLOB,
   ART_ROUTE            VARCHAR2(1024),
   constraint PK_ROUTE primary key (ID_ROUTE)
);

/*==============================================================*/
/* Index: ROUTEFAHRZEUG_FK                                      */
/*==============================================================*/
create index ROUTEFAHRZEUG_FK on ROUTE (
   ID_FAHRZEUG ASC
);

/*==============================================================*/
/* Index: ROUTEPERSONAL_FK                                      */
/*==============================================================*/
create index ROUTEPERSONAL_FK on ROUTE (
   ID_PERSONAL ASC
);

/*==============================================================*/
/* Index: ROUTEDEPOT_FK                                         */
/*==============================================================*/
create index ROUTEDEPOT_FK on ROUTE (
   ID_DEPOT ASC
);

/*==============================================================*/
/* Index: ROUTEFREMDBETRIEB_FK                                  */
/*==============================================================*/
create index ROUTEFREMDBETRIEB_FK on ROUTE (
   ID_FREMDBETRIEB ASC
);

/*==============================================================*/
/* Table: ROUTEWERTSTOFF                                        */
/*==============================================================*/
create table ROUTEWERTSTOFF (
   ID_ROUTE             INTEGER               not null,
   ID_WERTSTOFF         INTEGER               not null,
   constraint PK_ROUTEWERTSTOFF primary key (ID_ROUTE, ID_WERTSTOFF)
);

/*==============================================================*/
/* Index: WIRD_TRANSPORTIERT_IN_FK                              */
/*==============================================================*/
create index WIRD_TRANSPORTIERT_IN_FK on ROUTEWERTSTOFF (
   ID_ROUTE ASC
);

/*==============================================================*/
/* Index: TRANSPORTIERT_FK                                      */
/*==============================================================*/
create index TRANSPORTIERT_FK on ROUTEWERTSTOFF (
   ID_WERTSTOFF ASC
);

/*==============================================================*/
/* Table: TRANSPORTVORSCHRIFT                                   */
/*==============================================================*/
create table TRANSPORTVORSCHRIFT (
   ID_TRANSPORTVORSCHRIFT INTEGER               not null,
   NAME_TRANSPORTVORSCHRIFT VARCHAR2(1024)        not null,
   BESCHREIBUNG_T_VORSCHRIFT CLOB,
   constraint PK_TRANSPORTVORSCHRIFT primary key (ID_TRANSPORTVORSCHRIFT)
);

/*==============================================================*/
/* Table: VERKAUF                                               */
/*==============================================================*/
create table VERKAUF (
   ID_VERKAUF           INTEGER               not null,
   ID_FREMDBETRIEB      INTEGER,
   ID_DEPOT             INTEGER               not null,
   ID_PERSONAL          INTEGER               not null,
   MENGE_VERKAUF        FLOAT,
   GESAMTPREIS_VERKAUF  FLOAT,
   constraint PK_VERKAUF primary key (ID_VERKAUF)
);

/*==============================================================*/
/* Index: VERKAUFFREMDBETRIEB_FK                                */
/*==============================================================*/
create index VERKAUFFREMDBETRIEB_FK on VERKAUF (
   ID_FREMDBETRIEB ASC
);

/*==============================================================*/
/* Index: VERKAUFDEPOT_FK                                       */
/*==============================================================*/
create index VERKAUFDEPOT_FK on VERKAUF (
   ID_DEPOT ASC
);

/*==============================================================*/
/* Index: PERSONALVERKAUF_FK                                    */
/*==============================================================*/
create index PERSONALVERKAUF_FK on VERKAUF (
   ID_PERSONAL ASC
);

/*==============================================================*/
/* Table: WERTSTOFFTYP                                           */
/*==============================================================*/
create table WERTSTOFFTYP (
   ID_WERTSTOFFTYP      INTEGER               not null,
   NAME_WERTSTOFFTYP    VARCHAR2(1024)        not null,
   BESCHREIBUNG_WERTSTOFFTYP CLOB,
   constraint PK_WERTSTOFFTYP primary key (ID_WERTSTOFFTYP)
);

/*==============================================================*/
/* Table: WERTSTOFF                                             */
/*==============================================================*/
create table WERTSTOFF (
   ID_WERTSTOFF         INTEGER               not null,
   ID_ENTSORGUNGSBESTIMMUNG INTEGER               not null,
   ID_WERTSTOFFTYP      INTEGER               not null,
   ID_WERTSTOFFGEFAHRENSTUFE INTEGER               not null,
   WER_ID_WERTSTOFF     INTEGER,
   ID_TRANSPORTVORSCHRIFT INTEGER               not null,
   NAME_WERTSTOFF       VARCHAR2(1024)        not null,
   BESCHREIBUNG_WERTSTOFF CLOB,
   MENGE_WERTSTOFF      FLOAT,
   PREIS_WERTSTOFF      FLOAT,
   RECYCLEBAR_WERTSTOFF SMALLINT,
   constraint PK_WERTSTOFF primary key (ID_WERTSTOFF)
);

/*==============================================================*/
/* Index: WERTSTOFFWERTSTOFFTYP_FK                                */
/*==============================================================*/
create index WERTSTOFFWERTSTOFFTYP_FK on WERTSTOFF (
   ID_WERTSTOFFTYP ASC
);

/*==============================================================*/
/* Index: WERTSTOFFGEFAHRENSTUFE_FK                              */
/*==============================================================*/
create index WERTSTOFFGEFAHRENSTUFE_FK on WERTSTOFF (
   ID_WERTSTOFFGEFAHRENSTUFE ASC
);

/*==============================================================*/
/* Index: ENTSORGUNGSB_WERTSTOFF_FK                             */
/*==============================================================*/
create index ENTSORGUNGSB_WERTSTOFF_FK on WERTSTOFF (
   ID_ENTSORGUNGSBESTIMMUNG ASC
);

/*==============================================================*/
/* Index: TRANSPORTVORSCHRIFTWERTSTOFF_FK                        */
/*==============================================================*/
create index TRANSPORTVORSCHRIFTWERTSTOFF_FK on WERTSTOFF (
   ID_TRANSPORTVORSCHRIFT ASC
);

/*==============================================================*/
/* Index: WERTSTOFFWERTSTOFF_FK                                 */
/*==============================================================*/
create index WERTSTOFFWERTSTOFF_FK on WERTSTOFF (
   WER_ID_WERTSTOFF ASC
);

/*==============================================================*/
/* Table: WERTSTOFFGEFAHRENSTUFE                                */
/*==============================================================*/
create table WERTSTOFFGEFAHRENSTUFE (
   ID_WERTSTOFFGEFAHRENSTUFE INTEGER               not null,
   NAME_WERTSTOFFGEFAHRENSTUFE VARCHAR2(1024)        not null,
   BESCHREIBUNG_W_GEFAHRENSTUFE CLOB,
   constraint PK_WERTSTOFFGEFAHRENSTUFE primary key (ID_WERTSTOFFGEFAHRENSTUFE)
);

/*==============================================================*/
/* Table: WERTSTOFFVERKAUF                                      */
/*==============================================================*/
create table WERTSTOFFVERKAUF (
   ID_WERTSTOFF         INTEGER               not null,
   ID_VERKAUF           INTEGER               not null,
   constraint PK_WERTSTOFFVERKAUF primary key (ID_WERTSTOFF, ID_VERKAUF)
);

/*==============================================================*/
/* Table: Fuehrerscheine                                        */
/*==============================================================*/
create table FUEHRERSCHEIN (
   BEZEICHNUNG          VARCHAR2(1024)           not null,
   constraint PK_FUEHRERSCHEIN primary key(BEZEICHNUNG)
);

/*==============================================================*/
/* Index: BEINHALTET_FK                                         */
/*==============================================================*/
create index BEINHALTET_FK on WERTSTOFFVERKAUF (
   ID_WERTSTOFF ASC
);

/*==============================================================*/
/* Index: WIRD_VERKAUFT_FK                                      */
/*==============================================================*/
create index WIRD_VERKAUFT_FK on WERTSTOFFVERKAUF (
   ID_VERKAUF ASC
);

create table WERTSTOFFDEPOT (
   ID_WERTSTOFF         INTEGER               not null,
   ID_DEPOT             INTEGER               not null,
   MENGE_WERTSTOFF      INTEGER               not null,
   constraint PK_WERTSTOFFDEPOT primary key(ID_WERTSTOFF,ID_DEPOT)
);

alter table ADRESSEROUTE
   add constraint FK_ADRESSER_BESCHREIB_ROUTE foreign key (ID_ROUTE)
      references ROUTE (ID_ROUTE);

alter table ADRESSEROUTE
   add constraint FK_ADRESSER_VERFUGT_U_ADRESSE foreign key (ID_ADRESSE)
      references ADRESSE (ID_ADRESSE);

alter table DEPOT
   add constraint FK_DEPOT_BESCHREIB_ADRESSE foreign key (ID_ADRESSE)
      references ADRESSE (ID_ADRESSE);

alter table DEPOTERWEITERUNG
   add constraint FK_DEPOTERW_DEPOTERWE_DEPOTERW foreign key (ID_DEPOTERWEITERUNGART)
      references DEPOTERWEITERUNGART (ID_DEPOTERWEITERUNGART);

alter table DEPOTERWEITERUNG
   add constraint FK_DEPOTERW_ERWEITERT_DEPOT foreign key (ID_DEPOT)
      references DEPOT (ID_DEPOT);

alter table FAHRZEUG
   add constraint FK_FAHRZEUG_FUHRPARKF_FUHRPARK foreign key (ID_FUHRPARK)
      references FUHRPARK (ID_FUHRPARK);

alter table FAHRZEUG
   add constraint FK_FAHRZEUG_FUEHRERSCHEIN foreign key (FUEHRERSCHEIN_FAHRZEUG)
      references FUEHRERSCHEIN (BEZEICHNUNG);

alter table FREMDBETRIEB
   add constraint FK_FREMDBET_BESCHREIB_ADRESSE foreign key (ID_ADRESSE)
      references ADRESSE (ID_ADRESSE);

alter table FUHRPARK
   add constraint FK_FUHRPARK_BESCHREIB_ADRESSE foreign key (ID_ADRESSE)
      references ADRESSE (ID_ADRESSE);

alter table PERSONAL
   add constraint FK_PERSONAL_ADRESSEPE_ADRESSE foreign key (ID_ADRESSE)
      references ADRESSE (ID_ADRESSE);

alter table PERSONAL
   add constraint FK_PERSONAL_PERSONALP_PERSONAL foreign key (CHEF_ID_PERSONAL)
      references PERSONAL (ID_PERSONAL);

alter table PERSONAL
   add constraint FK_PERSONAL_PERSONALART foreign key (ID_PERSONALART)
      references PERSONALART (ID_PERSONALART);

alter table PERSONAL
   add constraint FK_PERSONAL_FUEHRERSCHEIN foreign key (FUEHRERSCHEIN_PERSONAL)
      references FUEHRERSCHEIN (BEZEICHNUNG);

alter table ROUTE
   add constraint FK_ROUTE_ROUTEDEPO_DEPOT foreign key (ID_DEPOT)
      references DEPOT (ID_DEPOT);

alter table ROUTE
   add constraint FK_ROUTE_ROUTEFAHR_FAHRZEUG foreign key (ID_FAHRZEUG)
      references FAHRZEUG (ID_FAHRZEUG);

alter table ROUTE
   add constraint FK_ROUTE_ROUTEFREM_FREMDBET foreign key (ID_FREMDBETRIEB)
      references FREMDBETRIEB (ID_FREMDBETRIEB);

alter table ROUTE
   add constraint FK_ROUTE_ROUTEPERS_PERSONAL foreign key (ID_PERSONAL)
      references PERSONAL (ID_PERSONAL);

alter table ROUTEWERTSTOFF
   add constraint FK_ROUTEWER_TRANSPORT_WERTSTOF foreign key (ID_WERTSTOFF)
      references WERTSTOFF (ID_WERTSTOFF);

alter table ROUTEWERTSTOFF
   add constraint FK_ROUTEWER_WIRD_TRAN_ROUTE foreign key (ID_ROUTE)
      references ROUTE (ID_ROUTE);

alter table VERKAUF
   add constraint FK_VERKAUF_PERSONALV_PERSONAL foreign key (ID_PERSONAL)
      references PERSONAL (ID_PERSONAL);

alter table VERKAUF
   add constraint FK_VERKAUF_VERKAUFDE_DEPOT foreign key (ID_DEPOT)
      references DEPOT (ID_DEPOT);

alter table VERKAUF
   add constraint FK_VERKAUF_VERKAUFFR_FREMDBET foreign key (ID_FREMDBETRIEB)
      references FREMDBETRIEB (ID_FREMDBETRIEB);

alter table WERTSTOFF
   add constraint FK_WERTSTOF_ENTSORGUN_ENTSORGU foreign key (ID_ENTSORGUNGSBESTIMMUNG)
      references ENTSORGUNGSBESTIMMUNG (ID_ENTSORGUNGSBESTIMMUNG);

alter table WERTSTOFF
   add constraint FK_WERTSTOF_TRANSPORT_TRANSPOR foreign key (ID_TRANSPORTVORSCHRIFT)
      references TRANSPORTVORSCHRIFT (ID_TRANSPORTVORSCHRIFT);

alter table WERTSTOFF
   add constraint FK_WERTSTOF_WERTSTOFFG_WERTSTOF foreign key (ID_WERTSTOFFGEFAHRENSTUFE)
      references WERTSTOFFGEFAHRENSTUFE (ID_WERTSTOFFGEFAHRENSTUFE);

alter table WERTSTOFF
   add constraint FK_WERTSTOF_WERTSTOFFW_WERTSTOFF foreign key (ID_WERTSTOFFTYP)
      references WERTSTOFFTYP (ID_WERTSTOFFTYP);

alter table WERTSTOFF
   add constraint FK_WERTSTOF_WERTSTOFF_WERTSTOF foreign key (WER_ID_WERTSTOFF)
      references WERTSTOFF (ID_WERTSTOFF);

alter table WERTSTOFFVERKAUF
   add constraint FK_WERTSTOF_BEINHALTE_WERTSTOF foreign key (ID_WERTSTOFF)
      references WERTSTOFF (ID_WERTSTOFF);

alter table WERTSTOFFVERKAUF
   add constraint FK_WERTSTOF_WIRD_VERK_VERKAUF foreign key (ID_VERKAUF)
      references VERKAUF (ID_VERKAUF);

alter table WERTSTOFFDEPOT
   add constraint FK_WERTSTOFFD_WERTSTOFF foreign key (ID_WERTSTOFF)
      references WERTSTOFF (ID_WERTSTOFF);

alter table WERTSTOFFDEPOT
   add constraint FK_WERTSTOFFD_DEPOT foreign key (ID_DEPOT)
      references DEPOT (ID_DEPOT);