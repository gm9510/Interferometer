 
#!/bin/bash

cd "/home/marin/Codes/Interferometer"

make GP_mz_GS
./GP_mz_GS

make Mean
./Mean

dir=Datos_MZ/
fig=Figuras_Dens/
dens=GP_GS_dens_dp_
phas=GP_GS_fase_dp_


echo "Ploting results on $dir"
#plotting probability density
for num in {0..20}
do

dataname=$dir$dens$num.0.dat
figname=$fig$dens$num.png

echo " : $dataname"
echo " : $figname"

gnuplot -e "datafile='${dataname}' ; outputname='${figname}'" Dens.plt 

done


#Plotting Phase
for num in {0..20}
do

dataname=$dir$phas$num.0.dat
figname=$fig$phas$num.png

echo " : $dataname"
echo " : $figname"

gnuplot -e "datafile='${dataname}' ; outputname='${figname}'" Fase.plt 

done
echo "Plot ended"


echo "Ploting results on Figuras/MeanvsDeep.png"
gnuplot Fullmean_plot.plt
echo "Plot ended"

exit
