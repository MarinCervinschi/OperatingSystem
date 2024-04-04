#!/bin/zsh
#File FCR.sh

cd $1

for i in *
do
    # se directory vai più in profondità
    if test -d $i -a -x $i
    then
        FCR.sh $i $X
        # se il file non ha riportato errori stampo il nome assoluto della directory con i file al suo interno
        res=$?

        if test $res -eq 0
        then
            # aggiungo una direcory trovata globalmente
            echo "1" >> /tmp/temp
            # stampo il risultato 
            echo Il nome assoluto della directory: `pwd`/$i
            echo Tutti i file trovati
            for file in "$i"/*
            do
                echo `pwd`/$i/$file
                echo Linea $2 a partire dalla fine: `tail -n $2 "$file" | head -n 1`
            done
        fi
        exit 1
    else 
        # controllo nel caso sia una file, il numero di righe 
        if test ! -f $i -o ! -r $i
        then 
            exit 2
        else 
            # se file controllo che le linee siano > X
            n=`wc -l < $i`
            if test "$n" -lt "$2"
            then
                exit 3
            fi
        fi
    fi
done