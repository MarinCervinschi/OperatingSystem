#!/bin/zsh
#File trova-file.sh
case $# in
1)      case $1 in
        /*) echo Il percorso di $1 è assoluto.
                exit 1;;
        */*) echo Il persorso di $1 è relativo.
                exit 2;;
        *)echo Il persorso di $1 è semplice.
                if test -f $1
                then
                        echo Il percorso è `pwd`/$1
                else
                        echo Il file non è presente nella direcotry attuale.
                fi;;
        esac;;
*) echo $# non è il numero di parametri giusto
   exit 1;;
esac
