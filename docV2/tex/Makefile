PROGRAM = doc.pdf

SHELL = /bin/bash
LATEX = /usr/bin/pdflatex
DVIPDF = /usr/bin/dvipdf
BIBTEX = /usr/bin/bibtex
MAKEINDEX = /usr/bin/makeindex
FLAGSLATEX =  
FLAGSDVIPDF =



doc.pdf: doc.tex
	$(LATEX) $(FLAGSLATEX) doc.tex
	$(BIBTEX) doc.aux
	$(MAKEINDEX) doc.idx
	$(LATEX) $(FLAGSLATEX) doc.tex
	$(LATEX) $(FLAGSLATEX) doc.tex
	$(LATEX) $(FLAGSLATEX) doc.tex

clean:
	rm -f ${PROGRAM} *.aux *.bbl *.blg *.idx *.log *.thm *.toc *.dvi *.lof *.loa *.ilg *.ind
	
