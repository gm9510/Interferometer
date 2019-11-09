#Other fonts: Helvetica (gnuplot default font), Romans 

reset
set terminal postscript eps enhanced color "Times,25"
set output "SPIE_figures/Momentum_densityplot_L60M20_glt0.eps"
set pm3d
set view map
unset surface
unset key
set label "a" at -0.45,7 tc rgb "black" front
set xlabel "g"
set ylabel "k"
#set title "Magnon momentum-density-plot g<0"
#set palette rgbformulae 21,22,23
#set palette color
#set palette model RGB
#set palette defined
#set palette defined (0 0 0 0, 1 0 0 1, 3 0 1 0, 4 1 0 0, 6 1 1 1)
set palette defined ( 0 "black", 1.72 "white",1.8 "yellow", 2 "orange", 3 "red" ) 
#set cbrange[0:1.9]
set yrange[0.1:2*pi]
set xrange[-0.9:0]
set ytics ("0" 0.1, "{/Symbol p}/2" pi/2., "{/Symbol p}" pi, "3{/Symbol p}/2" 3.*pi/2.,"2{/Symbol p}" 2.*pi)
splot "NEW_L60M20/nk-g_3Dshifted_L60M20_g.dat" u 1:2:3  w lp
unset output
unset terminal


reset
set terminal postscript eps enhanced color "Times,25"
set output "SPIE_figures/Momentum_densityplot_L60M20_ggt0.eps"
set pm3d
set view map
unset surface
unset key
set label "b" at 0.45,7 tc rgb "black" front
set xlabel "g"
set ylabel "k"
#set title "Magnon momentum-density-plot g>0"
#set palette rgbformulae 21,22,23
#set palette color
#set palette model RGB
#set palette defined
#set palette defined (0 0 0 0, 1 0 0 1, 3 0 1 0, 4 1 0 0, 6 1 1 1)
#set palette defined (0 "black", 1.72 "white",1.8 "yellow", 2 "orange", 10"red" ) 
set palette defined (0 "black", 1.72 "white", 1.8 "yellow", 2 "orange",  10"red",60"blue") 

set cbrange[0:60]
set yrange[0.1:2*pi]
set xrange[0.0:0.9]
set ytics ("0" 0.1, "{/Symbol p}/2" pi/2., "{/Symbol p}" pi, "3{/Symbol p}/2" 3.*pi/2.,"2{/Symbol p}" 2.*pi)
splot "NEW_L60M20/nk-g_3Dshifted_L60M20_g.dat" u 1:2:3  w lp
unset output
unset terminal

reset
set terminal postscript eps enhanced color "Times,25"
set output "SPIE_figures/CentralPoint_momentum_vs_g_L60M20.eps"
set xlabel "g"
set ylabel "n_k"
set xrange[-0.9:0.9]
unset key
plot "NEW_L60M20/nk-g_L60M20_g.dat" u 1:2 w lp pt 7 ps 1.5
unset output
unset terminal

reset
set terminal postscript eps enhanced color "Times,25"
set output "SPIE_figures/Total_momentum-density_vs_g_L60M20.eps"
set xlabel "g"
set xrange[-0.9:0.9]
set key top left
plot "NEW_L60M20/nk-g_L60M20_g.dat" u 1:($3/60) t "n_k" w lp pt 7 ps 1.4, "" u 1:($5/60) t "n" w lp pt 4 ps 1.6 lt 3
unset output
unset terminal


