#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 </dir> <string1> <string2>"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo che il primo parametro sia una directory in forma assoluta
case $1 in
/*) if test ! -d $1 -o ! -x $1
    then
        echo Error: $1 non directory o non traversabile
        exit 2
    fi;;
*) echo Error: $1 non in forma assoluta; exit 3;;
esac


G=$1 # variabile del testo

# controllo che il secondo parametro sia una stringa
case $2 in
*/*)	echo "Errore: $2 non deve contenere il carattere /"; exit 4;;
esac

# controllo che il terzo parametro sia una stringa
case $3 in
*/*)	echo "Errore: $3 non deve contenere il carattere /"; exit 5;;
esac

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

echo "DEBUG: Inizia la singola fase per la directory $G"
FCR.sh $G $2 $3 # chiamata ricorsiva passando la directory e le due stringhe
