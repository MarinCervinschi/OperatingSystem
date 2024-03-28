#!/bin/zsh
#File primo-par.sh

# controllo il numero di parametri sia diverso da 0
if test $# -lt 1
then
	echo ERROR: voglio almeno un parametro
	exit 1
fi

FIRST=$1        #salviamo il primo parametro
shift           #e quindi lo eliminiamo dalla lista dei parametri

#stampiamo il primo parametro e la lista degli altri parametri (escluso il primo)
echo Primo parametro = $FIRST
echo Lista parametri escluso primo = $*
