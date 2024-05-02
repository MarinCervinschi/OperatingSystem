# EX 5
Con un editor, scrivere un programma in C **padreFigliConSalvataggioPID.c** che deve
essere invocato esattamente con 1 parametro che deve essere considerato un numero intero N
strettamente positivo e strettamente minore di 155. 

Dopo aver fatto tutti i controlli necessari (sul numero dei parametri, sul loro ‘tipo’ e vincoli sopra indicati), per prima cosa il programma deve riportare su standard output il pid del processo corrente (processo padre) insieme con il numero N. Quindi, il processo
padre deve generare N processi figli (P0, P1, … PN-1, indicati nel seguito Pi). Ognuno di tali figli Pi deve riportare su standard output il proprio pid insieme con il proprio indice d’ordine (i) e quindi deve calcolare
in modo random (vedi sopra) un numero compreso fra 0 e 100+i.

Al termine, ogni processo figlio Pi deve ritornare al padre il valore random calcolato e il padre deve
stampare su standard output il pid di ogni figlio, insieme con il numero d’ordine derivante dalla creazione,
e il valore ritornato.

**SUGGERIMENTO PER LA CREAZIONE DEGLI N FIGLI DA PARTE DEL PADRE:** Poiché il padre dove
recuperare il numero d’ordine derivante dalla creazione è ASSOLUTAMENTE indispensabile che prima di
creare i figli venga allocato un array dinamico (di dimensione N) in cui il padre andrà a salvare i pid dei figli
e che verrà poi usato per cercare al suo interno il valore ritornato dalla wait e quindi poter stampare
l’indice corrispondente che è il numero d’ordine derivante dalla creazione!