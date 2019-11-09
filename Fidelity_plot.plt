reset

set terminal png enhance font "Times,35"

set output "Figuras_5PS/Fidelity_dp_10.20.png"

unset key
set xlabel "t"
set ylabel "Fidelity"

set yrange [0:1.1]
#set label "(f)" at 2,0.8 tc rgb "black" front

set xtics 10
unset key
plot "Datos/GP_GS_fid_10.20.dat" with lines lw 6

reset


