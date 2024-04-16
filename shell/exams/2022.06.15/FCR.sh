#!/bin/sh
#File FCR.sh

G=$1
T=$2

# mi sposto nella gerarchia passata come parametro
cd $G

for F
do
    # se file leggibile
    if test -f $F -a -r $F
    then

        # Se file leggibile e non vuoto
        if test -f "$F" -a -r "$F" -a -s "$F"
        then
            # controllo il contenuto del file, deve contenere 
            # soltanto caratteri minuscoli
            case cat $F in
            [!a-z]) echo File $F non contiene solo caratteri minuscoli;;
            *)      echo `pwd`/$F >> $T
                    echo Trovato file che rispetta le specifiche : `pwd`/$F;;
            esac
        fi
    fi
done

# chiamata ricorsiva per le sotto-directory
for $d in *
do
    if test -d $d -a -x $d
    then
        FCR.sh `pwd`/$d $T
    fi
done