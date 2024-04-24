#!/bin/zsh
#File append.sh
if test $# -gt 2
then 
	echo Il numero di parametri $# non è correto
	exit 1
fi

case $# in
1)	if test -f $1
	then
		echo Sono $1 e sono un file
		cat >> $1
	else
		echo ERROR: $1 non è un file
		echo 2
	fi;;
2)	if test -f $1 -a -f $2
	then 
		cat < $1 >> $2
	else
		if test -f $1
		then
			echo ERROR: $2 non è un file
			exit 2
		else
			echo ERROR: $1 non è un file
			exit 2
		fi
	fi
esac
