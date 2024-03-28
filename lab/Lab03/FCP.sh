#!/bin/zsh
#File FCP.sh

# controllo che ci sia soltanto 1 parametro
if test $# -ne 1
then
	echo ERROR: mi serve sono un parametro
	exit 1
else
	echo DEBUG-il numero di parametri giusto
fi

# controllo che il parametro rappresenti un nome assoluto
case $1 in
/*) 	echo DEBUG-il nome è assoluto;;
*) 	echo ERROR: il nome non è assoluto
	exit 2;;
esac

# controllo che sia una directory traversabile
if test -d $1 -a -x $1
then 
	echo DEBUG-Sono una directory traversabile
else
	echo ERROR: non sono una directory o non sono traversabile
fi

# finiti i controlli chiamo il file 'file-dir.sh' passandogli la directory assoluta $1
./file-dir.sh $1
