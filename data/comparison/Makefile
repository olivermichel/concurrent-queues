
DOC = comparison.html
SRC = comparison.Rmd
DATA = queue1.csv queue2.csv queue3.csv queue4.csv queue5.csv moodycamel.csv
PLOTS = cdf-1.pdf cdf-1.png means-1.pdf means-1.png

$(DOC) $(addprefix fig/, $(PLOTS)): $(SRC) $(DATA)
	Rscript -e 'library(rmarkdown); rmarkdown::render("$<", "html_document")'

clean:
	$(RM) $(DOC) $(addprefix fig/, $(PLOTS))
	rmdir fig
