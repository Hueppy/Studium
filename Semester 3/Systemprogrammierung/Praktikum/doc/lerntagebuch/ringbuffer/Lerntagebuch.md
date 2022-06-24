---
title:  'Lerntagebuch zum Blatt 05 (Ledanzeige)'
author:
- Fabian Pechta (robin_fabian.pechta@fh-bielefeld.de)
- Jan-Henrik Capsius (jan-henrik.capsius@fh-bielefeld.de@fh-bielefeld.de)
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

Implementierung einer Ringpuffer Datenstruktur.

# Ansatz und Modellierung

<!--
Bitte hier den Lösungsansatz kurz beschreiben:
-   Wie sollte die Aufgabe gelöst werden?
-   Welche Techniken wollten Sie einsetzen?
-   Wie sah Ihre Modellierung aus (UML-Diagramm)?
-   Worauf müssen Sie konkret achten?
-->

Folgende Datenstruktur wurde für die Implementierung vorgegeben:
```c
struct ring_buffer {
    size_t size, count, head;
    void **elems;
    void (*free_callback)(void *p);
};
```

Folgende Funktionen wurden für die Implementierung vorgegeben:
```c
ring_buffer *init_buffer(const size_t n, void (*f)(void *p));
int free_buffer(ring_buffer *cb);
void *read_buffer(ring_buffer *cb);
void write_buffer(ring_buffer *cb, void *data);
```
Die Funktion `init_buffer` eine neue Instanz der Datenstruktur erstellen und initialisieren,  
mit dem Parameter `n` lässt sich die Größe des resultierenden Puffers festlegen,  
mit dem Parameter `f` wird ein Callback angegeben, welcher zur freigabe der Elemente ausgeführt wird.  
Die Funktion `free_buffer` soll die Instanz, welche über den Parameter `cb` reingegeben wird freigegeben werden.  
Die Funktion `read_buffer` soll das älteste Element im Puffer zurückgeben, anschließend den `head`-Zeiger um ein Element verschieben.  
Die Funktion `write_buffer` soll einen Datensatz in den Puffer einhängen,  
ist der Puffer voll soll das älteste Element ersetzt werden, das ersetzte Element wird dabei freigegeben.

# Umsetzung

<!--
Bitte hier die Umsetzung der Lösung kurz beschreiben:
-   Was haben Sie gemacht,
-   an welchem Datum haben sie es gemacht,
-   wie lange hat es gedauert,
-   was war das Ergebnis?
-->

Die Funktion `init_buffer` wurde folgendermaßen implementiert:
```c
ring_buffer *init_buffer(const size_t n, void (*f)(void *p)) {
	ring_buffer *res = malloc(sizeof(ring_buffer));
	res->size = n;
	res->count = 0;
	res->head = 0;
	res->elems = malloc(sizeof(void*) * n);
	res->free_callback = f;
	
	return res;
}
```
Hierbei wird zunächst mittels `malloc` Speicher für die Datenstruktur alloziert,  
und dann die Werte der Felder initialisiert, dabei wird für das Feld `elemns` ebenfalls  
nocheinmal `malloc` aufgerufen und den Speicher für die Zeiger auf die Elemente zu allozieren.  

22.11.2021, 5 Minuten, Initialisierung der Datenstruktur möglich.  

Die Funktion `free_buffer` wurde folgendermaßen implementiert:
```c
int free_buffer(ring_buffer *cb) {
	size_t old_count = cb->count;
	while (cb->count > 0) {
		void *elem = read_buffer(cb);
		cb->free_callback(elem);
	}

	free(cb->elems);
	free(cb);

	return old_count;
}
```
Hierbei wird zunächst die Anzahl der Elemente in der Variable `old_count` gespeichert.  
Anschließend wird mit der Funktion `read_buffer` nacheinander jedes Element aus dem Puffer geholt,  
und dieses wird über den `free_callback` freigegeben.  
Nachdem alle Element freigegeben sind, wird danach der zunächst der allozierte Speicher für das `elems`-  
Feld freigegeben, dann der Speicher für die Datenstruktur ansich.  
Zum Schluss wird dann der Wert der Variable `old_count`, in welcher die Anzahl der Elemente der Datenstruktur  
vor der Freigabe gespeichert wurde, zurückgegeben.  

22.11.2021, 10 Minuten, Freigabe der Datenstruktur möglich.  

Die Funktion `read_buffer` wurde folgendermaßen implementiert:
```c
void *read_buffer(ring_buffer *cb) {
	void *data = NULL;
	if (cb->count > 0) {
		data = *(cb->elems + cb->head);
		cb->head = (cb->head + 1) % cb->size;
		cb->count--;	
	} 
	
	return data;
}
```
Hierbei prüft die Funktion zunächst ob Elemente im Puffer gespeichert sind.  
Ist dies der Fall holt sich die Funktion die Daten welche an der Stelle von `head` gespeichert ist,  
inkrementiert den `head` um 1 und rechnet das Ergebnis modulo der Größe des Puffers,  
sodass der Head am Ende des Puffers wieder zum Anfang "überläuft",  
anschließend wird der `count` dekrementiert.
Zum Schluss gibt die Funktion den Zeiger auf das Element zurück,  
war in der Datenstruktur kein Element gespeichert, wird `NULL` zurückgegeben.  

22.11.2021, 10 Minuten, Auslesen der Daten in der Datenstruktur möglich.  

Die Funktion `write_buffer`wurde folgendermaßen implementiert:
```c
void write_buffer(ring_buffer *cb, void *data) {
	size_t tail = (cb->head + cb->count) % cb->size;
    if (cb->size == cb->count) {
		void *old_elem = read_buffer(cb);
		cb->free_callback(old_elem);
	}

	*(cb->elems + tail) = data;
	cb->count++;
}
```
Hierbei berechnet die Funktion zunächst den `tail` (also den Ort der neusten Daten).  
Danach wird überprüft ob die Datenstruktur bereits voll ist, ist dieses der Fall  
holt sich die Funktion das älteste Element der Datenstruktur mit `read_buffer` und gibt dieses frei.  
Anschließend wird der Wert am `tail` auf die neuen Daten gesetzt und `count` inkrementiert.

22.11.2021, 7 Minuten, Einfügen von Daten in die Datenstruktur möglich  

22.11.2021, 1 Stunde, Lerntagebuch führen  

22.11.2021, 45 Minuten, Testfälle schreiben  

# Postmortem

<!--
Bitte blicken Sie auf die Aufgabe, Ihren Lösungsansatz und die Umsetzung
kritisch zurück:
-   Was hat funktioniert, was nicht? Würden Sie noch einmal so vorgehen?
-   Welche Probleme sind bei der Umsetzung Ihres Lösungsansatzes aufgetreten?
-   Wie haben Sie die Probleme letztlich gelöst?
-->

Die beschriebene Umsetzung konnte problemlos implementiert werden.
