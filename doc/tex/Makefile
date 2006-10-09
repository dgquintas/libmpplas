PROGRAM = doc.pdf

SHELL = /bin/bash
LATEX = /usr/bin/latex
DVIPDF = /usr/bin/dvipdf
BIBTEX = /usr/bin/bibtex
MAKEINDEX = /usr/bin/makeindex
FLAGSLATEX =  
FLAGSDVIPDF =

${PROGRAM}: doc.dvi
	$(DVIPDF) $(FLAGSDVIPDF) doc.dvi


doc.dvi: doc.tex
	$(LATEX) $(FLAGSLATEX) doc.tex
	$(BIBTEX) doc.aux
	$(MAKEINDEX) doc.idx
	$(LATEX) $(FLAGSLATEX) doc.tex
	$(LATEX) $(FLAGSLATEX) doc.tex
	$(LATEX) $(FLAGSLATEX) doc.tex

clean:
	rm -f ${PROGRAM} *.aux *.bbl *.blg *.idx *.log *.thm *.toc *.dvi *.lof *.loa *.ilg *.ind
	
