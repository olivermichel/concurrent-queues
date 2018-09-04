
load '../config.gp'

set terminal pdf
set datafile separator ","


set xlabel "batch size"
set ylabel "mean throughput [M records/s]"

set key off

set output 'batch_size_throughput_plot.pdf';
plot 'batch_size_throughput_plot.csv' using 1:2 with lp ls 1