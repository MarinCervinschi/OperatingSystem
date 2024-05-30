#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2|3) 	echo "ERROR: numero di paramtri [$#] non accettabile"
            echo "Usage: $0 directory (num > 0) char char ..."
            exit 1;;
*)		    echo DEBUG-OK: numero di parametri corretto;;
esac


# se il primo parametro e' in forma assoluta controllo che sia directory e traversabile
case $1 in
/*) if test ! -d $1 -o ! -x $1
    then
        echo "Error: [$1] non directory o non traversabile"
        exit 2
    fi
    echo "DEBUG-OK: [$1] e' directory e traversabile";;
*) echo "Error: [$1] non in forma assoluta"; exit 3;;
esac

# salvo il nome della directory in una variabile (G specificata dal testo)
G=$1

# controllo che il secondo parametro sia un numero > 0
expr $2 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $2 -le 0 # controllo che il numero sia positivo
    then
        echo "ERROR: [$2] non strettamente positivo"
        exit 4
    fi
else
    echo "ERROR: [$2] non numerico"
    exit 5
fi

# salvo il numero in una variabile (L specificata dal testo)
L=$2

# sposto il cursore di lettura dei parametri
shift
shift

# controllo che i successivi parametri siano caratteri
for i in $*
do 
    case $i in
    ?)	echo "DEBUG-OK: carattere [$i]";;
    *)	echo "[$i] non singolo carattere"; exit 6;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo (nome del testo)
:> /tmp/nomiAssoluti

# chiamo la funzione ricorsiva passando i parametri
./FCR.sh $G $L /tmp/nomiAssoluti $*


# stampo il numero di file che soddisfa le specifiche
echo Il numero di file che soddisfa le specifiche e\' `wc -l < /tmp/nomiAssoluti`

for F in `cat /tmp/nomiAssoluti`
do
	echo "DEBUG-stiamo per invocare la parte C con file [$F] lunghezza [$L] e caratteri [$*]"
	./13Lug22 $F $L $*
done

#cancello il file temporaneo
rm /tmp/nomiAssoluti