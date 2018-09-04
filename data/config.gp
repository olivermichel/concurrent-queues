set terminal pdfcairo font "sans,12" linewidth 4 rounded fontscale 1.0 size 6,3

set style line 80 lt rgb "#333333"

set style line 81 lt 0   # dashed
set style line 81 lt rgb "#999999" lw 0.75 # grey
set grid back ls 81

set xtics nomirror
set ytics nomirror

set key bottom right

set border 3 back ls 80

set style line 1 lt rgb "#A00000" lw 1.3 pt 6
set style line 2 lt rgb "#006699" lw 1.3 pt 4
set style line 3 lt rgb "#5060D0" lw 1.3 pt 8
set style line 4 lt rgb "#F25900" lw 1.3 pt 12
set style line 5 lt rgb "#666666" lw 1.3 pt -1