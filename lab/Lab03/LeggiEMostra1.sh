#!/bin/zsh
#file comandi LeggiEMostra1.sh 
#CONTROLLO SU PRESENZA DI ALMENO UN PARAMETRO
if test $# -lt 1
then 	echo Errore: voglio almeno un parametro
	exit 1
fi

#chiediamo all'utente se vuole visualizzare il contenuto del file: N.B. forziamo l'output sul terminale corrente per non avere problemi se si usasse la ridirezione dello standard output
for i
do
	# controlliamo che il parametro sia un file leggibile
	if test ! -r $i
        then
                echo Errore: $i non file oppure non leggibile
                exit 2
        fi

	printf "vuoi visualizzare il file $i (y/n)? " >&1
	#leggiamo la risposta dell'utente
	read risposta

	#usiamo in questo caso un case per vincolare meno l'utente nelle risposte!
        case $risposta in
        S* | s* | Y* | y*)      echo info del file $i
                                ls -la $i       #potrebbe anche essere un nome che inizia con .                                			  # echo contenuto del file $i
                                cat $i;;
        *) echo niente stampa di $i;;
        esac
done
