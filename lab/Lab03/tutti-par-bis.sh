#!/bin/zsh
#File tutti-par-bis.sh
# controllo dell'input
if test $# -lt 1
then
	echo ERROR: il numero di parametri "($#)" è sbagliato
	exit 1
fi

echo Parametri in forma aggregata: $*
echo Parametri uno per volta
j=1
for i
do
	echo Parametro \$$j = $i
	j=`expr $j + 1`
done
