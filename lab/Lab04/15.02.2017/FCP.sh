#!/bin/zsh
#File FCP.sh

# controllo del numero di parametri
if test $# -ne 2
then
	echo ERROR: Usage is: $0 [/directory] [number > 0]
	exit 1
fi

# controllo il nome assoluto del primo parametro 
case $1 in
/*)	;;
*/*) 	echo ERROR: $1 non in forma assoluta
	exit 2;;
esac

# controllo il valore del secondo parametro, deve essere strettamente maggiore di zero
if test $2 -le 0
then
	echo ERROR: $2 deve essere maggiore di 0
	exit 3
fi

# chiamo G il nome assoluto della directory e X il numero strettamente maggiore di zero
G=$1
X=$2

PATH=`pwd`:$PATH
export PATH
./FCR.sh $G $X
echo HO FINITO TUTTO
