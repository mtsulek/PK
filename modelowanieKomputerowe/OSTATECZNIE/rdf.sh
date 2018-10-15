#!/bin/bash

dane="$(tail -n 1 $1 | tr ' ' '\n' | tr ';' ' ')"

tmp_nazwa_pliku='.tmp_pliczek.hasz_ololololloo.dat'

tail -n 1 $1 | tr ' ' '\n' | tr ';' ' ' > $tmp_nazwa_pliku

gplot="set key autotitle columnhead; set datafile separator '\t';
plot \"$1\" using $2:$3 with lines;
pause -1;"

#plot "< echo '09-13-2010,2263.80 09-14-2010,2500' | tr ' ' '\n' | tr ',' ' '" using 1:2 with lines

gplot="
set xlabel \"r/n\";
set ylabel \"g(r)\";
plot \"$tmp_nazwa_pliku\" using 1:2 with lines notitle; pause -1;"

echo "$gplot"

gnuplot -e "$gplot"
