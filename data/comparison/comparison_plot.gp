
load '../config.gp'

set terminal pdfcairo font "sans,12" linewidth 4 rounded fontscale 1.0 size 6,2.5
set datafile separator ","

set xlabel "throughput [M records/s]"
set ylabel "CDF"

#set xrange[0:20]
set yrange[0:1]

data_file = 'comparison_plot.csv'

n = 20

set output 'comparison_plot.pdf';
plot data_file using 1:(1./n) smooth cumulative title 'queue1' ls 1, \
     data_file using 2:(1./n) smooth cumulative title 'queue2' ls 2, \
     data_file using 3:(1./n) smooth cumulative title 'queue3' ls 3, \
     data_file using 4:(1./n) smooth cumulative title 'moodycamel' ls 4, \
     data_file using 5:(1./n) smooth cumulative title 'queue4' ls 5, \
     data_file using 6:(1./n) smooth cumulative title 'queue5' ls 6
