
batch_size_throughput_plot.pdf: batch_size_throughput_plot.gp batch_size_throughput_plot.csv \
	../config.gp
	gnuplot $<

batch_size_throughput_plot.csv: queue5_pipeline.R queue5_pipeline.csv
	R -q -f $< 2> /dev/null

clean:
	$(RM) batch_size_throughput_plot.csv
	$(RM) batch_size_throughput_plot.pdf