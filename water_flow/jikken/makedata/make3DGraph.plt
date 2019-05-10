set xlabel "Margin"
set ylabel "Ratio (NAS / WF)"
set zlabel "Sales (Yen)"

set nokey

set xrange [0.02:0.33]
set yrange [0.27: 1.03]
set zrange [0:2.5e+5]

set view 65,60

splot "./stdout_C3_T4_data.txt" using 1:2:3 with lines
