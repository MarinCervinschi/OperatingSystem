#!/bin/zsh
#File for2.sh
for i in p*	#per tutti i file/directory che cominciano con la 'p'della directory corrente
do
	if test -f $i
	then 
		echo Sono "($i)" e sono un file
		echo "==="
		cat < $i
		echo "==="
	else
		echo Sono "($i)" e sono una directory
	fi
done
