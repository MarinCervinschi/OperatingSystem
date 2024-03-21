#!/bin/zsh
case $# in
0)	echo `ls -Rl`;;
1)	if	test -f $1
	then
		echo SONO DIRCTL1.sh e sono un file
		echo 'Il valore di $0 ===>' $0
		echo 'Il valore di $1 ===>' $1
		echo "DEBUG-Ora eseguo ls -l $1"
		ls -l $1
	fi
	if	test -d $1
	then
		echo SONO DIRCTL1.sh e sono una directory
        	echo 'Il valore di $0 ===>' $0  
        	echo 'Il valore di $1 ===>' $1  
        	echo "DEBUG-Ora eseguo ls -dl $1"
        	ls -dl $1
	fi;;
*)	echo $# non è il numero di parametri giusto
        exit 1;;
esac	
