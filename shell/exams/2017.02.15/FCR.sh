#!/bin/zsh
#File FCR.sh

cd $1
X=$2
#definiamo una variabile per contenere il numero di righe
NR=

#definiamo una variabile per contenere il numero di righe che contengono almeno un carattere numerico 
N=

#definiamo una variabile per memorizzare i nomi dei file 
files=

for i in *
do
	if test -f $i -a -r $i #se e' un file ed e' leggibile
	then
		#calcoliamo il numero di linee
		NR=`wc -l < $i`
        	#calcoliamo quante linee contengono almeno un carattere numerico 
		N=`grep '[0-9]' $i | wc -l`
		#echo NR is $NR e N is $N
		if test $NR -eq $X -a $N -eq $NR
		then
	  		files="$files $i" #le condizioni sono verificate e quindi salviamo il nome del file (basta il nome relativo, non serve che sia assoluto)
		fi
	fi
done

#se ho trovato almeno un file
if test "$files"
then
        echo TROVATO DIRETTORIO `pwd`
        echo che contiene i seguenti file che soddisfano la specifica $files
  echo DEVO CHIAMARE LA PARTE C\?
  read risposta
  case $risposta in
  s*|S*|y*|Y*)  ./FCR.sh $files $X;;
  *)            echo Nessuna invocazione della parte C;;
  esac  
fi

for i in *
do
if test -d $i -a -x $i
then
  	#echo RICORSIONE in `pwd`/$i 
  	$0 `pwd`/$i $X	#sempre passaggio del nome assoluto della dir 
fi
done
