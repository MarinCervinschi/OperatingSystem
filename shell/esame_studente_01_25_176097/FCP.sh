#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

M=$1 # variabile del testo
# controllo che sia un nome relativo semplice
case $1 in
*/*) echo Errore: $1 non in forma relativa semplice; exit 2;;
*) echo DEBUG-OK: primo parametro corretto;;
esac

# sposto il cursore in avanti di uno così da poter aver accessi alle H gerarchie
shift

# controllo la validità delle gerarchie
for abs
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $abs in
    /*) if test ! -d $abs -o ! -x $abs
        then
            echo Error: $abs non directory o non traversabile
            exit 3
        fi;;
    *) echo Error: $abs non in forma assoluta; exit 4;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo per contare globalmente tutti i file
# che rispettano le specifiche, nome del testo
> /tmp/completeNames

# chiamate ricorsiva per esplorare le gerarchie
for abs
do
    echo fase per $abs
    FCR.sh $abs /tmp/completeNames
done

# dichiaro una varibile somma (nome del testo) per contare 
# il numero toatle di file trovati nella terza posizione
somma=`wc -l < /tmp/completeNames`

# se il numero di file trovati è 0 ,errore
if test $somma -eq 0
then
    echo ERROR: non ho trovati nessun file nella posizione numero 3
    #cancello i file temporaneo
    rm /tmp/completeNames
    exit 5
fi

# se arrivo qua significa che ho trovato almeno un file
# quindi riposto tale numero su std out
echo In tutte le H gerarchie ho trovato $somma file nella posizione numero 3

# creo una nuova directory con il nome M passato come parametro
mkdir $M

# mi sposto nella directory appena creata
cd $M

# leggo il contenuto del file temporaneo composto dai nomi assoluti dei file trovati
for elem in `cat /tmp/completeNames`
do
    # stampa per maggiore chiarezza
    echo Creo un link haedware per il file $elem

    # creo il link hardware
    ln $elem .
done

#cancello i file temporaneo
rm /tmp/completeNames