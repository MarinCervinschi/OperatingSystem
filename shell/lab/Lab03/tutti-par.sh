#!/bin/zsh
#File tutti-par.sh
# controllo dell'input
if test $# -lt 1
then
	echo ERROR: il numero di parametri "($#)" è sbagliato
	exit 1
fi

echo Parametri in forma aggregata: $*
echo Parametri uno per volta
for i in $*
do
	echo Parametro = $i
done
