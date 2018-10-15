#!/bin/bash
outputDir="sprawko"

startFromLine=3

dgridset="100,100"
terminalopt="set terminal pdf size 12, 9"
terminalopt="set terminal png"
fileextension=".png"

#otheroptions='set border 10; set hidden3d; set xtics add ("0.0" 0.1); set ytics add ("0.0" 0.1); set ztics add ("0.0" 0.1);'
otheroptions='set border 10; set xtics add ("0.0" 0.1); set ytics add ("0.0" 0.1);'
otheroptions=""
splotOtherParams="with lines notitle"


mkdir -p "$outputDir"

x="$2"
y="$3"

echo $x

if [ $x != $y ]; then
	if [ $x == "1" ]; then	
		parametrx="Częstotliwość [Hz]";
	fi
	if [ $x == "2" ]; then
		parametrx="Temperatura [°C]";
	fi

	#parametrx=$(cat "$1" | sed '3q;d' |  sed 's/Ohms/Ω/g' | tr '\t' '\n' | sed 's/^ *//' | sed "$x""q;d")
	parametry=$(cat "$1" | sed '3q;d' |  sed 's/Ohms/Ω/g' | tr '\t' '\n' | sed 's/^ *//' | sed "$y""q;d")
	
	echo "$parametrx, $parametry"

	title="Wykres $parametrx od $parametry";

	logset=""
	trma1="
	$terminalopt;
	set output \"$outputDir/$1_$parametrx""_$parametry""$fileextension\";
	set title \"$title\";
	$otheroptions;
	set xlabel \"$parametrx\";
	set ylabel \"$parametry\";
	$logset;
	plot \"$1\" every ::$startFromLine using $x:$y $splotOtherParams;"
	
	#echo "$trma1"
	gnuplot -e "$trma1"
	

	logset="set logscale x"

	trma1="
	$terminalopt;
	set output \"$outputDir/$1""$parametrx""_$parametry""_logscale""_$parametrx""$fileextension\";
	set title \"$title\";
	$otheroptions;
	set xlabel \"$parametrx\";
	set ylabel \"$parametry\";
	$logset;
	plot \"$1\" every ::$startFromLine using $x:$y $splotOtherParams;"
	
	#echo "$trma1"
	gnuplot -e "$trma1"
	
	logset="set logscale y"

	trma1="
	$terminalopt;
	set output \"$outputDir/$1_$parametrx""_$parametry""_logscale""_$parametry""$fileextension\";
	set title \"$title\";
	$otheroptions;
	set xlabel \"$parametrx\";
	set ylabel \"$parametry\";
	$logset;
	plot \"$1\" every ::$startFromLine using $x:$y $splotOtherParams;"
	
	#echo "$trma1"
	gnuplot -e "$trma1"
	
	logset="set logscale x; set logscale y"

	trma1="
	$terminalopt;
	set output \"$outputDir/$1_$parametrx""_$parametry""_logarithimc_""$fileextension\";
	set title \"$title\";
	$otheroptions;
	set xlabel \"$parametrx\";
	set ylabel \"$parametry\";
	$logset;
	plot \"$1\" every ::$startFromLine using $x:$y $splotOtherParams;"
	
	#echo "$trma1"
	gnuplot -e "$trma1"
	


fi

sync

