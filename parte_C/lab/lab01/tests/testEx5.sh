#!/bin/sh
#File testEx5.sh

# Creazione di un file temporaneo di input
input_file=$(mktemp /tmp/input.XXXXXX)
echo "Contenuto del file di input" > $input_file

# Spostamento nella cartella dell'esercizio
cd ../ex5

# Test per il numero di parametri
./contaOccorrenze $input_file > /dev/null 2>&1
if [ $? -eq 1 ]; then
    echo "Test 1 passato!"
else
    echo "Test 1 fallito: controllo del numero di parametri"
fi

./contaOccorrenze $input_file "o" "extra_param" > /dev/null 2>&1
if [ $? -eq 1 ]; then
    echo "Test 2 passato!"
else
    echo "Test 2 fallito: controllo del numero di parametri"
fi

# Test per il controllo dei parametri
./contaOccorrenze non_existing_file "o" > /dev/null 2>&1
if [ $? -eq 2 ]; then
    echo "Test 3 passato!"
else
    echo "Test 3 fallito: il primo parametro non è un file esistente"
fi

./contaOccorrenze $input_file "oo" > /dev/null 2>&1
if [ $? -eq 3 ]; then
    echo "Test 4 passato!"
else
    echo "Test 4 fallito: il secondo parametro non è un singolo carattere"
fi

# Cancellazione del file temporaneo
rm $input_file