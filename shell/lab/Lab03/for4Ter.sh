#!/bin/zsh
#File for4Ter.sh

# controllo che sia esattamente un parametro
if test $# -ne 1
then 
	echo ERROR: il numero di parametri "($#)" non è corretto
	exit 1
fi

# controllo che sia un file e che sia un nome relativo semplice
if test -f $1
then 
	echo  DEBUG-VISUALIZZAZIONE DI $1
	case $1 in
	*/*)	echo ERROR: non sono un nome relativo semplice
		exit 2;;
	esac
else
	echo ERROR: "($1)" non è un file
	exit 2
fi

#supponiamo che nel file temp siano stati memorizzati i nomi di alcuni file insieme con la loro lunghezza in linee
c=0	#variabile che ci serve all'interno del for per capire se siamo su un elemento dispari (nome file) o su un elemento pari (numero di linee)
for i in `cat $1` 	#la lista usata nel for corrisponde al contenuto di un file!
do
 	c=`expr $c + 1` 	#ad ogni iterazione incrementiamo il contatore
        if test `expr $c % 2` -eq 1    	#se il contatore e' dispari
	then 
		echo Elemento dispari, quindi nome di file $i
		if test -f $i		#controlliamo sia il nome di un file
		then 	cat $i		#e se si' lo visualizziamo
		fi
        else 				#se il contatore e' pari
		echo Elemento pari, quindi lunghezza in linee del file appena visualizzato = $i 
        fi
done
