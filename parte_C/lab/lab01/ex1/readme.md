# 1
Con un editor, scrivere un programma in C **parametri1.c** che deve essere invocato con **almeno 1 parametro**; 

Dopo aver fatto il controllo che il numero dei parametri sia giusto (controllo LASCO), si visualizzi su standard output il nome
dell’eseguibile e il numero dei parametri e, quindi, il valore di ogni parametro (cioè la corrispondente stringa)
inserendo, contestualmente, il numero d’ordine dei singoli parametri: 
- attenzione che il primo vero parametro è argv[1] e quindi il suo indice è 1; 

Se si indica con N il numero di parametri, si imposti il ciclo for con un indice i che varia da 0 a N-1 (quindi con N escluso) e quindi i parametri si otterranno utilizzando su argv l’indice corrispondente a i+1 (IL PERCHÈ DI QUESTA SCELTA SARÀ CHIARO IN SEGUITO). 

Si verifichi il funzionamento sia in assenza di parametri (caso errato) che con un numero variabile di parametri.