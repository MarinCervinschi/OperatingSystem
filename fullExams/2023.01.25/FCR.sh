#!/bin/sh
#File FCR.sh

G=$1 # variabile del testo
E1=$2 # stringa 1
E2=$3 # stringa 2

# mi sposto nella gerarchia passata come parametro
cd $G

cont1=0 # variabile per contare i file con estensione $E1 (variabile del testo)
cont2=0 # variabile per contare i file con estensione $E2 (variabile del testo)

files1= # variabile per salvare i nomi dei file con estensione $E1
files2= # variabile per salvare i nomi dei file con estensione $E2

for F in * # F variabile del testo
do
    # se $F e' un file ed e' leggibile
    if test -f $F -a -r $F
    then
        # controllo se $F ha estensione $E1
        case $F in
        # incremento il contatore dei file con estensione $E1
        *.$E1)  cont1=`expr $cont1 + 1`
                # salvo il nome del file in files1
                files1="$files1 $F";;
        esac
    fi
    # se $F e' un file ed e' leggibile e scrivibile
    if test -f $F -a -r $F -a -w $F
    then
        # controllo se $F ha estensione $E2
        case $F in
        # incremento il contatore dei file con estensione $E2
        *.$E2)  cont2=`expr $cont2 + 1`
                # salvo il nome del file in files2
                files2="$files2 $F";;
        esac
    fi
done

# se ho trovato almeno un file leggibile con estenzione $E1 e almeno un file leggibile e scrivibile con estenzione $E2
if test $cont1 -gt 0 -a $cont2 -gt 0
then
    echo "Sono `pwd` e ho trovato $cont1 file con estensione $E1 e $cont2 file con estensione $E2"
    # per ogni file con estensione $E2
    for f in "$files2"
    do
        # chiamo la parte C passando tutti i file con estensione $E1 e il file con estensione $E2
        echo DEBUG-CHIAMO PARTE C con file $files1 e $f
        #main $files $f
    done
fi

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d $G -a -x $G
    then
        FCR.sh `pwd`/$G $E1 $E2
    fi
done

