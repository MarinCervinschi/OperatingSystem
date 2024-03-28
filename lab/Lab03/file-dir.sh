#!/bin/zsh
#File file-dir.sh

# mi sposto nella directory passatomi come parametro
cd $1

# inizializo due variabili per tenere conto dei file e directory lette
FILE=0
DIR=0

# itere su tutto il contenuto della directory
for i in *
do
	if test -f $i
	then 
		echo "[F] `pwd`/$i"
		FILE=`expr $FILE + 1`
	elif test -d $i
	then
		echo "[D] `pwd`/$i"
		DIR=`expr $DIR + 1`
	fi
done

# riporto il numero di file e dir letti
echo Ho letto $FILE file
echo Ho letto $DIR directory
