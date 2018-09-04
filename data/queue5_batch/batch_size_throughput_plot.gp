set terminal pdf
set datafile separator ","

set output 'batch_size_throughput_plot.pdf';
plot 'batch_size_throughput_plot.csv' using 1:2 with lp ls 1