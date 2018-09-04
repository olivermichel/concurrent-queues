
comparison_plot.pdf: comparison_plot.gp comparison_plot.csv
	gnuplot $<

comparison_plot.csv: comparison.R moodycamel.csv queue1.csv queue2.csv queue3.csv queue4.csv queue5.csv
	R -f $<

clean:
	$(RM) comparison_plot.pdf
	$(RM) comparison_plot.csv
