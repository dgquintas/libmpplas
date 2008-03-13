PROGRAM = trans.pdf

SHELL = /bin/bash
LATEX = /usr/bin/pdflatex
DVIPDF = /usr/bin/dvipdf
BIBTEX = /usr/bin/bibtex
MAKEINDEX = /usr/bin/makeindex
FLAGSLATEX =  
FLAGSDVIPDF =


trans.pdf: trans.tex
	$(LATEX) $(FLAGSLATEX) trans.tex
	$(LATEX) $(FLAGSLATEX) trans.tex
	$(LATEX) $(FLAGSLATEX) trans.tex

clean:
	rm -f ${PROGRAM} *.aux *.bbl *.blg *.idx *.log *.thm *.toc *.dvi *.lof *.loa *.ilg *.ind *.snm *.out *.nav
	
