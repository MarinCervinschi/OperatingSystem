#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2)  echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)      echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo $1
case $1 in
?)      echo DEBUG-OK: primo parametro;;
*)      echo $1 non singolo carattere
        exit 2;;
esac
#salviamo il parametro: il nome della variabile da usare era specificato nel testo
C=$1

# sposto il cursore in avanti di uno
shift

for i
do
    case $i in
    /*) if test ! -d $i -o ! -x $i
        then
            echo ERROR: non directory o non traversabile
            exit 3
        fi;;
    *)  echo ERROR: non in forma assoluta
        exit 4;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:PATH
export PATH

# creo un file temporaneo
> /tmp/nomiAssoluti

for i in *
do
    echo fase $i
    FCR.sh $i $C /tmp/nomiAssoluti
done

# stampo il numero totale di file trovati
echo Il numero totale di directory trovate = `wc -l < /tmp/nomiAssoluti`

for i in `cat /tmp/nomiAssoluti`
do
    echo Il nome assoluto della directory = $i
    # chiedo ad Elena se vuole visualizzare il contenuto
    echo Vuoi visualizzare il contenuto? "[Si/No]"
    read answer
    
    case $answer in
    s*|S*|y*|Y*)    echo Il contenuto di $i = 
                    ls -A $i;;
    *)	            echo Non desidera visualizzare il contenuto;;
    esac
done

#cancello il file temporaneo
rm /tmp/nomiAssoluti