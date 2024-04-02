#!/bin/zsh
#File FCR.sh

G=$1
X=$2

# mi sposto nella directory passata come parametro
cd $G

count=0
FILES=

# esploro da directory corrente
for i in *
do
        # cerco file leggibile
        if test -f $i -a -r $i
        then
                # controllo la lunghezza in linee
                n=`wc -l < $i`

                if test $n -eq $X
                then
                        # controllo che ogni riga contenga almeno un numero
                        if ! grep -q -v '[0-9]' $i
                        then
                                count=`expr $count + 1`
				FILE="$FILES $i"
                        fi
                fi
        fi

	# se directory traversabile chiamata ricorsiva
        if test -d $i -a -x $i
        then
                ./FCR.sh `pwd`/$i $X
        fi
done

if test $count -gt 0
then
        echo La directory `pwd` contiene $count files
	echo $FILES
fi

echo "main.c $FILES $X"
