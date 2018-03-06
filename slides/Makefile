default: pdf

pdf: gensvg
	pdflatex -jobname=slides_bright -interaction=nonstopmode '\newcommand{\thememode}{bright}\input{slides.tex}'
	pdflatex -jobname=slides_dark -interaction=nonstopmode '\newcommand{\thememode}{dark}\input{slides.tex}'
	make clean_latex;

clean: clean_latex
	rm imgs/generated/*

clean_latex:
	rm slides_*.aux slides_*.toc slides_*.fls slides_*.nav slides_*.snm slides_*.out slides_*.log slides_*.toc; true

rebuild: clean gensvg pdf

gensvg: 
	ruby ./theme/gen.rb
