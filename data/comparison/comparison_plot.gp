
load '../config.gp'

set terminal pdfcairo font "sans,12" linewidth 4 rounded fontscale 1.0 size 6,2.5
set datafile separator ","

set xlabel "throughput [M records/s]"
set ylabel "CDF"

data_file = 'comparison_plot.csv'

stats data_file using 1 name 'queue1'
stats data_file using 2 name 'queue2'
stats data_file using 3 name 'queue3'
stats data_file using 4 name 'queue4'
stats data_file using 5 name 'queue5'

set output 'comparison_plot.pdf';
plot data_file using 1:(1./queue1_records) smooth cumulative title 'queue1' ls 1, \
     data_file using 2:(1./queue2_records) smooth cumulative title 'queue2' ls 2, \
     data_file using 3:(1./queue3_records) smooth cumulative title 'queue3' ls 3, \
     data_file using 4:(1./queue4_records) smooth cumulative title 'queue4' ls 4, \
     data_file using 5:(1./queue5_records) smooth cumulative title 'queue5' ls 5
