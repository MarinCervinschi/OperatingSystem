#!/bin/zsh
case $# in

1)	case $1 in
	/*) echo Il percorso di $1 è assoluto.
		if test -f $1
		then 
			echo Sono un file
		elif test ! -d $1 -a ! -x $1
		then 
			echo Sono una directory traversabile
		else 
			echo Non sono nè un file nè una directory traversabile
		fi;;
	*/*) echo Il persorso di $1 è relativo.;;
	*)echo Il persorso di $1 è semplice.;;
	esac;;
*) echo $# non è il numero di parametri giusto
   exit 1;;
esac
