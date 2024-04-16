#!/bin/sh
#File FCR.sh

G=$1
X=$2

# mi sposto nella gerarchia passata come parametro
cd $G

# variabile per tenere traccia dei file trovati per poi passarli alla parte c
files=

# variabile utile per sapere se un file si trova in una posizione pari o dispari
count=0
for F in *
do
    # se file leggibile
    if test -f $F -a -r $F
    then
        NR=`wc -l < $F` # conto il numero di righe
        if test $NR -eq $X
        then
            # se il file si trova in una posizione dispari procedi
            if test `expr $count % 2` -ne 0
            then
                echo `pwd`/$F # stampo il nome assoluto del file trovato
                trovato=1
                files="$files $F"
            fi
        fi
    fi
    count=`expr $count + 1`
done

# se files non è vuoto significa che ho trovato almeno un file buono e 
# quindi passo alla parte c
if test "$files"
then
    echo main.c $files
fi

# chiamata ricorsiva per le sotto-directory
for D in *
do
    if test -d $D -a -x $D
    then
        FCR.sh `pwd`/$D $X
    fi
done