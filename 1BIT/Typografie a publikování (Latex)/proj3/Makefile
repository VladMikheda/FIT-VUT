#
#Projekt: Projekt č. 3
#Autor: Vladislav Mikheda
#Login: xmikhe00
#
DOK = proj3

$(DOK).pdf: $(DOK).ps
	ps2pdf -sPAPERSIZE=a4 $(DOK).ps

$(DOK).ps: $(DOK).dvi
	dvips $(DOK).dvi

$(DOK).dvi: $(DOK).tex
	latex $(DOK).tex
	latex $(DOK).tex
	
clean:
	rm -f ${DOK}.{aux,dvi,log,ps,out}
	
cleanpdf:
	rm -f ${DOK}.pdf


