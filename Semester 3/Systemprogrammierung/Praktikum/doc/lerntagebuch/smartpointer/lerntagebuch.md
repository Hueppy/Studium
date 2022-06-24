---
title:  'Lerntagebuch zum Blatt 08 (Smartpointer)'
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

Implementierung eines referenzgezählten Smartpointers

# Ansatz und Modellierung

<!--
Bitte hier den Lösungsansatz kurz beschreiben:
-   Wie sollte die Aufgabe gelöst werden?
-   Welche Techniken wollten Sie einsetzen?
-   Wie sah Ihre Modellierung aus (UML-Diagramm)?
-   Worauf müssen Sie konkret achten?
-->

Zunächst soll in der Datei `RefCounter.cpp` die Vorgaben der Klasse `RefCounter` in der vorgegebenen Datei `RefCounter.h` implementiert werden.  
Die Klasse implementiert einen einfachen Referenzzähler, und bietet folgende Methoden:  
 * `RefCounter()`: Erstellt einen neuen Referenzzähler (mit n = 0)
 * `void inc()`: Inkrementiert den Referenzzähler
 * `void dec()`: Dekrementiert den Referenzzähler
 * `bool isZero()`: Vergeleicht den Zählerstand mit 0
 * `unsigned int getRefCount()`: Gibt den aktuellen Zählerstand zurück
 
Anschließend soll in der Datei `NullReferenceException.h` eine Exception-Klasse deklariert werden, welche von `std::runtime_error` erbt.  

Zum Schluß soll dann die Vorgaben der Template-Klasse `SmartPointer` implementiert werden.  
Hier bietet die Klasse übliche C++ Konstrukte (Copy-Construktor, Assignment-Operator, ...) und Operator-Overloads (->, *), welche den Zugriff auf das Objekt hinter dem Pointer bieten, und noch einige Hilfsmethoden.

# Umsetzung

<!--
Bitte hier die Umsetzung der Lösung kurz beschreiben:
-   Was haben Sie gemacht,
-   an welchem Datum haben sie es gemacht,
-   wie lange hat es gedauert,
-   was war das Ergebnis?
-->

Die Klasse `RefCounter` wurde folgendermaßen implementiert:
```cpp
RefCounter::RefCounter() {
    this->n = 0;
}

void RefCounter::inc() {
    this->n++;
}

void RefCounter::dec() {
    this->n--;
}

bool RefCounter::isZero() const {
    return this->n == 0;
}

unsigned int RefCounter::getRefCount() const {
    return this->n;
}
```

Die Exception-Klasse `NullPointerException` wurde folgendermaßen implementiert:
```cpp
class NullPointerException : public std::runtime_error {
 public:
     NullPointerException() : std::runtime_error("aa"){}
}
```

Anschließend wurde die Template-Klasse `SmartPointer` implementiert.

Zum Schluss wurde dann die Implementierung mithilfe der vorgegebenen Unit-Tests auf ihre Korrektheit geprüft.


# Postmortem

<!--
Bitte blicken Sie auf die Aufgabe, Ihren Lösungsansatz und die Umsetzung
kritisch zurück:
-   Was hat funktioniert, was nicht? Würden Sie noch einmal so vorgehen?
-   Welche Probleme sind bei der Umsetzung Ihres Lösungsansatzes aufgetreten?
-   Wie haben Sie die Probleme letztlich gelöst?
-->

Die im Blatt beschrieben Aufgaben konnten problemlos umgesetzt werden.
