#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

counter=1
params=

for i
do
    if test $counter -ne $# # serve per non considerare l'ultimo parametro
    then
        # controllo la validità della gerarchia
        # se in forma assoluta controllo che sia directory e traversabile
        case $i in
        /*) if test ! -d $i -o ! -x $i
            then
                echo "Error: $i non directory o non traversabile"
                exit 2
            fi;;
        *) echo "Error: $i non in forma assoluta"; exit 3;;
        esac
        params="$params $i" # se i controlli sono andati bene memorizzo il nome nella lista params
    else
        case $i in
        ?)	echo DEBUG-OK: ultimo parametro;;
        *)	echo $i non singolo carattere; exit 4;;
        esac
        C=$i # se i controlli sono andati bene salvo l'ultimo parametro
        # ATTENZIONE 'C' e' la variabile del testo
    fi
    counter=`expr $counter + 1` #incremento il contatore del ciclo sui parametri
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

for G in $params
do
    echo fase per $G
    echo "**************************************"
    # invoco il file ricorsivo
    FCR.sh $G $C
done