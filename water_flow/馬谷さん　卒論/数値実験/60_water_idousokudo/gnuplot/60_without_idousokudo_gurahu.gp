set size ratio 1.1 1.0
set yrange[0:80]
set xlabel font 'Arial,15' "移動速度（ m / 分）"
set ylabel font 'Arial,14' "流入時間（分）"
set style fill solid
set xtics font "Arial, 23"
set ytics font "Arial, 20"
set boxwidth 0.5 relative

plot "60_without_idousokudo_gurahu.dat" using 1:2:xtic(1) with linespoints lw 1 lc rgb "blue" notitle

#set terminal postscript eps enhanced color
#set terminal pdf
#set output sprintf("aaa.eps")
#set output "aaa.pdf"	
#replot