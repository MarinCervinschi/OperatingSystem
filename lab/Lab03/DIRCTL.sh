#!/bin/zsh
#File DIRCTL.sh
if    test $# -ne 1
then
    echo $# non è il numero di parametri giusto
    exit 1
else
    echo SONO DIR.sh
    echo 'Il valore di $0 ===>' $0
    echo 'Il valore di $1 ===>' $1
    echo "DEBUG-Ora eseguo ls -l $1"
    ls -l $1
fi
