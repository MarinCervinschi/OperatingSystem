#!/bin/zsh
#File FCP.sh

# controllo sul numero di parametri 
if test $# -lt 2
then
    echo ERROR: $# deve essere maggiore o uguale a 2
    exit 1
fi

# definisco una variabile per salvare l'ultimo parametro
X=
# defininsco una variabile per identificare l'ultimo parametro
count=0
for i
do 
    # controllo i primi N parametri
    count=`expr $count + 1`
    if test $count -ne $#
    then
        #controllo che sia in forma assoluta
        case $i in
        # se in forma assoluta controllo che sia directory e traversabile
        /*) if test ! -d $i -a ! -x $i
            then
                echo ERROR: $i non directory o non attraversabile
                exit 2
            fi;;
        *)  echo ERROR: non in forma assoluta
            exit 3;;
        esac
    else 
        # controllo l'ultimo che deve essere un numero
        expr $i + 0 > /dev/null 2>&1
        N1=$?

        if test $N1 -ne 2 -a $N1 -ne 3 
        then
        	echo numerico $i #siamo sicuri che numerico
        	if test $i -le 0
            then
        		echo $i non strettamente positivo
               	exit 4
            fi
        else
          	echo $i non numerico
          	exit 5
        fi
        X=$i
    fi 
done
#settiamo la variabile PATH e la esportiamo
PATH=`pwd`:$PATH
export PATH

# creo file
touch /tmp/temp 

count=0
#invocazione del file comando ricorsivo
for i
do
    count=`expr $count + 1`
    if test $count -ne $#
    then
        FCR.sh $i $X
    fi
done

# stampo il numero totale di file trovati
n=`wc -l < /tmp/temp | tr -d ' '`
echo HO trovato $n directory che soddisfano le ricchieste

# cancello il file temporaneo per le prox chiamate
rm /tmp/temp