#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2|3) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 '/dir' 'numero > 0' 'stringa1' 'stringa2' -opt[.. stringaN]"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo la validità della gerarchia
# se in forma assoluta controllo che sia directory e traversabile
case $1 in
/*) if test ! -d $1 -o ! -x $1
    then
        echo "Error: $1 non directory o non traversabile"
        exit 2
    fi;;
*) echo "Error: $1 non in forma assoluta"; exit 3;;
esac

G=$1 # variabile del testo

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

X=$2 # variabile del testo

shift # tolgo il primo parametro
shift # tolgo il secondo parametro

# controllo che le stringhe siano effettivamente stringhe
for i in $*
do
    case $i in
    */*)	echo "Errore: [$i] non deve contenere il carattere /"
            exit 6;;
    # se sono stringe controllo che siano lunghe almeno due caratteri
    ?)		echo "Error: la stringa [$i] deve contenere almeno due caratteri";;
    esac
done


# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

echo "DEBUG: Inizia la singola fase per la directory $G"
FCR.sh $G $X $* # invoco la parte ricorsiva passando come parametri la gerarchia, il numero e le stringhe
