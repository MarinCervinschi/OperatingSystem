#!/bin/zsh
#File ultimo-par.sh

# controllo il numero di parametri sia diverso da 0
if test $# -lt 1
then
	echo ERROR: voglio almeno un parametro
	exit 1
fi

LAST=
LIST=

count=0
for i
do
	count=`expr $count + 1`
	if test $count -ne $#
	then
		LIST="$LIST $i"
	else
		LAST=$i
	fi
done

echo Ultimo parametro = $LAST
echo Lista parametri escluso ultimo = $LIST
