### EX 1
Con un editor, scrivere un programma in C **provaPipe-bis.c** che deve prendere ispirazione da due
programmi mostrati a lezione (disponibili su GITHUB): i due programmi sono provaopen.c e
provaPipe.c. 

Tale programma deve avere solo **due parametri** di invocazione che devono essere nomi
di file (come in provaopen.c). Dopo aver aperto i due file passati come parametri (salvando i valori
ritornati dalle open nelle variabili fd1 e fd2), si proceda alla chiusura di fd1 (in modo assolutamente
analogo a quanto fatto nel programma provaopen.c), quindi -invece che aprire un altro file- si deve
creare una pipe (in modo assolutamente analogo a quanto fatto nel programma provaPipe.c): 

si stampino, infine, i valori dei due file descriptor della pipe (sempre come fatto nel programma
provaPipe.c). Verificarne il funzionamento sia con un numero di parametri sbagliato, che giusto, ma
file non esistenti che esistenti: cosa si osserva come valore del lato di lettura della pipe?