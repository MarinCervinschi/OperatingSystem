#!/bin/zsh
#File DIRCTL2.sh
case $# in
0)      echo non sono stati passati parametri
	echo DEBUG-eseguo 'ls -l' paginato nella directory corrente
   	ls -l | more
   	exit 0;;
1)      if      test -f $1
        then
                echo SONO DIRCTL1.sh e sono un file
                echo 'Il valore di $0 ===>' $0
                echo 'Il valore di $1 ===>' $1
                echo "DEBUG-Ora eseguo ls -l $1"
                ls -l $1
        elif      test -d $1
        then
                echo SONO DIRCTL1.sh e sono una directory
                echo 'Il valore di $0 ===>' $0  
                echo 'Il valore di $1 ===>' $1  
                echo "DEBUG-Ora eseguo ls -dl $1"
                ls -dl $1
        fi;;
*)      echo $# non è il numero di parametri giusto
        exit 1;;
esac
