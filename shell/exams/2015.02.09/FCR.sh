#!/bin/zsh
#File FCR.sh

# dichiaro le variabili con il nome del testo
G=$1
K=$2
F=$3

# mi sposto nella directory
cd $G

#definiamo una variabile per contenere il numero di righe
NR=
#la variabile trovato ci serve per sapere se abbiamo trovato almeno un file
trovato=false
for i in *
do
	if test -f $i -a -r $i #se e' un file ed e' leggibile
	then
		# calcoliamo il numero di linee
		NR=`wc -l < $i`
		if test $NR -eq $K
		then
            echo `pwd`/$i >> $F
	  		#e aggiorniamo la variabile trovato
            trovato=true
		fi
	fi
done

if test $trovato = true
then
    echo TROVATO directory  `pwd`
fi

for i in *
do
    if test -d $i -a -x $i
    then
        #chiamata ricorsiva passando sempre il nome assoluto della dir
        $0 `pwd`/$i $K $F
    fi
done
