---
title:  'Lerntagebuch zum Blatt 02 (Ledanzeige)'
author:
- Fabian Pechta (robin_fabian.pechta@fh-bielefeld.de)
- Jan-Henrik Capsius (@fh-bielefeld.de)
- Patrick Hüntelmann (patrick.huentelmann@fh-bielefeld.de)
...

<!--
Führen Sie zu jedem Aufgabenblatt und zum Projekt (Stationen 3-9) ein
Lerntagebuch in Ihrem Team. Kopieren Sie dazu diese Vorlage und füllen
Sie den Kopf entsprechend aus.

Im Lerntagebuch sollen Sie Ihr Vorgehen bei der Bearbeitung des jeweiligen
Aufgabenblattes vom ersten Schritt bis zur Abgabe der Lösung dokumentieren,
d.h. wie sind Sie die gestellte Aufgabe angegangen (und warum), was war
Ihr Plan und auf welche Probleme sind Sie bei der Umsetzung gestoßen und
wie haben Sie diese Probleme gelöst. Beachten Sie die vorgegebene Struktur.
Für jede Abgabe sollte ungefähr eine DIN-A4-Seite Text erstellt werden,
d.h. ca. 400 Wörter umfassen. Wer das Lerntagebuch nur ungenügend führt
oder es gar nicht mit abgibt, bekommt für die betreffende Abgabe 0 Punkte.

Checken Sie das Lerntagebuch mit in Ihr Projekt/Git-Repo ein.

Schreiben Sie den Text mit [Markdown](https://pandoc.org/MANUAL.html#pandocs-markdown).

Geben Sie das Lerntagebuch stets mit ab. Achtung: Wenn Sie Abbildungen
einbetten (etwa UML-Diagramme), denken Sie daran, diese auch abzugeben!

Beachten Sie auch die Hinweise im [Orga "Bewertung der Aufgaben"](pm_orga.html#punkte)
sowie [Praktikumsblatt "Lerntagebuch"](pm_praktikum.html#lerntagebuch).
-->


# Aufgabe

<!--
Bitte hier die zu lösende Aufgabe kurz in eigenen Worten beschreiben.
-->

Entwickeln eines Programmes zur Demonstration der Ansteuerung einer LED-Segmentanzeige

# Ansatz und Modellierung

<!--
Bitte hier den Lösungsansatz kurz beschreiben:
-   Wie sollte die Aufgabe gelöst werden?
-   Welche Techniken wollten Sie einsetzen?
-   Wie sah Ihre Modellierung aus (UML-Diagramm)?
-   Worauf müssen Sie konkret achten?
-->

Zunächst soll in der Header-Datei `ledanzeige/segmentanzeige.h` einige Datenstrukturen definiert werden:
 * Ein Typ `byte` der vorzeichenlose 8-Bit Werte speichert
   * Hier ist geplant den vorzeichenlosen 8-Bit Typen `uint8_t` aus `stdint.h` zu benutzen
 * Ein Aufzählungstyp `segment` mit den Elementen `SEG1`, `SEG2`, `SEG3` und `SEG4`
 * Ein Aufzählungstyp `dot` mit den Elementen `OFF` und `ON`
 * Ein Aufzählungstyp `brightness` mit den Elementen `DARK`, `MEDIUM` und `BRIGHT`

 Anschließend soll in der Datei `ledanzeige/segmentanzeige.c` die Funktion `TM1637_write_byte(byte wr_data)` implementiert werden, welche den übergebenen byte seriell überträgt.
  * Hierzu soll zunächst der Clock-Pin auf `LOW` geschaltet werden
  * Danach soll soll der Daten-Pin je nach Wert des Bits auf `LOW` oder `HIGH` geschaltet werden
  * Dann soll der Clock-Pin wieder auf `HIGH` geschaltet werden
  * Nach jedem `digitalWrite()`-Aufruf soll mit `delayMicroseconds()` kurz gewartet werden um die Spannung zu stabilisieren
  * Am Ende der Übertragung soll die Funktion `TM1637_ack()` aufgerufen werden

Zum Schluss soll dann ein kleines Programm geschrieben werden, welches mit der Funktion `void TM1637_display_number(float number)` aus der Datei `ledanzeige/TM1637.h` die LED-Segmentanzeige demonstriert.
 * Vor der Verwendung der LED-Segmentanzeige muss die Funktion `TM1637_setup()` aufgerufen werden


# Umsetzung

<!--
Bitte hier die Umsetzung der Lösung kurz beschreiben:
-   Was haben Sie gemacht,
-   an welchem Datum haben sie es gemacht,
-   wie lange hat es gedauert,
-   was war das Ergebnis?
-->

Der 8-Bit breite vorzeichenlose Datentyp `byte` wurde folgendermaßen umgesetzt:
```c
#include <stdint.h>

typedef uint8_t byte;
```

Die Aufzählungstypen `segment`, `dot` und `brightness` wurden folgendermaßen umgesetzt:
```c
typedef enum {
    SEG1 = 0,
    SEG2 = 1,
    SEG3 = 2,
    SEG4 = 3
} segment;

typedef enum {
    OFF = 0,
    ON  = 1
} dot;

typedef enum {
    DARK   = 0,
    MEDIUM = 1,
    BRIGHT = 7
} brightness;
```

Für die Umsetzung der Funktion `TM1637_write_byte` wurde zunächst folgende Hilfsfunktion umgesetzt, welche den Wert eines Pins setzt und anschließend kurz wartet:
```c
void writeAndDelay(int pin, int value) 
{
    digitalWrite(pin, value);
    delayMicroseconds(DELAY_TIMER);
}
```

Danach wurde die eigentliche Funktion folgendermaßen umgesetzt:
```c
void TM1637_write_byte(byte wr_data)
{
    byte mask = 1;
    while (mask > 0) {
        writeAndDelay(PIN_CLOCK, LOW);
        writeAndDelay(PIN_DATA, (wr_data & mask) > 0 ? HIGH : LOW);
        writeAndDelay(PIN_CLOCK, HIGH);

        mask <<= 1;
    }

    TM1637_ack();
}
```
Hierbei wird zunächst mit der Variable `mask` eine Bitmaske erzeugt, welche während der Schleife durch jedes Bit in dem übergebenen Wert durchläuft.

Das abschließende Demo-Programm wurde folgendermaßen umgesetzt:
```c
int main()
{
    uint8_t i;

    TM1637_setup();
    for (i = 0; i < 10; i++)
    {
        TM1637_display_number(i * 111.1);
        delay(2000);
    }    

    return 0;
}
```
Hierbei wird zunächst mit der Funktion `TM1637_setup()` die Segmentanzeige initialisiert, dann werden in einer Schleife der Wert `i * 111.1` mit der Funktion `TM1637_display_number` dargestellt und anschließend mit dem Aufruf `delay(2000);` 2000 Milisekunden gewartet.

# Postmortem

<!--
Bitte blicken Sie auf die Aufgabe, Ihren Lösungsansatz und die Umsetzung
kritisch zurück:
-   Was hat funktioniert, was nicht? Würden Sie noch einmal so vorgehen?
-   Welche Probleme sind bei der Umsetzung Ihres Lösungsansatzes aufgetreten?
-   Wie haben Sie die Probleme letztlich gelöst?
-->

Die im Blatt beschrieben Aufgaben konnten problemlos umgesetzt werden.