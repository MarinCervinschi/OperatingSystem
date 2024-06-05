#!/bin/sh
#File FCR.sh

G=$1 # salvo la directory in una variabile (G data dal testo)
M=$2 # salvo il numero di file in una variabile (M data dal testo)
# mi sposto nella gerarchia passata come parametro
cd $G 

shift # elimino il primo parametro
shift # elimino il secondo parametro

# adesso $* contiene solo i file

cont=0 # variabile che conta il numero di file di nome relativo semplice uguale ai file passati come parametro
# cont variabile del testo

files= # variabile che contiene i file di nome relativo semplice uguale ai file passati come parametro
# variabile del testo

for F in * # scorro tutti i file della directory
do
    if test -f $F # se F è un file, se directory non mi interessa
    then
        for F2 in $* # scorro tutti i file passati come parametro
        do
            if test $F = $F2 # se i file sono uguali
            then
                cont=`expr $cont + 1` # incremento il contatore
                files="$files $F" # aggiungo il file alla lista
                break # esco dal ciclo interno
            fi
        done
    fi
done

if test $cont -ge $M # se ho trovato almeno M file
then
    echo "Sono `pwd` e ho trovato $cont file"
    echo DEBUG-CHIAMO PARTE C con file $files
    #main $files # chiamo la parte C
fi

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d $G -a -x $G
    then
        FCR.sh `pwd`/$G $M $* # chiamata ricorsiva
    fi
done