
EXP   = queue5_batch
DOC   = queue5_batch.html
SRC   = queue5_batch.Rmd
DATA  = queue5_batch.csv
PLOTS = throughput-1.pdf throughput-1.png

$(DOC) $(addprefix fig/, $(PLOTS)): $(SRC) $(DATA)
	Rscript -e 'library(rmarkdown); rmarkdown::render("$<", "html_document")'

clean:
	$(RM) $(DOC) $(addprefix fig/, $(PLOTS))
	rmdir fig
