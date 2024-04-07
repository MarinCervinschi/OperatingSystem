#!/bin/zsh
#File FCP.sh
 
#Controllo che i parametri non siano meno di 3
if test $# -lt 3
then
    echo Numero parametri incorretto, almeno 3 >&2
    exit 1
fi

# controllo -$1
# deve essere un numero > 0
expr $1 + 0 > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then #siamo sicuri che numerico
    if test $1 -le 0
    then 
        echo $1 non strettamente positivo
        exit 2
    fi
else
    echo $1 non numerico
    exit 3
fi
X=$1 #se i controlli sono andati bene salviamo l'ultimo parametro

# mi sposto avanti di uno
shift

#Per tutte le gerarchie passate
for G in $*
do
    # se in forma assoluta controllo se directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo $G non directory
            exit 4
        fi;;
    *)  echo $G non nome assoluto; 
        exit 5;;
    esac
done

#settiamo la variabile PATH e la esportiamo
PATH=`pwd`:$PATH
export PATH

> /tmp/tmp$$ # file temporaneo su cui scriveremo i file trovati

# per ogni gerarchia passata esseguo il file ricorsivo
for G in $*
do
    echo fase per $i
    FCR.sh $G $X /tmp/tmp$$
done

#terminate tutte le ricerche ricorsive cioe' le N fasi
# Andiamo a contare le linee del file /tmp/conta$$
echo Il numero di file totali che soddisfano la specifica = `wc -l < /tmp/conta$$`
for i in `cat /tmp/conta$$`
do
    #Stampiamo (come richiesto dal testo) i nomi assoluti dei file trovati
    echo Trovato il file $i
    #chiediamo all'utente il numero K per ogni file trovato
    echo -n "Dammi il numero K (strettamente maggiore di 0 e strettamente minore di $X): "
    read K
    #Controllo K (sempre con expr, se prima lo abbiamo fatto con expr, altrimenti sempre con case se prima lo abbiamo fatto con case!)
    expr $K + 0  > /dev/null 2>&1
    N1=$?
    if test $N1 -ne 2 -a $N1 -ne 3
    then    #echo numerico $K siamo sicuri che numerico
            if test $K -le 0 -o $K -ge $X
            then    echo $K non positivo o non minore di $X
                    rm /tmp/conta$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
                    exit 6
            fi
    else
            echo $K non numerico
            rm /tmp/conta$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
            exit 7
    fi
    #selezioniamo direttamente la $K-esima linea del file corrente
    echo la $K-esima linea del file corrente : `head -$K $i | tail -1`
done
#da ultimo eliminiamo il file temporaneo
rm /tmp/conta$$