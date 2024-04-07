#!/bin/zsh
#File FCP.sh

# controllo sul numero di parametri
if test $# -ne 2
then
	echo ERROR: Usage is: $0 [/directory] [number > 0]
	exit 1
fi

# controllo il nome assoluto del primo parametro 
case $1 in
		# se in forma assoluta controllo se directory e traversabile
/*)		if test ! -d -o ! -x $1; then
			echo $1 non in directory o non taversabile
			exit 2
		fi;;

*) 	echo ERROR: $1 non in forma assoluta
	exit 3;;
esac

# controllo secondo parametro (fatto con expr) deve essere un numero
expr $2 + 0 > /dev/null 2>&1
N1=$?

if test $N1 -ne 2 -a $N1 -ne 3; then
	echo numerico $2 #siamo sicuri che numerico
	if test $2 -le 0 ;then
		echo $2 non strettamente positivo
       	exit 4
    fi
else
  	echo $2 non numerico
  	exit 5
fi

#settiamo la variabile PATH e la esportiamo
PATH=`pwd`:$PATH
export PATH

#invocazione del file comando ricorsivo
./FCR.sh $* 
