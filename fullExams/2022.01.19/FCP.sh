#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2|3) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 <parametro1> <parametro2> ... <parametro4>"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# Controllo che il primo parametro sia un numero intero strettamente positivo dispari

expr $1 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $1 -lt 0 # controllo che il numero sia positivo
    then
        echo ERROR: $1 non strettamente positivo
        exit 2
    fi
    # Verifico che il parametro sia un numero dispari
    if test `expr $1 % 2` -eq 0 
    then
        echo ERROR: $1 non dispari
        exit 3
    fi
else
    echo ERROR: $1 non numerico
    exit 4
fi

C=$1 # variabile del testo

# Controllo che il secondo parametro sia un numero intero strettamente positivo pari

expr $2 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $2 -lt 0 # controllo che il numero sia positivo
    then
        echo ERROR: $2 non strettamente positivo
        exit 5
    fi
    # Verifico che il parametro sia un numero pari
    if test `expr $2 % 2` -eq 1
    then
        echo ERROR: $2 non pari
        exit 6
    fi
else
    echo ERROR: $2 non numerico
    exit 7
fi

X=$2 # variabile del testo

shift 
shift 

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 8
        fi;;
    *) echo Error: $G non in forma assoluta; exit 9;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
:> /tmp/nomiAssoluti

for G
do
    echo "Fase per $G\n"
    FCR.sh $G $X $C /tmp/nomiAssoluti
done

NumeroFileTrovati=`wc -l < /tmp/nomiAssoluti`

echo "################################################################################"
echo "Ho trovato [$NumeroFileTrovati] file globali che soddisfano le richieste!"
echo "################################################################################"

echo "DEBUG-CHIAMO PARTE C con file `cat /tmp/nomiAssoluti` e il numero [$C]"
#main `cat /tmp/nomiAssoluti` $C

#cancello il file temporaneo
rm /tmp/nomiAssoluti
