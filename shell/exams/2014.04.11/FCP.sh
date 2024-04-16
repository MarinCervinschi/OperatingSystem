#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1) 	echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 2
        fi
    *) echo Error: $G non in forma assoluta; exit 3;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# variabile che mi aiuta a tenere traccia dei file temporanei creati
n=1

# chiamate ricorsiva per esplorare le gerarchie
for $G
do
    # creo un file temporaneo per la gerarchia Gi
    > /tmp/conta$$-$n
    echo fase per $G
    # chiamata ricorsiva
    FCR.sh $G /tmp/conta$$-$n
    # conto i file trovati per la gerarchia Gi
    fileTrovati=`wc -l < /tmp/conta$$-$n` 
    echo Per la gerarchia $G abbiamo trovato $fileTrovati file
    # incremento n per il file successivo
    n=`expr $n + 1`
done

# imposto di nuovo la variabile a 1 per poter iterare i file creati
n=1
# itero N volte le gerarchie iniziali
for G
do

    # leggo il contenuto del file temporaneo composto dai nomi assoluti dei file trovati
    for $f in `cat /tmp/tmp$$-$n`
    do
        echo Sono in $G e questi sono i miei file:
        echo $f

        echo Dammi un numero X
        read X

        expr $X + 0  > /dev/null 2>&1
        N1=$?
        if test $N1 -ne 2 -a $N1 -ne 3
        then # in questo caso è certamente numerico
            if test $X -lt 0 # controllo che il numero sia positivo
            then
                echo ERROR: $X non strettamente positivo
                continue
            fi
        else
            echo ERROR: $X non numerico
            continue
        fi

        echo Le prime $X righe del file sono:
        head -n $X < $f

    done
    n=`expr $n + 1`
    
done

# reimposto di nuovo n per poter cancellare tutti i file creati
n=1
for G
do
    rm /tmp/conta$$-$n
    n=`expr $n + 1`
done

