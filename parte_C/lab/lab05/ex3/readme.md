### EX 3
Con un editor, scrivere un programma in C **9Set16.c** che risolva la parte C dell’Esame del 9 Settembre
2016 che si riporta qui di seguito per comodità.

La parte in C accetta un **unico parametro** che rappresenta il nome assoluto di un file (F) (senza bisogno di
controlli sul fatto che sia assoluto).

Il processo padre deve generare 26 processi figli (P0, P1, … P25), tanti quanti i caratteri dell’alfabeto
inglese: tutti i processi figli Pi (con i che varia da 0 a 25) sono associati all’unico file F e ognuno dei processi
figli è associato al carattere alfabetico minuscolo corrispondente (P0 è associato al carattere ‘a’ fino a P25
che è associato al carattere ‘z’). 

Ogni processo figlio Pi deve leggere i caratteri del file F cercando il carattere a lui associato Ci (per i=0, C0=‘a’, … per i=25, C25=‘z’). I processi figli e il processo padre devono attenersi a questo schema di comunicazione a pipeline: il figlio P0 comunica con il figlio P1 che comunica con il figlio P2 etc. fino al figlio P25 che comunica con il padre.

Questo schema a pipeline deve prevedere l’invio in avanti di un array di strutture dati ognuna delle quali deve contenere due campi: 
1) v1, di tipo char, che deve contenere il carattere Ci; 
2) v2, di tipo long int, che deve contenere il numero di occorrenze del carattere Ci, calcolate dal corrispondente processo. 

Ogni array di strutture utilizzato dai figli e dal padre deve avere dimensione fissa (26 elementi!). Quindi la comunicazione deve avvenire in particolare in questo modo: 
- il figlio P0 passa in avanti (cioè comunica) un array di strutture A0 (di 26 elementi), che
contiene una sola struttura significativa (nell’elemento di indice 0 dell’array A0) con v1 uguale ad ‘a’ e con
v2 uguale al numero di occorrenze del carattere ‘a’ trovate da P0 nel file F; 
- il figlio seguente P1, dopo aver calcolato il numero di occorrenze del carattere associato C1 nel file F, deve leggere (con una singola read) l’array A0 inviato da P0 e quindi deve confezionare l’array A1 che corrisponde all’array A0 aggiungendo nell’elemento di indice 1 la struttura con i propri dati e la passa (con una singola write) al figlio seguente
P2, etc. fino al figlio P25, che si comporta in modo analogo, ma passa al padre. Quindi, al processo padre
deve arrivare l’array A25. 

Il processo padre, dopo aver ordinato tale array A25 in senso crescente rispetto al campo v2, deve riportare i dati di ognuna delle 26 strutture su standard output insieme al PID e all’indice i del processo che ha generato tale struttura.

Al termine, ogni processo figlio Pi deve ritornare al padre l’ultimo carattere letto dal file F; il padre deve
stampare su standard output il PID di ogni figlio e il valore ritornato sia come carattere che come valore
ASCII (in decimale).

### SE PUÒ SERVIRE SI RIPORTA IL SEGUENTE CODICE:
```c
void bubbleSort(int v[], int dim) {
    int i;
    bool ordinato = false;
    
    while (dim > 1 && !ordinato) {
        ordinato = true; /* hp: è ordinato */
        
        for (i = 0; i < dim - 1; i++) {
            if (v[i] > v[i + 1]) {
                scambia(&v[i], &v[i + 1]);
                ordinato = false;
            }
        }
        
        dim--;
    }
}
```
**OSSERVAZIONE1:** Poiché, in questo caso, il numero di processi è noto staticamente, l’array di pipe che
verrà usato in pipeline è da definire in modo statico e quindi senza bisogno di usare malloc; stesso discorso
per l’array di strutture che deve essere usato dai figli per leggere dal precedente (a parte il primo figlio) e
poi scrivere al successivo (l’ultimo scrive al padre). Ci si ricordi che, poiché il padre deve stampare i PID
dei figli che hanno mandato i vari conteggi, il padre deve salvare (sempre in un array statico) i PID dei figli!

**OSSERVAZIONE2:** Come visto a lezione (anche se, nel caso della soluzione del 26 Maggio 2017, il numero
di processi e quindi di pipe era noto solo dinamicamente), nel caso di comunicazione in pipeline ogni
processo (a parte il primo) legge dalla pipe i-1 e scrive sulla pipe i.

**OSSERVAZIONE3:** Ricordarsi che, come nel caso dei programmi provaEsame2-a.c e
provaEsame2-b.c dell’esercitazione dell’11/05/2023, l’apertura dell’unico file F deve essere
effettuata da ogni figlio e NON dal padre, dato che ogni figlio deve avere il proprio file-pointer per cercare
il carattere associato!

**OSSERVAZIONE4:** Poiché si deve andare ad ordinare l’array ricevuto dal padre, la funzione che fa
l’ordinamento (che deve essere scritta, ad esempio, prendendo ispirazione da quella riportata nel testo!)
dovrà considerare che ogni singolo elemento dell’array è una struct con due campi e che l’ordinamento
va fatto sulla base del campo v2.

**OSSERVAZIONE5:** Fare attenzione a come il padre, una volta ordinato l’array, deve calcolare l’indice dei
figli e quindi il loro PID!