#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0)  echo ERROR: numero di paramtri non accettabile
    exit 1;;
*)	echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo $1, deve essere una directory traversabile
case $1 in
/*) if test ! -d $1 -o ! -x $1
    then
        echo ERROR: non directory o non traversabile
        exit 2
    fi;;
*) echo ERROR: non in forma assoluta; exit 3;;
esac
G=$1

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
> /tmp/tmp$$

LIVELLO=0

# fase A
FCR.sh $G $LIVELLO /tmp/tmp$$ A 0

# conto i livelli trovati nella gerarchia
NL=`wc -l < /tmp/tmp$$`
# stampo il numero di file trovati
echo "La gerarchia $G ha $NL livelli"

# fase B

echo Dammi un numero pari compreso fra 1 e $NL
read num

# controllo se numero
expr $num + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    echo DEBUG-OK: $num è numerico
else
    echo ERROR: $num non numerico
    rm /tmp/tmp$$
    exit 4
fi

# controllo se pari
if test `expr $num % 2` -ne 0
then
    echo ERROR: $num non pari
    rm /tmp/tmp$$
    exit 5
fi

# controllo se 1 <= num <= num livelli
if test $num -lt 1 -o $num -gt $NL
then
    echo ERROR: il numero deve essere compreso tra 1 e $NL
    rm /tmp/tmp$$
    exit 6
fi

# chiamata ricorsiva per la fase B
FCR.sh $G $LIVELLO /tmp/tmp$$ B $num

#cancello il file temporaneo
rm /tmp/tmp$$