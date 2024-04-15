#!/bin/zsh
#File revertDate.sh

# Questo script shell è utilizzato per invertire la data nei nomi dei file

for f in * # Per ogni file nella directory corrente
do
    if test -d $f -a -x $f # Se il file è una directory traversabile
    then
        data=$f # Assegna il nome del file alla variabile 'data'

        # Estrae il giorno, il mese e l'anno dal nome del file
        giorno=`echo $data | cut -d '.' -f1`
        mese=`echo $data | cut -d '.' -f2`
        anno=`echo $data | cut -d '.' -f3`

        # Rinomina il file invertendo l'ordine di giorno, mese e anno
        mv $f "$anno.$mese.$giorno"
    fi
done