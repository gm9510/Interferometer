#! /bin/bash

cd "/home/marin/Codes/Interferometer"

dir=Datos_5PS/
fig=Figuras_5PS/
name=GP_GS_fase_dp_


for num in {0..20}
do

dataname=$dir$name$num.0.dat
figname=$fig$name$num.png

echo " : $dataname"
echo " : $figname"

gnuplot -e "datafile='${dataname}' ; outputname='${figname}'" Fase.plt 

done


exit
