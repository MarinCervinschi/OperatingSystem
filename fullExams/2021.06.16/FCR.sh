#!/bin/sh
#File FCR.sh

G=$1
H=$2
M=$3

# mi sposto nella gerarchia passata come parametro
cd $G

cont=0 # contatore dei file con dimensione maggiore di H
# variabile del testo
# varibile per salvare i nomi dei file trovati
files=

# conto tutti i file che rispettano le condizioni
for F in *
do 
    # controllo che sia un file e che sia leggibile
    if test -f $F -a -r $F
    then
        NR=`wc -l < $F`
        if test $NR -eq $H # controllo che il numero di righe sia uguale a H
        then
            # controllo che il nome sia costituite da esattamente 2 caratteri
            case $F in
            ??)	cont=`expr $cont + 1`
                files="$files $F";; # salvo il nome del file e incremento il contatore
            *)	;;
            esac
        fi
    fi
done

# controllo che il numero di file trovati sia 
if test $cont -lt $M -a $cont -ge 2
then
    echo Sono `pwd` e ho trovato $cont file.
    echo DEBUG-CHIAMO PARTE C con file $files
    #main $files
fi

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d $G -a -x $G
    then
        FCR.sh `pwd`/$G $H $M
    fi
done