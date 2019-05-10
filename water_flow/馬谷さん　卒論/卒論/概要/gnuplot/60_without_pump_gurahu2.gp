#set size ratio 1.1 1.0
#set xrange[0:]
set yrange[-40:50]
set xlabel font 'Arial,10' "出入口番号"
#set ylabel font 'Arial,14' "流入時間（分）"
set style fill solid
#set xtics 1,1,24
#set ytics font "Arial, 20"
set boxwidth 0.5 relative

plot "60_without_Fteam_gurahu.dat" using 0:2:xtic(1) with boxes lw 1 lc rgb "dark-pink" notitle
replot "60_without_Eteam_gurahu.dat" using 0:2:xtic(1) with boxes lw 1 lc rgb "skyblue" notitle
replot "60_without_Dteam_gurahu.dat" using 0:2:xtic(1) with boxes lw 1 lc rgb "dark-violet" notitle
replot "60_without_Cteam_gurahu.dat" using 0:2:xtic(1) with boxes lw 1 lc rgb "green" notitle
replot "60_without_Bteam_gurahu.dat" using 0:2:xtic(1) with boxes lw 1 lc rgb "blue" notitle
replot "60_without_Ateam_gurahu.dat" using 0:2:xtic(1) with boxes lw 1 lc rgb "red" notitle


#set terminal postscript eps enhanced color
#set terminal pdf
#set output sprintf("aaa.eps")
#set output "aaa.pdf"	
#replot