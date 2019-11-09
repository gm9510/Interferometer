#! /bin/bash

cd "/home/marin/Codes/Interferometer"

dir=Datos_5PS/
fig=Figuras_5PS/
dens=GP_GS_dens_dp_


for num in {0..20}
do

dataname=$dir$dens$num.0.dat
figname=$fig$dens$num.png

echo " : $dataname"
echo " : $figname"
#Ploting Probability Density.
gnuplot -e "datafile='${dataname}' ; outputname='${figname}'" Dens.plt 

done

exit
