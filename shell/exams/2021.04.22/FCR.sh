#!/bin/zsh
#File FCR.sh

G=$1
S=$2
T=$3

# mi sposto nella gerarchia
cd $G

#variabile che ci servira' per capire se abbiamo trovato almeno un file
trovato=false 

for F in *
do
    if test -f $F #se è un file
    then
        # controlliamo se termina per la stringa cercata
        case $F in
        #se il nome rispetta la specifica, settiamo trovato a true
        *.$S)   trovato=true; break;; 
        *) ;;
        esac
    fi
done

#se abbiamo trovato almeno un file dobbiamo salvare il nome della dir corrente nel file temporaneo
if test $trovato = true 
then
    #dobbiamo scrivere il nome della directory nel file temporaneo
    pwd >> $3
fi

# chiamata ricorsiva per le sotto-directory della gerarchia
for i in *
do
    if test -d $i -a -x $i
    then
        $0 `pwd`/$i $S $F
    fi   
done