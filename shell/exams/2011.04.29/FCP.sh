#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) echo ERROR: numero di paramtri non accettabile
     exit 1;;
*)echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo il primo parametro
case $1 in
/*) echo DEBUG-OK: file assoluto;;
*) echo ERROR: non in forma assoluta; exit 2;;
esac
G=$1 # nome del testo

# controllo del secondo parametro
case $2 in
*/*) echo Errore: $2 non in forma relativa semplice; exit 3;;
*)  if test ! -f $2 
    then
        echo ERROR: non file
        exit 4
    fi;;
esac
F=$2 # nome del testo

# controllo il terzo parametro
expr $3 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $3 -lt 0 # controllo che il numero sia positivo
    then
        echo ERROR: $3 non strettamente positivo
        exit 5
    fi
else
    echo ERROR: $3 non numerico
    exit 6
fi
N=$3 # nome del testo

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
> /tmp/tmp$$


FCR.sh $G $F A /tmp/tmp$$

# conto i file trovati
NF`wc -l < /tmp/tmp$$`

echo La gerarchia $G ha $NF file giusti

if test $NF -lt $N
then
    # fase B
    FCR.sh $G $F B

    # fase C
    > /tmp/tmp$$ # azzero il file
    FCR.sh $G $F A /tmp/tmp$$

    # conto i file trovati
    NF`wc -l < /tmp/tmp$$`
    echo La gerarchia $G ha $NF file giusti
fi

#cancello il file temporaneo
rm /tmp/tmp$$













































