#!/bin/sh
#File FCR.sh

G=$1

# mi sposto nella gerarchia passata come parametro
cd $G

A=0
B=0
C=0

# Controllo A
case $G in
*/????) A=1;;
*);;
esac

# Controllo B
case $G in
*/?$2?$2) B=1;;
*);;
esac

# Controllo C

files= # variabile per salvare i file che rispettano i criteri

cont=0
# ATTENZIONE 'cont' e' la variabile del testo

for F in *
do
    # controllo che sia un file leggibile
    if test -f $F -a -r $F
    then
        NL=`wc -l < $F` # numero di righe del file
        if test `expr $NL % 2` -eq 0  # controllo che il numero di righe sia pari
        then
            cont=`expr $cont + 1`
            files="$files $F" # aggiungo il file alla lista
        fi
    fi
done

# se ho trovato al meno un file leggibile NON vuoto con numero in linee pari
if test $cont -gt 0
then
    C=1
fi

# Nel caso fossero rispetate tutte le richieste A B C
if test $A -eq 1 -a $B -eq 1 -a $C -eq 1
then
    echo "SONO UN DIRETTORIO VALIDO [`pwd`]"
    echo DEBUG-CHIAMO PARTE C con file $files
    #main $files
fi

# Nel caso fossero rispetate A B ma non C
if test $A -eq 1 -a $B -eq 1 -a $C -eq 0
then
    echo "SONO UN DIRETTORIO CHE RISPECCHIA a E b MA NON c [`pwd`]"
fi

# chiamata ricorsiva per le sotto-directory
for D in *
do
    # se directory traversabile
    if test -d $D -a -x $D
    then
        FCR.sh `pwd`/$D $2
    fi
done