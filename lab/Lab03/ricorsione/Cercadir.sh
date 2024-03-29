#!/bin/zsh
#file comandi Cercadir.sh
#ricerca in breadth-first
cd $1		#ci spostiamo nella directory in cui dobbiamo fare la ricerca per questa invocazione
if test -x $2	#verifichiamo se esiste una directory con il nome fornito dall'utente
then
	echo la directory $2 si trova in `pwd`	#trovato dir
fi

#passiamo ora alla parte ricorsiva
for i in *
do
	if test -d $i -a -x $i 
	then
		#stampa di debugging
		echo DEBUG-Stiamo per esplorare la directory `pwd`/$i
		#invocazione ricorsiva: ATTENZIONE NOME ASSOLUTO dir!!!
		Cercadir.sh `pwd`/$i $2
	fi
done
