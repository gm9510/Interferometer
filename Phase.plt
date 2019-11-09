reset

set terminal png enhance font "Times,35" size 1280,480
set output "Figuras_HE/GP_GS_fase_dp_10.4.png"
set pm3d
set view map

unset surface
unset key

#set label "(e)" at 1,3 tc rgb "black" front

set xlabel "t"	offset 0,1
set ylabel "x"			offset 1,0
set cblabel "{/Symbol f}"

set xtics ("0" 0, "10" 10, "20" 20, "30" 30 ,"40" 40) offset 0,0.5
set ytics ("-5" -5, "-3" -3, "0" 0, "3" 3 ,"5" 5) offset 1,0
set cbtics ("0" -pi,  "{/Symbol p}" 0, "2{/Symbol p}" pi) offset -0.5,0

set xrange[0:40]
set yrange[-5:5]
set cbrange[-pi:pi]

set palette model HSV defined ( 0 0 1 1, 1 1 1 1 )

splot "Datos_HE/GP_GS_fase_dp_10.4.dat"

reset
