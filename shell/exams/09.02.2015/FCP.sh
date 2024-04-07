#!/bin/zsh
#File FCP.sh

# controllo il numero di parametri
case $# in
2)	;;
*) 	echo "Errore: Usage is $0 <directory> <numero>"
	exit 1;;
esac

G=$1 # primo parametro 
K=$2 # secondo parametro

# controllo $1
# se in forma assoluta controllo se directory e traversabile
case $G in
/*) if test ! -d $G -o ! -x $G
    then
        echo $G non directory
        exit 2
    fi;;
*)  echo $G non nome assoluto; 
    exit 3;;
esac

# controllo $2
# Controllo numero intero strettamente positivo (con expr)
expr $K + 0 > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then #siamo sicuri che numerico
    if test $K -le 0
    then 
        echo $K non strettamente positivo
        exit 4
    fi
else
    echo $K non numerico
    exit 5
fi

#settiamo la variabile PATH e la esportiamo
PATH=`pwd`:$PATH
export PATH

# chiamata ricorsiva
touch /tmp/tmp$$ #creiamo il file temporaneo che passeremo poi come ultimo parametro al file comandi ricorsivo
FCR.sh $1 $2 /tmp/tmp$$

parms= #variabile in cui accumuliamo file trovati e numeri chiesti all'utente

for i in `cat /tmp/tmp$$`
do
        params="$params $i"
        #Il programma, per ognuno dei file, deve richiedere all'utente un numero X intero strettamente positivo e minore di $K
        echo "Dammi un numero intero strettamente positivo e minore o uguale a $K per il file $i: "
        read X
        #Controllo X (sempre con case!)
        case $X in
        *[!0-9]*) echo non numerico o non positivo
                  rm /tmp/tmp$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
                  exit 6;;
        *)  if test $X -eq 0
            then 
                echo ERRORE: dato inserito $X uguale a zero
                rm /tmp/tmp$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
                exit 7
            fi ;;
        esac
        if test $X -gt $K
        then
                echo Numero fornito $X non minore di $K
                rm /tmp/tmp$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
                exit 8
        fi
        params="$params $X"
done

#cancelliamo il file temporaneo dato che non ne abbiamo piu' bisogno
rm /tmp/tmp$$

#Infine, si deve invocare la parte in C passando come parametri gli N nomi assoluti dei file selezionati F0, F1, ..., FN-1 intervallati dai numeri positivi chiesti all'utente
echo Sto per chiamare la parte C a cui si passano i parametri $params
FCP $params