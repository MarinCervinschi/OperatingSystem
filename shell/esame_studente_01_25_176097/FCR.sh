#!/bin/sh
#File FCR.sh

# do dei noi ai parametri passati
abs=$1
T=$2

# mi sposto nella gerarchia passata come parametro
cd $abs

# variabile utile per identificare la posizione di un file all'interno 
# di una directory
count=1

# varibile per controllare se ho trovato il file o no
trovato=0

# itero la directory corrente, elem variabile del testo
for elem in *
do
    # se mi trovo nella posizione numero 3
    if test $count -eq 3
    then
        # aggiungo il nome assoluto del file trovato nel file temporaneo per tenere il conto
        echo `pwd`/$elem >> $T
        trovato=1 # ho trovato un file
    fi
    # se file continuo il conteggio
    if test -f $elem
    then
        count=`expr $count + 1`
    fi
done

# se non esiste un file nella posizione numero 3
if test $trovato -eq 0
then
    echo "Nella directory `pwd` non ci sono file nella posizione numero 3"
fi

# chiamata ricorsiva per le sotto-directory
for elem in *
do
    # se directory traversabile
    if test -d $elem -a -x $elem
    then
        FCR.sh `pwd`/$elem $T
    fi
done