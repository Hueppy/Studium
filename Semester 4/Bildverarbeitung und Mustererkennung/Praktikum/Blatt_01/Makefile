DOC := Blatt1.pdf
ARC := abgabe.zip

all: $(ARC)

clean:
	rm abgabe.zip
	latexmk -CA

spell: spell_$(SRC) $(foreach src, $(ADD_SRC), spell_$(src))

dummy:

spell_%: % dummy
	aspell -t -c $< -l de

abgabe.zip: $(DOC)
	7z a abgabe.zip $(DOC) *.py

%.pdf: %.tex
	latexmk -pdf -pdflatex="pdflatex -interaction=nonstopmode" -use-make $<

.PHONY: all clean dummy spell
