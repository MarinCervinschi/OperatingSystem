#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2|3) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

counter=1
params=
for i
do
    if test $counter -lt `expr $# - 1` # serve per non considerare gli ultimi due parametri
    then
        # controlla lavalidita' delle prime Q gerarchie
        # se sono in forma assoluta controllo che siano directory e traversabile
        case $i in
        /*) if test ! -d $i -o ! -x $i
            then
                echo Error: $i non directory o non traversabile
                exit 2
            fi;;
        *) echo Error: $i non in forma assoluta; exit 3;;
        esac
        params="$params $i" # se i controlli sono andati bene memorizzo il nome nella lista params
    else

        if test $counter -eq `expr $# - 1` # serve per non considerare l'ultimo parametro
        then
            # controllo che il punultimo parametro sia un numero strettamento positivo
            expr $i + 0  > /dev/null 2>&1
            N1=$?
            if test $N1 -ne 2 -a $N1 -ne 3
            then # in questo caso è certamente numerico
                if test $i -le 0 # controllo che il numero sia positivo
                then
                    echo ERROR: $i non strettamente positivo
                    exit 4
                fi
            else
                echo ERROR: $i non numerico
                exit 5
            fi
            H=$i # se i controlli sono andati bene salvo salvo il penultimo parametro
            # H variabile del testo
        else
            expr $i + 0  > /dev/null 2>&1
            N1=$?
            if test $N1 -ne 2 -a $N1 -ne 3
            then # in questo caso è certamente numerico
                if test $i -le 0 # controllo che il numero sia positivo
                then
                    echo ERROR: $i non strettamente positivo
                    exit 6
                fi
            else
                echo ERROR: $i non numerico
                exit 7
            fi
            M=$i # se i controlli sono andati bene salvo l'ultimo parametro
            # M variabile del testo
        fi
    fi
    counter=`expr $counter + 1` #incremento il contatore del ciclo sui parametri
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# chiamate ricorsiva per esplorare le gerarchie
for G in $params # G nome del testo
do
    echo "## fase per $G\n"
    FCR.sh $G $H $M 
done
