#!/bin/bash

diroutput="pikt"

mkdir -p "$diroutput"

#dodatkowe='set style line 5 lt rgb "cyan" lw 3 pt 6'
dodatkowe='set style line 5 lt rgb "blue" lw 1 pt 1'
opt="with lines ls 5"

set_xrange=';'
set_yrange='set yrange [0:2.5];'

#dane_gestosc_0_05.dat

#for x in *.dat; do echo "$x" | sed 's/dane_gestosc//g'; done

#$plik="dane_gestosc_0_1.dat"
plik="$1"
pliknazwa=$(echo "$plik" | sed 's/dane_gestosc//g' | sed 's/.dat//g')
#pliknazwa="_0_1.png"

dlax=1
dlay=3
parametrx=$(cat "$plik" | sed '1q;d' | tr '\t' '\n' | sed 's/^ *//' | sed "$dlax""q;d")
parametry=$(cat "$plik" | sed '1q;d' | tr '\t' '\n' | sed 's/^ *//' | sed "$dlay""q;d")
nazwa="VAF_t$pliknazwa.png"

gplot="
set term png;
set output \"$diroutput/$nazwa\";
set datafile separator \"\t\";
set xlabel \"$parametrx\";
set ylabel \"$parametry\";
set grid;
$dodatkowe;
plot \"$plik\" using $dlax:$dlay $opt notitle;"

echo "$gplot"

gnuplot -e "$gplot"

dlax=1
dlay=5
parametrx=$(cat "$plik" | sed '1q;d' | tr '\t' '\n' | sed 's/^ *//' | sed "$dlax""q;d")
parametry=$(cat "$plik" | sed '1q;d' | tr '\t' '\n' | sed 's/^ *//' | sed "$dlay""q;d")
nazwa="diffusity_t$pliknazwa.png"

parametry

gplot="
set term png;
set output \"$diroutput/$nazwa\";
set datafile separator \"\t\";
set xlabel \"$parametrx\";
set ylabel \"$parametry\";
set grid;
$dodatkowe;
plot \"$plik\" using $dlax:$dlay $opt notitle;"

echo "$gplot"

gnuplot -e "$gplot"


nazwa="rdf_t$pliknazwa.png"
dane="$(tail -n 1 $plik  | tr ' ' '\n' | tr ';' ' ')"

tmp_nazwa_pliku="rdf_t$pliknazwa.dat"

#tail -n 1 $plik | tr ' ' '\n' | tr ';' ' ' | tr 'inf' '0' > "$tmp_nazwa_pliku"
tail -n 1 $plik | tr ',' '\t' | tr ';' '\n' | tr 'inf' '0' > "$tmp_nazwa_pliku"


gplot="
set term png;
set output \"$diroutput/$nazwa\";
set xlabel \"r/σ\";
set ylabel \"g(r)\";
set grid;
$set_xrange;
$set_yrange;
$dodatkowe;
plot \"$tmp_nazwa_pliku\" using 1:2 $opt notitle;"

echo "$gplot"

gnuplot -e "$gplot"

