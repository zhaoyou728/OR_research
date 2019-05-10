# cd "C:/home/dan/Dropbox/comm/semi/2011/usuki/120210"
# load "make3DGraph_BigChar.plt"

clear

#set xlabel "Margin" font "Arial,20"
#set ylabel "Ratio (NAS/WF)" +0,-1 font "Arial,20"

set label "Margin" font "Times,32" at screen 0.10, screen 0.15, screen 0.35
set label "Ratio" font "Times,32" at screen 0.6, screen 0.15, screen 0.3
set label "Sales (10^5 Yen)" font "Times,32" at screen 0.1, screen 0.88, screen 0.3
#set label "Margin" at screen 0.13, screen 0.2, screen 0.35
#set label "Ratio (NAS/WF)" at screen 0.6, screen 0.15, screen 0.3
#set label "Sales (Yen)" at screen 0.1, screen 0.82, screen 0.3

set nokey

set xrange [0.02:0.33]
set yrange [0.27: 1.03]
set zrange [0:2.5]

set xtics (0.10, 0.20, 0.30)
set ytics (0.30, 0.50, 0.70, 0.90)
set ztics (0.5, 1.5, 2.5)

set tics font "Arial,24"

set view 65,60

splot "./xxxxx.txt" using 1:2:3 with lines lw 2

set terminal jpeg
set output "xxxxx.jpg"
replot
