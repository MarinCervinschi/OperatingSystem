#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri, devono essere 3
if test $# -ne 3
then
    echo ERROR: numero di paramtri non accettabile
    exit 1;;
fi

# controllo $1
# controllo la validità della gerarchia
G=$1
case $G in
/*) if test ! -d $G -o ! -x $G
    then
        echo Error: $G non directory o non traversabile
        exit 2
    fi
*) echo Error: $G non in forma assoluta; exit 3;;
esac

# controllo $2
case $2 in
*/*)	echo Errore: $2 non deve contenere il carattere /
        exit 4;;
esac
S=$2 

# controllo $3
expr $3 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $3 -le 0 # controllo che il numero sia positivo
    then
        echo ERROR: $3 non strettamente positivo
        exit 5
    fi
else
    echo ERROR: $3 non numerico
    exit 6
fi
N=$3

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
> /tmp/conta$$

# fase A
FCR.sh $G $S /tmp/conta$$

# stampo il numero di directory trovate e il loro nome assoluto
ND=`wc -l < /tmp/conta$$`
echo "Ho trovato $ND directory che contengono almeno un file .$S"
echo "Essi sono `cat /tmp/conta$$`"

# se il numero trovato non è maggiore di N
if test $ND -le $N
then
    echo "Il numero trovato non è strettamente maggiore di $N"
    #cancello il file temporaneo
    rm /tmp/conta$$
    exit 0
fi

# fase B

echo Dammi un numero X compreso fra 1 e $N
read X

# controllo se numerico
expr $X + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    echo DEBUG-OK: X è numerico
    # controllo se 1 <= X <= N
    if test $X -lt 1 -o $X -gt $N
    then
        echo ERROR: $X non compreso fra 1 e $N
        #cancello il file temporaneo
        rm /tmp/conta$$
        exit 7
    fi
else
    echo ERROR: X non numerico
    #cancello il file temporaneo
    rm /tmp/conta$$
    exit 8
fi

# arrivati a questo punto sono certo del numero del utente e posso procedere

# non è necessario invocare di nuovo il file FCR poiché ho già i nomi delle directory
# contenenti almeno un file .$S, mi basta selezionare la riga X-esima, e poiché contine il percorso assoluto 
# della directory posso spostarmici dentro e iterarci sul contenuto


# mi salvo il nome assoluto della directory che si trova alla riga X-esima
ger=`head  -n $X /tmp/conta$$ | tail -n 1`

echo La directory numero $X è $ger

# mi sposto e itero sul contenuto della gerarchia X-esima
cd $ger
for i in *
do
    # se file leggibile
    if test -f $i -a -r $i
    then
        # se il nome finische in .S
        if test $i -eq *.$S
        then
            echo Questa è la prima riga del file $ger/$i
            head -n 1 < $i
        fi
    fi
done

#cancello il file temporaneo
rm /tmp/conta$$