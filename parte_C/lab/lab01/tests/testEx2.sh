#!/bin/sh
#File testEx2.sh

# Creazione di un file temporaneo di input
input_file=$(mktemp /tmp/input.XXXXXX)

# Spostati nella directory dell'eseguibile
cd ../ex2

# Test 1: Numero di parametri errato. Il programma dovrebbe terminare con un codice di uscita 1.
./parametri2 >/dev/null 2>&1
if [ $? -ne 1 ]; then
    echo "Test 1 fallito: il programma non ha terminato con un codice di uscita 1 quando il numero di parametri è errato"
else
    echo "Test 1 passato"
fi

# Test 2: Il primo parametro non è un file. Il programma dovrebbe terminare con un codice di uscita 2.
./parametri2 non_esiste 1 a >/dev/null 2>&1
if [ $? -ne 2 ]; then
    echo "Test 2 fallito: il programma non ha terminato con un codice di uscita 2 quando il primo parametro non è un file"
else
    echo "Test 2 passato"
fi

# Test 3: Il secondo parametro non è un numero strettamente positivo. Il programma dovrebbe terminare con un codice di uscita 3.
./parametri2 $input_file 0 a >/dev/null 2>&1
if [ $? -ne 3 ]; then
    echo "Test 3 fallito: il programma non ha terminato con un codice di uscita 3 quando il secondo parametro non è un numero strettamente positivo"
else
    echo "Test 3 passato"
fi

# Test 4: Il terzo parametro non è un singolo carattere. Il programma dovrebbe terminare con un codice di uscita 4.
./parametri2 $input_file 1 aa >/dev/null 2>&1
if [ $? -ne 4 ]; then
    echo "Test 4 fallito: il programma non ha terminato con un codice di uscita 4 quando il terzo parametro non è un singolo carattere"
else
    echo "Test 4 passato"
fi

# Cancellazione del file temporaneo
rm $input_file