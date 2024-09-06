#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2|3) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo la validità della gerarchia
case $1 in
/*) if test ! -d $1 -o ! -x $1 # in questo caso e' in forma assoluta
    then    # controllo se directory traversabile
        echo Error: $1 non directory o non traversabile
        exit 2
    fi;;
*) echo Error: $1 non in forma assoluta; exit 3;;
esac
G=$1 # G variabile del testo

expr $2 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $2 -le 0 # controllo che il numero sia positivo
    then
        echo ERROR: $2 non strettamente positivo
        exit 4
    fi
else
    echo ERROR: $2 non numerico
    exit 5
fi
L=$2 # L variabile del testo

shift
shift

# sposto il cursore in avanti di due, per avere solo i singoli caratteri da controllare

# verifico se gli altri Q parametri siano singoli caratteri
for i
do
    case $i in
    ?)	;; # in questo caso e' singolo carattere
    *)	echo $i non singolo carattere; exit 6;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH


# creo un file temporaneo
:> /tmp/nomiAssoluti

# chiamate ricorsiva per esplorare le gerarchie
FCR.sh $G $L /tmp/nomiAssoluti $*

echo "Nella gerarchia [$G] ho trovato [`wc -l < /tmp/nomiAssoluti`] file"

# leggo il contenuto del file temporaneo composto dai nomi assoluti dei file trovati
for F in `cat /tmp/nomiAssoluti`
do
    echo "DEBUG-CHIAMO PARTE C con file [$F] il numero [$L] e i caratteri [$*]"
    main $F $L $*
done

#cancello il file temporaneo
rm /tmp/nomiAssoluti