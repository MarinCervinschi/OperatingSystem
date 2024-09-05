#!/bin/sh
#File FCR.sh

G=$1
H=$2
M=$3

# mi sposto nella gerarchia passata come parametro
cd $G

cont=0  # per contare i file che soddisfano la specifica
# cont variabile del testo

files= # variabile per salvare i file che rispettano i criteri

for F in * # F variabile del testo
do
    # controllo che sia un file leggibile
    if test -f $F -a -r $F
    then
        case $F in # il nome del file deve essere di esattamente due caratteri
        ??)
            NL=`wc -l < $F` 
            # numero di righe del file
            if test $NL -eq $M # controllo che il numero di linee sia uguale a M
            then
                files="$files $F" # aggiungo il file alla lista
                cont=`expr $cont + 1` # incremento il contatore dei file trovati
            fi;;
        *);;
        esac
    fi
done

# cotrollo se il numero dei file trovati e' H < cont <= 2
if test $cont -lt $H -a $cont -ge 2
then
    echo DIRETTORIO VALIDO `pwd`
    echo DEBUG-CHIAMO PARTE C con file $files e il numero M=[$M]
    #main $files $M
fi

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d G -a -x G
    then
        FCR.sh `pwd`/G $H $M
    fi
done
