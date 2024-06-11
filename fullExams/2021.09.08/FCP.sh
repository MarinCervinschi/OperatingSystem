#!/bin/sh
#File FCP.sh


# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 <char> </dir2> </dir2> -opt[.. /dirN]"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo che il primo parametro sia un singolo carattere
case $1 in
?)	echo DEBUG-OK: primo parametro char;;
*)	echo $1 non singolo carattere; exit 2;;
esac

#salviamo il parametro: il nome della variabile da usare era specificato nel testo
C=$1

shift # elimino il primo parametro

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 3
        fi;;
    *) echo Error: $G non in forma assoluta; exit 4;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
:> /tmp/nomiAssoluti

for G
do
    echo "DEBUG: Inizia la fase per la gerarchia [$G]"
    FCR.sh $G $C /tmp/nomiAssoluti
done

cont=`wc -l < /tmp/nomiAssoluti`
echo "Ho trovato $cont directory che rispettano le richieste"

# leggo il contenuto del file temporaneo composto dai nomi assoluti dei file trovati
for i in `cat /tmp/nomiAssoluti`
do
    files= # variabile che mi serve per salvare i file trovati in ogni gerarchia buona per poi passarli alla parte c
    # mi sposta nella cartella
    cd $i
    for F in *
    do
        if test -f $F
        then
            files="$files $F"
        fi
    done
    # inutile uscire dato che i nomi delle gerarchie sono nomi assoluti
    echo DEBUG-CHIAMO PARTE C con file $files
    #main $files
done

#cancello il file temporaneo
rm /tmp/nomiAssoluti