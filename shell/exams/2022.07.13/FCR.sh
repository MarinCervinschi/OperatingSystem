#!/bin/zsh
#File FCR.sh

G=$1 # salvo il nome della directory in una variabile (G specificata dal testo)
L=$2 # salvo il numero in una variabile (L specificata dal testo)
TMP=$3 # salvo il nome del file temporaneo in una variabile

# mi sposto nella gerarchia passata come parametro
cd $1

# variabile di controllo
trovato= 

# sposto il cursore di lettura dei parametri
shift
shift
shift

# per ogni file nella gerarchia
for F in *
do 

    # se il file corrente è un file regolare e leggibile
    if test -f $F -a -r $F
    then
        trovato=1 # setto la variabile di controllo a 1
        # salvo il numero di righe del file corrente
        NR=`wc -l < $F`
        # se il numero di righe è uguale a L
        if test $NR -eq $L
        then
            # per ogni carattere passato come parametro
            for C in $*
            do
                # se il file corrente NON contiene il carattere corrente
                if ! grep -q $C $F > /dev/null 2>&1
                then
                    trovato=0 # setto la variabile di controllo a 0 ed esco dal ciclo
                    # sono sicuro che il file corrente non contiene tutti i caratteri passati come parametro
                    # quindi esco dal ciclo
                    break
                fi
            done
            # se la variabile di controllo è 1 significa che il file corrente contiene tutti i caratteri passati come parametro
            if test $trovato -eq 1
            then
                # stampo il percorso assoluto del file corrente
                echo "Trovato file che contiene i caratteri passati come parametro: `pwd`/$F di lunghezza in righe $NR"
                echo `pwd`/$F >> $TMP
            fi
        fi
    fi

done

# chiamata ricorsiva per le sotto-directory
for D in *
do
    # se directory traversabile
    if test -d $D -a -x $D
    then
        FCR.sh `pwd`/$D $L $TMP $* # passo tutti i parametri
    fi
done