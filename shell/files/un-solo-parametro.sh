#!/bin/zsh
case $# in

1)	case $1 in
	/*) echo Il percorso di $1 è assoluto.;;
	*/*) echo Il persorso di $1 è relativo.;;
	*)echo Il persorso di $1 è semplice.;;
	esac;;
*) echo $# non è il numero di parametri giusto
   exit 1;;
esac
