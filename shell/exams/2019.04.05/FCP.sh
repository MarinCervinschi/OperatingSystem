#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2)  echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)      echo DEBUG-OK: numero di parametri corretto;;
esac

#dobbiamo isolare l'ultimo parametro e intanto facciamo i controlli
couter=1
params=

for i
do
    if test $counter -ne $# # serve per non considerare l'ultimo parametro
    then
        if test ! -d $i -o ! -x $i
        then
            echo ERROR: non directory o non traversabile
            exit 2
        fi
        params="$params $i" # se i controlli sono andati bene memorizzo il nome nella lista params
    else
        # verifico se l'ultimo parametro stringa
        case $i in
        */*)	echo Errore: $i non deve contenere il carattere /
                exit 1;;
        esac
        S=$i # nome specificato nel testo
    fi
    counter=`expr $counter + 1` #incremento il contatore del ciclo sui parametri
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
> /tmp/tmp$$

for i in $params
do
    echo fase per $i
    # invoco il file ricorsivo
    FCR.sh $i $S /tmp/tmp$$
done

# conto il numero totale di file trovati
NF=`wc -l < tmp/tmp$$`
echo Abbiamo trovato $NF file $S.txt

#variabile che serve per capire se l'elemento corrente del for e' una lumghezza o il nome assoluto di un file 
c=0	
for i in `cat /tmp/tmp$$`
do
    # stampiamo il num di caratteri e il nome assoluto del file trovato
    if test `expr $c % 2`-eq 1
    then
        echo Elemento dispari quindi la lunghezza in caratteri del file = $i
    else
        echo Elemento pari quindi il nome assoluto del file = $i
        # chiedo all'utente se vuole ordinare il file
        echo Vuoi ordinare il file?
        read risposta
        
        case $risposta in
        s*|S*|y*|Y*)    echo Il file ordinato senza differenziare maiuscole e minuscole
                        sort -f $i;;
        *)	            echo Deciso di non ordinare il file $i;;
        esac
    fi
done

#cancello il file temporaneo
rm /tmp/tmp$$
