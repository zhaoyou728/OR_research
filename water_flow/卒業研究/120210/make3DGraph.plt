clear

#set xlabel "Margin" font "Helvetica,20"
#set ylabel "Ratio (NAS/WF)" +0,-1 font "Helvetica,20"

set label "Margin" font "Helvetica,20" at screen 0.13, screen 0.2, screen 0.35
set label "Ratio (NAS/WF)" font "Helvetica,20" at screen 0.6, screen 0.15, screen 0.3
set label "Sales (Yen)" font "Helvetica,20" at screen 0.1, screen 0.82, screen 0.3

set nokey

set xrange [0.02:0.33]
set yrange [0.27: 1.03]
set zrange [0:2.5e+5]

set view 65,60

set terminal postscript eps color enhanced "Helvetica,16"
set output "stdout_C3_T4_data_m.eps"
splot "./stdout_C3_T4_data_m.txt" using 1:2:3 with lines lw 2

