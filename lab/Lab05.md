# Lab 05 - 04/04/2024 *SHELL*
## 15/04/2016

La parte in Shell deve prevedere un numero variabile di parametri N+1 (N maggiore o uguale a 2): 
- i primi N parametri devono essere nomi assoluti di directory che identificano N gerarchie (G1, G2, …) all’interno del file
system; 
- l’ultimo parametro deve essere considerato un numero intero X strettamente positivo. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in N fasi, una per ogni
gerarchia.
Il programma, per ognuna delle N fasi, deve esplorare la gerarchia Gi corrispondente - tramite un file comandi
ricorsivo, **FCR.sh** - e devono contare globalmente tutte le directory che soddisfano le seguenti due specifiche: 
1) devono contenere solo file (e non sotto-directory)
2) devono contenere solo file la cui lunghezza in linee sia strettamente maggiore di X. 

Al termine di tutte le N fasi, si deve riportare sullo standard output il numero totale
delle directory trovate globalmente che soddisfano la specifica precedente (directory trovate). 

Inoltre, per ogni directory trovata, si deve riportare sullo standard output il suo nome assoluto, e quindi per ognuno dei file (file
corrente) in esso contenuto deve essere riportato sullo standard output il suo nome assoluto e contestualmente
la linea X-esima del file corrente a partire dalla fine del file.
## FCP.sh
```shell
#!/bin/zsh
#Soluzione della Prima Prova in itinere del 15 Aprile 2016
#versione che usa un file temporaneo e usa FCR.sh per tutte le fasi

#controllo sul numero di parametri: deve essere maggiore o uguale a 3 
case $# in
0|1|2)	echo Errore: numero parametri is $# quindi pochi parametri. Usage is $0 numero dirass1 dirass2 ...
	exit 1;;
*) 	echo DEBUG-OK: da qui in poi proseguiamo con $# parametri ;;
esac
#dobbiamo isolare l'ultimo parametro e intanto facciamo i controlli
num=1 	#la variabile num ci serve per capire quando abbiamo trovato l'ultimo parametro
params=	#la variabile params ci serve per accumulare i parametri a parte l'ultimo
#in $* abbiamo i nomi delle gerarchie e il numero intero 
for i 
do
	if test $num -ne $# #ci serve per non considerare l'ultimo parametro che e' il numero
	then
		#soliti controlli su nome assoluto e directory traversabile
		case $i in
		/*) 	if test ! -d $i -o ! -x $i
	    		then
	    		echo $i non directory o non attraversabile
	    		exit 2
	    		fi;;
		*)  	echo $i non nome assoluto; exit 3;;
		esac
		params="$params $i" #se i controlli sono andati bene memorizziamo il nome nella lista params
	else
	#abbiamo individuato l'ultimo parametro e quindi facciamo il solito controllo su numerico e strettamente positivo
		#Controllo ultimo  parametro (con expr)
		expr $i + 0  > /dev/null 2>&1
		N1=$?
		if test $N1 -ne 2 -a $N1 -ne 3
		then #echo numerico $i siamo sicuri che numerico
     			if test $i -le 0
     			then echo $i non strettamente positivo
          		exit 4
     			fi
		else
  			echo $i non numerico
  			exit 5
		fi
		X=$i #se i controlli sono andati bene salviamo l'ultimo parametro
	fi
	num=`expr $num + 1` #incrementiamo il contatore del ciclo sui parametri
done
#controlli sui parametri finiti possiamo passare alle N fasi
PATH=`pwd`:$PATH
export PATH
> /tmp/conta$$ #creiamo/azzeriamo il file temporaneo. NOTA BENE: SOLO 1 file temporaneo!

for i in $params
do
	echo fase per $i 
	#invochiamo il file comandi ricorsivo con la gerarchia, il numero e il file temporaneo
	FCR.sh $i $X /tmp/conta$$   
done

#terminate tutte le ricerche ricorsive cioe' le N fasi
#N.B. Andiamo a contare le linee del file /tmp/conta$$
echo Il numero di directory totali che soddisfano la specifica = `wc -l < /tmp/conta$$` 
for i in `cat /tmp/conta$$`	#nel file temporaneo abbiamo i nomi assoluti delle directory trovate
do
	#Stampiamo (come richiesto dal testo) i nomi assoluti delle directory trovate
	echo "Trovato la directory $i; contiene i seguenti file:"
	cd $i	#ci spostiamo nella directory corrente del for
	for file in * #siamo sicuri che sono solo file (controllo fatto da FCR.sh)
	do
		echo "file: `pwd`/$file"
		echo "la cui linea $X-esima a partire dalla fine e' la seguente:"
		#selezioniamo direttamente la $X-esima linea del file corrente a partire dalla fine
		tail -$X $file | head -1
	done
done 
#da ultimo eliminiamo il file temporaneo
rm /tmp/conta$$
```

## FCR.sh
```shell
#!/bin/zsh
#FCR.sh 
#file comandi ricorsivo che scrive il nome delle directory trovate sul file temporaneo 
#il cui nome e' passato come terzo argomento

cd $1
#la variabile NR ci serve per il numero di linee dei file; in questo caso la inizializziamo per fare un ulteriore controllo come spiegato in seguito
NR=0
#la variabile DIR ci serve per capire se ci sono solo file
DIR=false
#la variabile trovato ci serve per capire se tutti i file rispettano la specifica
trovato=true

for i in *
do
	#controlliamo solo i nomi dei file (se inseriamo anche il controllo se leggibili per cautelarci dato che dopo usiamo il comando wc bisogna commentarlo!)
	if test -f $i 
	then 	
		#calcoliamo il numero di linee 
		NR=`wc -l < $i`
		#controlliamo se il numero delle linee NON e' strettamente maggiore di X
		if test $NR -le $2
			then
			#abbiamo trovato un file che NON soddisfa le specifiche e quindi mettiamo a false trovato
			trovato=false
		fi
	else
		if test -d $i
		then
		#abbiamo trovato una directory e quindi dobbiamo mettere a true DIR
		DIR=true
		fi
	fi
done
#se i due booleani sono rimasti ai valori iniziali allora abbiamo trovato una directory giusta. Nota bene: l'ultimo controllo garantisce che si sia trovato almeno un file dato che una directory vuota non rispetta le specifiche! 
if test $DIR = false -a $trovato = true -a $NR -ne 0 
then
	pwd >> $3 #salviamo il nome della directory corrente (che soddisfa le specifiche) nel file temporaneo
	#NOTA BENE: in questo caso basta usare il comando pwd e quindi e' ritenuto sbagliato scrivere echo `pwd`
fi

#ricorsione in tutta la gerarchia
for i in *
do
	if test -d $i -a -x $i
	then
		#chiamata ricorsiva cui passiamo come primo parametro il nome assoluto della directory 
		FCR.sh `pwd`/$i $2 $3 
	fi
done
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
```shell
  
```
