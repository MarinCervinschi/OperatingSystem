#!/bin/sh
#File testEx1.sh

cd ../ex1

# Test 1: Nessun parametro. Il programma dovrebbe terminare con un codice di uscita 1.
./parametri1 >/dev/null 2>&1
if [ $? -ne 1 ]; then
    echo "Test 1 fallito: il programma non ha terminato con un codice di uscita 1 quando non sono stati forniti parametri"
else
    echo "Test 1 passato"
fi

# Test 2: Un parametro. Il programma dovrebbe terminare con un codice di uscita 0.
./parametri1 parametro1 >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Test 2 fallito: il programma non ha terminato con un codice di uscita 0"
else
    echo "Test 2 passato"
fi

# Test 3: Due parametri. Il programma dovrebbe terminare con un codice di uscita 0.
./parametri1 parametro1 parametro2 >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Test 3 fallito: il programma non ha terminato con un codice di uscita 0"
else
    echo "Test 3 passato"
fi