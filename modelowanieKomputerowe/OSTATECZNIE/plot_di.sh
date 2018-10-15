#!/bin/bash

diroutput="pikt"

mkdir -p "$diroutput"

dodatkowe='set style line 5 lt rgb "blue" lw 1 pt 1 ps 3;
set style line 6 lt rgb "green" lw 1 pt 1 ps 3;'
opt="with lines ls 5"

# Rysuje RDF teoretyczne i praktyczne
#| grep -o '[0-9]\+\.[0-9]\+'
#tmp_a=$(cat dane_gestosc*.dat | grep 'RDF theor: ' | awk '{print $3}')
#tmp_b=$(cat dane_gestosc*.dat | grep 'Max peak: ' | awk '{print $3}')

tmp_a=$(cat dane_gestosc*.dat | grep 'RDF theor: ' | grep -o '[0-9]\+\.[0-9]\+')
tmp_b=$(cat dane_gestosc*.dat | grep 'Max peak: ' | grep -o '[0-9]\+\.[0-9]\+')

tmp_data_len=$(echo -e "$tmp_a" | wc -l)

array_a=(${tmp_a//'\n'/ })
array_b=(${tmp_b//'\n'/ })
array_c=""
for x in "${!array_a[@]}"
do
	tmpx=$(bc <<< "scale=2; $x/10 + 0.1")
	tmp=$(echo -e "$tmpx\t${array_a[x]}\t${array_b[x]}")
    array_c="$array_c$tmp\n"
done

tymczasowy_plik='.tmp_lol_hahaxDsmieszny_piesek.dat'

echo -e "$array_c" > "$tymczasowy_plik"

nazwa="RDF_gestosc.png"
#opt="with lp ps 3"
opt1="with linespoints ls 5"
opt2="with linespoints ls 6"
gplot="
set term png;
set output \"$diroutput/$nazwa\";
set ylabel \"g\";
set xlabel \"gęstość\";
set datafile separator \"\t\";
$dodatkowe;
set grid;
plot \"$tymczasowy_plik\" using 1:3 $opt1 title \"Praktyczne\",
	 \"$tymczasowy_plik\" using 1:2 $opt2 title \"Teoretyczne\";"

echo -e "$gplot"

gnuplot -e "$gplot"

# Rysuje zaleznosc cisnienia "Boublika" od gesotsci

tmp_a=$(cat dane_gestosc*.dat | grep 'Pressure from state space Boublik: 	' | grep -o '[0-9]\+\.[0-9]\+')

tmp_data_len=$(echo -e "$tmp_a" | wc -l)

array_a=(${tmp_a//'\n'/ })
array_c=""
for x in "${!array_a[@]}"
do
	tmpx=$(bc <<< "scale=2; $x/10 + 0.1")
	tmp=$(echo -e "$tmpx\t${array_a[x]}")
    array_c="$array_c$tmp\n"
done

echo -e "$array_c" > "$tymczasowy_plik"

nazwa="cisnienie_gestosc.png"
#opt="with lp ps 3"
opt="with linespoints ls 5"
gplot="
set term png;
set output \"$diroutput/$nazwa\";
set ylabel \"P\";
set xlabel \"gęstość\";
set datafile separator \"\t\";
$dodatkowe;
set grid;
plot \"$tymczasowy_plik\" using 1:2 $opt notitle;"

echo -e "$gplot"

gnuplot -e "$gplot"

# Rysuje zaleznosc dyfuzji od gesotsci

tmp_a=$(cat dane_gestosc*.dat | grep 'Diffusivity: 	' | grep -o '[0-9]\+\.[0-9]\+')

tmp_data_len=$(echo -e "$tmp_a" | wc -l)

array_a=(${tmp_a//'\n'/ })
array_c=""
for x in "${!array_a[@]}"
do
	tmpx=$(bc <<< "scale=2; $x/10 + 0.1")
	tmp=$(echo -e "$tmpx\t${array_a[x]}")
    array_c="$array_c$tmp\n"
done

echo -e "$array_c" > "$tymczasowy_plik"

nazwa="dyfuzja_gestosc.png"
#opt="with lp ps 3"
opt="with linespoints ls 5"
gplot="
set term png;
set output \"$diroutput/$nazwa\";
set ylabel \"D\";
set xlabel \"gęstość\";
set datafile separator \"\t\";
$dodatkowe;
set grid;
plot \"$tymczasowy_plik\" using 1:2 $opt notitle;"

echo -e "$gplot"

gnuplot -e "$gplot"

