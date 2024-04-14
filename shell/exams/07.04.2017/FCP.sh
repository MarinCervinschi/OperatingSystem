#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac


# controllo $1, deve essere il nome relativo semplice F di un file
case $1 in
*/*) echo Errore: $1 non in forma relativa semplice; exit 2;;
*)  if test ! -f $1 # se non file
    then
        echo ERROR: $1 non file
        exit 3
    fi;;
esac
F=$1 # parametro del testo

# sposto il cursore in avanti di uno
shift

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 4
        fi
    *) echo Error: $G non in forma assoluta; exit 5;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
> /tmp/tmp$$

# chiamate ricorsiva per esplorare le gerarchie
for G
do
    echo fase per $G
    FCR.sh $G $F /tmp/tmp$$
done

# stampo il numero totale di file trovati
echo "Ho trovato un totale di `wc -l < /tmp/tmp$$` file"

# leggo il contenuto del file temporaneo composto dai nomi assoluti dei file trovati
for f in `cat /tmp/tmp$$`
do
    echo "Sono $f"
    echo "La prima riga -> `head -1 $f`" # stampo la sua prima riga
    echo "L'ultima riga -> `tail -1 $f`" # stampo la sua ultima riga
done

#cancello il file temporaneo
rm /tmp/tmp$$