#!/bin/bash

cd "/home/gmarin/Codes/Interferometer"

make Itime_Msearch_Old
./Itime_Msearch

make Fidelity2_Old
./Fidelity2

echo "Plot Fideleity"
gnuplot Fidelity_plot.plt


exit


