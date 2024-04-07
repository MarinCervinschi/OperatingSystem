# Tags

## Export PATH
```shell
#settiamo la variabile PATH e la esportiamo
PATH=`pwd`:$PATH
export PATH
```

## Numero parametri

* Parametri **Q+1** (con Q maggiore o uguale a 2)
```shell
#Controllo che i parametri non siano meno di 3
if test $# -lt 3
then
    echo Numero parametri incorretto, almeno 3 >&2
    exit 1
fi
```
* Parametri **Q+2** (con Q maggiore o uguale a 2)
```shell
case $# in
0|1|2|3) echo Errore: numero parametri $# quindi pochi parametri. Usage is $0 W S dirass1 dirass2 ...
         exit 1;;
*)       echo DEBUG-OK: da qui in poi proseguiamo con $# parametri ;;
esac
```
* N parametri: (con N maggiore o uguale a 2)
```shell
#controllo sul numero di parametri: deve essere maggiore o uguale a 2
case $# in
0|1)	echo Errore: numero parametri $# quindi pochi parametri. Usage is $0 dirass1 dirass2 ...
	exit 1;;
*) 	echo DEBUG-OK: da qui in poi proseguiamo con $# parametri ;;
esac
```
* N parametri
```shell
case $# in
N)	;;
*) 	echo Errore: Usage is $0 dirass stringa numero 
	exit 1;;
esac
```
* un parametro + nome directory in forma assoluta
```shell
#controllo sul numero di parametri: deve essere passato un solo parametro
#facciamo anche contestualmente il controllo se e' una directory traversabile
case $# in
1)	case $1 in
	/*) if test ! -d $1 -o ! -x $1
	    then
	    echo $1 non directory o non attraversabile
	    exit 1
	    fi;;
	*)  echo $1 non nome assoluto; exit 2;;
	esac;;
*) 	echo Errore: Usage is $0 dirass 
	exit 3;;
esac
```
## Tipo di parametro
* numero intero (X) strettamente positivo e strettamente minore di 4
```shell
#dobbiamo controllare che il parametro sia un numero, sia strettamente maggiore di 0 e strettamente minore di 4
case $1 in
*[!0-9]*) echo $1 non numerico o non positivo
          exit 2;;
*)        if test $1 -eq 0 -o $1 -ge 4   #sbagliato
          then
                  echo $1 uguale a 0 oppure maggiore o uguale a 4
                  exit 3
          else
                  echo DEBUG-primo parametro giusto $1
          fi;;
esac

X=$1    #salviamo il numero nella variabile indicata dal testo 
```
* numero intero X strettamente positivo (con expr)
```shell
# Controllo numero intero strettamente positivo (con expr)
expr $1 + 0 > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then #siamo sicuri che numerico
    if test $1 -le 0
    then 
        echo $1 non strettamente positivo
        exit 4
    fi
else
    echo $1 non numerico
    exit 5
fi
X=$1 #se i controlli sono andati bene salviamo l'ultimo parametro
```
```shell
# fatto con case
case $2 in
    *[!0-9]*) echo $2 non numerico o non positivo
                    exit 4;;
    *) if test $2 -eq 0
       then echo ERRORE: secondo parametro $2 uguale a zero
            exit 5
       fi ;;
esac
```
* **nomi assoluti di directory** che identificano Q gerarchie (G1, G2, …) all’interno del file system
```shell
#Per tutte le gerarchie passate
for G in $*
do
    # se in forma assoluta controllo se directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo $G non directory
            exit 4
        fi;;
    *)  echo $G non nome assoluto; 
        exit 5;;
    esac
done
```
* file leggibile con lunghezza in linee pari X e tutte le linee contengono almeno un numero
```shell
#definiamo una variabile per contenere il numero di righe
NR=
#definiamo una variabile per contenere il numero di righe che contengono almeno un carattere numerico 
N=
#definiamo una variabile per memorizzare i nomi dei file 
files=
for i in *
do
	if test -f $i -a -r $i #se e' un file ed e' leggibile
	then
		#calcoliamo il numero di linee
		NR=`wc -l < $i`
        	#calcoliamo quante linee contengono almeno un carattere numerico 
		N=`grep '[0-9]' $i | wc -l`
		#echo NR is $NR e N is $N
		if test $NR -eq $X -a $N -eq $NR
		then
	  		files="$files $i" #le condizioni sono verificate e quindi salviamo il nome del file (basta il nome relativo, non serve che sia assoluto)
		fi
	fi
done
```
* file la cui lunghezza in linee sia strettamente maggiore di X
```shell
#controlliamo solo i nomi dei file
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
fi
```
* il contenuto del file deve essere tale per cui almeno X linee terminino con il carattere **‘t’**. 
```shell
#la variabile NG ci serve per il numero di linee trovate dal grep
NG=

for i in *
do
	if test -f $i -a -r $i #se e' un file ed e' leggibile
	then
		#controlliamo le linee che terminano con il carattere t!
        NG=`grep 't$' $i | wc -l
		# controlliamo che le linee trovate siano almeno X
		if test $NG -ge $X
		then
            # abbiamo trovato un file che rispetta la consegna
            # lo aggiungiamo al file temporaneo
            echo `pwd`/$i >> $F
		fi
	fi
done
```
```shell

```
```shell

```
```shell

```

* parametro deve essere una stringa **(S)**
```shell
#Controllo $2: ha senso che controlliamo che non contenga il carattere /
case $2 in
	*/*) echo $2 non deve contenere il carattere \/
	     exit 4;;
esac
S=$2	 #nome specificato nel testo
```
* parametro deve essere considerato un singolo carattere C
```shell
case $1 in
?) ;;
*)      echo $1 non singolo carattere
        exit 2;;
esac
#salviamo il parametro: il nome della variabile da usare era specificato nel testo
C=$1
```
* parametro deve essere considerato un nome relativo semplice F
```shell
#Controllo primo parametro sia dato in forma relativa semplice
case $1 in
*/*) echo Errore: $1 non in forma relativa semplice
    exit 2;;
*) ;;
esac
F=$1 #salviamo il primo parametro
```

## Isolare parametri
* primi N parametri
```shell
shift ... N volte
```
* l’ultimo parametro deve essere considerato ...
```shell
#dobbiamo isolare l'ultimo parametro e intanto facciamo i controlli
num=1 	#la variabile num ci serve per capire quando abbiamo trovato l'ultimo parametro
params=	#la variabile params ci serve per accumulare i parametri a parte l'ultimo
#in $* abbiamo i nomi delle gerarchie e il numero intero 
for i 
do
	if test $num -ne $# #ci serve per non considerare l'ultimo parametro che e' il numero
	then
		#soliti controlli su nome assoluto e directory traversabile
		...
		params="$params $i" #se i controlli sono andati bene memorizziamo il nome nella lista params
	else
	#abbiamo individuato l'ultimo parametro e quindi facciamo il solito controllo su numerico e strettamente positivo
		#Controllo ultimo  parametro (con expr)
		...
		X=$i #se i controlli sono andati bene salviamo l'ultimo parametro
	fi
	num=`expr $num + 1` #incrementiamo il contatore del ciclo sui parametri
done
```
* gli ultimi due parametri devono essere considerati ...
```shell
#dobbiamo isolare gli ultimi due parametri e intanto facciamo i controlli
num=1   #la variabile num ci serve per capire quando abbiamo trovato il penultimo e l'ultimo parametro
params= #la variabile params ci serve per accumulare i parametri a parte gli ultimi due
#in $* abbiamo i nomi delle gerarchie e i due numeri interi
for i
do
        if test $num -lt `expr $# - 1` #ci serve per non considerare gli ultimi due parametri che sono i numeri
        then
                #soliti controlli su nome assoluto e directory traversabile
                ...
                params="$params $i" #se i controlli sono andati bene memorizziamo il nome nella lista params
        else
        #abbiamo individuato gli ultimi due parametri e quindi facciamo il solito controllo su numerico e strettamente positivo
            #Controllo penultimo e ultimo parametro
		    ...
		    #se i controlli sono andati bene salviamo il penultimo e ultimo parametro
		    if test $num -eq `expr $# - 1`
		    then
		    	H=$i	#H nome indicato nel testo
		    else
		    	M=$i	#M nome indicato nel testo
            fi
        fi
       	num=`expr $num + 1` #incrementiamo il contatore del ciclo sui parametri
done
```
```shell

```
## Normale chiamata ricorsiva dentro FCR.sh
```shell
for i in *
do
    if test -d $i -a -x $i
    then
            #chiamata ricorsiva cui passiamo come primo parametro il nome assoluto della directory
            FCR.sh `pwd`/$i $X $F
    fi
done
```
## Salva dati file
* leggi dati da file tmp, chiedi dato da utente e controllalo, salva i file in una variabile
```shell
parms= #variabile in cui accumuliamo file trovati e numeri chiesti all'utente

for i in `cat /tmp/tmp$$`
do
    params="$params $i"
    #Il programma, per ognuno dei file, deve richiedere all'utente un numero X intero strettamente positivo e minore di $K
    echo "Dammi un numero intero strettamente positivo e minore o uguale a $K per il file $i: "
    read X
    #Controllo X (con case!)
    case $X in
    *[!0-9]*) echo non numerico o non positivo
              rm /tmp/tmp$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
              exit 6;;
    *)  if test $X -eq 0
        then 
            echo ERRORE: dato inserito $X uguale a zero
            rm /tmp/tmp$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
            exit 7
        fi ;;
    esac
    if test $X -gt $K
    then
            echo Numero fornito $X non minore di $K
            rm /tmp/tmp$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
            exit 8
    fi
    params="$params $X"
done
```
* stampa num. e file trovati, chiedi un num. dal utente, fai i controlli e stampa la K-esima riga dalla testa
```shell

#terminate tutte le ricerche ricorsive cioe' le N fasi
# Andiamo a contare le linee del file /tmp/conta$$
echo Il numero di file totali che soddisfano la specifica = `wc -l < /tmp/conta$$`
for i in `cat /tmp/conta$$`
do
    #Stampiamo (come richiesto dal testo) i nomi assoluti dei file trovati
    echo Trovato il file $i
    #chiediamo all'utente il numero K per ogni file trovato
    echo -n "Dammi il numero K (strettamente maggiore di 0 e strettamente minore di $X): "
    read K
    #Controllo K (sempre con expr, se prima lo abbiamo fatto con expr, altrimenti sempre con case se prima lo abbiamo fatto con case!)
    expr $K + 0  > /dev/null 2>&1
    N1=$?
    if test $N1 -ne 2 -a $N1 -ne 3
    then    #echo numerico $K siamo sicuri che numerico
            if test $K -le 0 -o $K -ge $X
            then    echo $K non positivo o non minore di $X
                    rm /tmp/conta$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
                    exit 6
            fi
    else
            echo $K non numerico
            rm /tmp/conta$$ #poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
            exit 7
    fi
    #selezioniamo direttamente la $K-esima linea del file corrente
    echo la $K-esima linea del file corrente : `head -$K $i | tail -1`
done
#da ultimo eliminiamo il file temporaneo
rm /tmp/conta$$
```
```shell

```
```shell

```
```shell

```
```shell

```



