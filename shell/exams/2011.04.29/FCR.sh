#!/bin/zsh
#File FCR.sh

G=$1
F=$2
fase=$3
T=$4

cd $G

# fase A
if test "$fase" = A
then
    # se file e se il nome = al nome del File passato come parametro
    if test -f $F
    then
        echo "Trovato $2 in `pwd`"
        pwd/$i >> $T # lo inserisco nel file globale
    fi
fi

# fase B
if test "$fase" = B
then
    # variabile per controllare se ho trovato il file di nome F
    trovato=false
    if test -f $F
    then
        trovato=true
    fi
    
    if test trovato = false
    then
        echo la directory `pwd` non contiene file giusti
        > $F
    fi

fi

# controllo le sotto-directory
for d in *
do
    if test -d $d -a -x $d
    then
        FCR.sh `pwd`/$i $F $fase $T
    fi
done

