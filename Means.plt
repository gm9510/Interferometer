reset

set terminal png enhance font "Times,25"

set output "Figuras_5PS/Dphase2.png"

unset key
set xlabel "Deep"
set ylabel "Phase Shift"

set yrange[0:2.35]
set ytics("3{/Symbol p}/4" 2.35,"{/Symbol p}/4" 0.7853, "{/Symbol p}/2" pi/2., "0" 0)

plot "Datos/GP_GS_mfull.dat" with linespoints

unset term 
unset output

reset

