#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 <parametro1> <parametro2> ..."
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

expr $1 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $1 -le 0 # controllo che il numero sia positivo
    then
        echo "ERROR: $1 non strettamente positivo"
        exit 2
    fi

    if test $1 -ge 20 # controllo che il numero sia strettamente minore di 20
    then
        echo "ERROR: $1 non strettamente minore di 20"
        exit 3
    fi
else
    echo ERROR: $1 non numerico
    exit 4
fi

X=$1
# ATTENZIONE 'X' e' la variabile del testo

shift # sposto il cursore in avanti di uno
# adesso in $* ho solo le Q gerarchie

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 5
        fi;;
    *) echo Error: $G non in forma assoluta; exit 6;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
:> /tmp/nomiAssoluti # ATTENZIONE '/tmp/nomiAssoluti' e' la variabile del test

# chiamate ricorsiva per esplorare le gerarchie
for G # ATTENZIONE 'G' e' la variabile del testo
do
    echo fase per $G
    echo "************************************"
    FCR.sh $G $X /tmp/nomiAssoluti
done

N=`wc -l < /tmp/nomiAssoluti`
# ATTENZIONE 'N' e' la variabile del testo

echo "----------------------------------------------------"
echo In tutte le Q fasi sono stati trovati $N file

params= # variabile per salvare i file trovati intervalati dal loro numero di linee
# che verra' passato alla parte C

# leggo il contenuto del file temporaneo composto dai nomi assoluti dei file trovati
for f in `cat /tmp/nomiAssoluti`
do
    NL=`wc -l < $f | tr -d ' '` # salvo il numero di linee del file corrente
    params="$params $f $NL" # aggiorno la lista con il nuovo file e il suo numero di linee
done

echo "DEBUG-CHIAMO PARTE C con [$params]"
#main $params

#cancello il file temporaneo
rm /tmp/nomiAssoluti