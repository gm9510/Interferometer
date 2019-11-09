reset

set terminal png enhance font "Times,35" size 1280,480
set output outputname
set pm3d
set view map

unset surface
unset key

#set label "(d)" at 1,3 tc rgb "black" front
set xlabel "t"	offset 0,1
set ylabel "x"			offset 1,0
set cblabel "|{/Symbol Y}|^2"

set xtics ("0" 0, "10" 10, "20" 20, "30" 30 ,"40" 40) offset 0,0.5
set ytics ("-5" -5, "-3" -3, "0" 0, "3" 3 ,"5" 5) offset 1,0
set cbtics ("0" 0, "0.01" 0.01, "0.02" 0.02, "0.03" 0.03, "0.04" 0.04 ) offset -0.5,0
#set cbtics 0.02 offset -0.5,0
#set format cb "%2.0t{/Symbol \327}10^{%L}"

set xrange[0:40]
set yrange[-5:5]
set cbrange[0:0.04]

set palette defined (0 "white",0.05 "light-blue",0.20 "blue",0.40 "magenta", 0.60 "red",0.8 "yellow")

splot datafile

reset
