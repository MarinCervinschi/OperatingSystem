#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2|3)    echo ERROR: numero di paramtri non accettabile
            exit 1;;
*)          echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo $1 deve essere W > 0
expr $1 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $1 -le 0 # controllo che il numero sia positivo
    then
        echo ERROR: $1 non strettamente positivo
        exit 2
    fi
else
    echo ERROR: $1 non numerico
    exit 3
fi

# dichiaro la variabile del testo
W=$1

# controllo $2
case $2 in
*/*)	echo Errore: $2 non deve contenere il carattere /
        exit 4;;
esac
S=$2 # nome specificato nel testo

# mi sposto di 2 in avanti
shift
shift

# controllo $3
for i 
do  
    # se in nome assoluto controllo se directory e traversabile
    case $i in
    /*) if test ! -d $i -o ! -x $i
        then
            echo ERROR: non directory o non traversabile
            exit 5
        fi;;
    *)  echo ERROR: non in forma assoluta
        exit 6;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
> /tmp/nomiAssoluti

# chiamata ricorsiva per le Q fasi
for G
do  
    echo fase per $G
    FCR.sh $G $S /tmp/nomiAssoluti
done

N=`wc -l < /tmp/nomiAssoluti`
# stampo il numero totale di dir trovate
echo Il totale di directory trovate = $N

if test $N -ge $W
then
    echo Marin dammi un numero intero compreso fra 1 e $W
    read X

    expr $X + 0  > /dev/null 2>&1
    N1=$?
    if test $N1 -ne 2 -a $N1 -ne 3
    then # in questo caso è certamente numerico
        if test $X -le 0 # controllo che il numero sia positivo
        then
            echo ERROR: $X non strettamente positivo
            #cancello il file temporaneo
            rm /tmp/nomiAssoluti
            exit 7
        fi
    else
        echo ERROR: $X non numerico
        #cancello il file temporaneo
        rm /tmp/nomiAssoluti
        exit 8
    fi
    
    echo il nome assoluto della directory corrispondente a $X =
    #dobbiamo selezionare la linea $X del file temporaneo
    head -$X < /tmp/nomiAssoluti | tail -1
else
    echo Il numero $N non maggiore o uguale ad $W
fi

#cancello il file temporaneo
rm /tmp/nomiAssoluti