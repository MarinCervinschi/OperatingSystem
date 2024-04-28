# EX 8
Con un editor, scrivere un programma in C **sostituisciCar.c** che deve essere invocato esattamente con **2 parametri**:
- il primo deve essere considerato il **nome di un file F**;
- il secondo deve essere considerato un **singolo carattere Cx**.

Dopo aver fatto tutti i controlli necessari (sul numero dei parametri e sul loro ‘tipo’), si deve operare una
modifica del contenuto del file F: in particolare, tutte le occorrenze del carattere Cx nel file F devono essere sostituite
con il carattere spazio/blank.

**N.B.** Si faccia attenzione che, quando si trova una occorrenza del carattere Cx (andando a leggere dal file un carattere
alla volta, come nel programma contaOccorrenze.c), il File Pointer risulta già avanzato e quindi bisogna portarlo
indietro di 1 (con la primitiva lseek) prima di poter fare la scrittura del carattere spazio!