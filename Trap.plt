
reset

set term png size 2560,720 transparent
set output "Figuras/Trap_HC_3.png"
set pm3d
set view map
unset surface
#unset colorbox
#set xlabel "Time" font "Liberation Sans,50" offset 0,-3
#set ylabel "Space" font "Liberation Sans,50" offset -3,0
#set cblabel "Energy" font "Liberation Sans,50" offset 7,0

#set palette defined (0 "black",3 "dark-blue",10 "blue",18 "dark-green",50 "white")
#set palette rgb 7,5,15

set xtics font "Liberation Sans,65" offset -2,-2
set ytics font "Liberation Sans,65" offset 0,-1
set cbtics font "Liberation Sans,65" offset 3,0

set xrange[0:40]
set yrange[-5:5]
set cbrange[0:20]
unset key

splot "Datos/GP_GS_Trap.dat" 
unset output
unset term

reset



