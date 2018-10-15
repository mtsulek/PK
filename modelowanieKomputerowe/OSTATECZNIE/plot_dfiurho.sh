#!/bin/bash

diroutput="pikt"

mkdir -p "$diroutput"

dlax=1
dlay=2
parametrx=$(cat 'difu_rho.dat' | sed '1q;d' | tr '\t' '\n' | sed 's/^ *//' | sed "$dlax""q;d")
parametry=$(cat 'difu_rho.dat' | sed '1q;d' | tr '\t' '\n' | sed 's/^ *//' | sed "$dlay""q;d")
nazwa="difu_cisnienie.png"

gplot="
set term png;
set output \"$diroutput/$nazwa\";
set datafile separator \"\t\";
set xlabel \"$parametrx\";
set ylabel \"$parametry\";
plot \"difu_cisnienie.dat\" using $dlax:$dlay with lp notitle"

echo "$gplot"

gnuplot -e "$gplot"
