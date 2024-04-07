#!/bin/zsh
#File FCR.sh

# setto le i parametri con delle variabili
G=$1
X=$2
F=$3

# mi sposto nella directory passata come par
cd $G

#la variabile NG ci serve per il numero di linee trovate dal grep
NG=

for i in *
do
	if test -f $i -a -r $i #se e' un file ed e' leggibile
	then
		#controlliamo le linee che terminano con il carattere t!
        NG=`grep 't$' $i | wc -l
		# controlliamo che le linee trovate siano almeno X
		if test $NG -ge $X
		then
            # abbiamo trovato un file che rispetta la consegna
            # lo aggiungiamo al file temporaneo
            echo `pwd`/$i >> $F
		fi
	fi
done

for i in *
do
    if test -d $i -a -x $i
    then
            #chiamata ricorsiva cui passiamo come primo parametro il nome assoluto della directory
            FCR.sh `pwd`/$i $X $F
    fi
done