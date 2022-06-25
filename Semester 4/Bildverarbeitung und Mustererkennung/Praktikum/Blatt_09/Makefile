DOC := Ausarbeitung.pdf
ARC := abgabe.zip

all: $(ARC)

clean:
	rm abgabe.zip
	latexmk -CA

spell: spell_$(SRC) $(foreach src, $(ADD_SRC), spell_$(src))

dummy:

spell_%: % dummy
	aspell -t -c $< -l de

$(ARC): $(DOC)
	7z a $@ $< *.py

%.pdf: %.tex $(wildcard *.png)
	latexmk -pdf -pdflatex="pdflatex -interaction=nonstopmode" -use-make -f $<

.PHONY: all clean dummy spell
