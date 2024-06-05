#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 </dir> <file1> <file2> .. <fileN>"
        exit 1;;
*)		echo "DEBUG-OK: numero di parametri corretto";;
esac

# controllo la validità della gerarchia
# se in forma assoluta controllo che sia directory e traversabile
case $1 in
/*) if test ! -d $1 -o ! -x $1
    then
        echo "Error: $1 non directory o non traversabile"
        exit 2
    fi;;
*) echo "Error: $1 non in forma assoluta"; exit 3;;
esac

G=$1 # salvo la directory in una variabile (G data dal testo)

shift # elimino il primo parametro

# controllo che i file siano regolari e leggibili
for F in $*
do 
    # controllo che il file sia in forma relativa semplice
    case $F in
    */*) echo Errore: $F non in forma relativa semplice; exit 4;;
    *) ;;
    esac

    if test ! -f $F # controllo solo se file, non serve controllare che sia anche leggibile
    then
        echo "Errore: $F non file regolare"
        exit 5
    fi
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

M=`expr $# / 2` # calcolo il numero di file passati come parametro
# M variabile del testo

# fase per G
echo "DEBUG-> Fase per $G" # anche se solo una fase, faccio una stampa di controllo
FCR.sh $G $M $* # chiamata ricorsiva, dato che ho fatto lo shift, $* contiene solo i file
