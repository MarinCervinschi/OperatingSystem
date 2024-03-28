#!/bin/zsh
#File append1.sh
if test $# -eq 2
then 
	# controllo [a]
	for i
	do
		case $i in
			*/*) 	echo ERROR: il percorso "($1)" non è relativo semplice
			exit 2;;
		esac
	done

	# controllo [b]
	if ! test -r $1
	then 
		echo ERROR: il file "($1)" non esiste o non è leggibile
		exit 3
	fi

	# controllo [c]
	if ! test -w $2
	then
		echo ERROR: il file "($2)" non esiste o non è scrivibile
		exit 4
	else
		if ! test -w .
		then 
			echo ERROR: la directory corrente non è scrivibile
			exit 5
		fi
	fi

	# dopo i controlli implementiamo il funzionamento di append
	cat < $1 >> $2
	
else
	echo ERROR: Il numero di parametri "($#)" è sbagliato
	exit 1
fi
