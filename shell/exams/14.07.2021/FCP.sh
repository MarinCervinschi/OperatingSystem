#!/bin/zsh
#File FCP.sh

# controllo il numero di parametri >= 4 
if test $# -lt 4
then
    echo Usage is: $0 <ger1> <ger2> <int> <int>
    exit 1
fi

# definisco variabile per tenere traccia del indice
num=1

# definisco una variabile per tenere traccia delle prime Q gerarchie
params=0

# itero sui parametri passati e controllo
for i 
do 
    if test $num -lt `expr $# -1`
    then
        # se in forma assoluta controllo se directory e traversabile
        case $i in 
        */)     if test ! -d $i -a ! -x $i
                then
                    echo Error: non directory o non traversabile
                    exit 2
                fi;;
        *)      echo Error: non in forma assoluta
                exit 3;; 
        esac
        # salvo la gerarchia
        params="$params $i"
    else
        # abbiamo trovato gli ultimi due parametri
        # controllo se sono numeri interi > 0
        case $i in 
        *[!0-9]*)   echo $i non numerico o non positivo
                    exit 4;;
        *)          if test $i -eq 0
                    then 
                        echo Errore: parametro $i uguale a zero
                        exit 5;;
                    fi;;
        esac

        # salvo i parametri numerici
        if test $num -eq `expr $# -1`
        then 
            H=$i # come indicato nel testo
        else 
            M=$i # come indicato nel testo
        fi
    fi
    num=`expr $num + 1` # incremento il contatore
done

#settiamo la variabile PATH e la esportiamo
PATH=`pwd`:PATH
export PATH

# iteriamo su ogni gerarchia invocando il file ricorsivo
for G in $params
do
    echo fase per $G
    FCR.sh $G $H $M
done

