
# Lab 03 - 21/03/2024 *SHELL*

## INIBIZIONI
**1) Dopo aver verificato che nella directory corrente ci sia un file di nome p.txt, con un editor, scrivere il file
comandi prova-comandi.sh che deve stampare con il comando echo il nome assoluto del file p.txt e
quindi, in modo separato, deve visualizzare la directory corrente: in entrambi i casi inserire frasi che facciano
capire all’utente che cosa si sta visualizzando! Verificarne il funzionamento.**
```shell
    ls -l p.txt
```
```shell
  nano prova-comandi.sh
```
```shell
#!/bin/zsh
#File prova-comandi.sh
echo Nome assoluto del file p.txt: `pwd`/p.txt
echo Directory corrente `pwd`
echo DEBUG-Directory corrente `pwd`
```
```shell
  chmod u+x prova-comandi.sh
```
```shell
  ./prova-comandi.sh
```
**2) Prendendo ispirazione dal file comandi provaSost.sh visto a lezione (scaricabile da GITHUB), con un editor,
scrivere un file comandi prova-inibizioni.sh che assegna ad una variabile di shell di nome a la stringa
ciao; quindi visualizzare con un unico comando echo il valore della variabile a, della directory corrente e della
espansione del metacarattere \*. Inserire dei commenti significativi. Rendere eseguibile il file comandi e
mandarlo in esecuzione. Quale è il risultato?**cp
```shell
  nano prova-inibizioni.sh
```
```shell
  #!/bin/zsh
  a=ciao
  echo Il valore della variabile a è $a 
  echo La directory corrente è `pwd` 
  echo Il valore di asterisco invece è *
```
```shell
  chmod u+x prova-inibizioni.sh
```
```shell
  ./prova-inibizioni.sh
```
```
  Il valore della variabile a è ciao
  La directory corrente è /Users/marin/files
  Il valore di asterisco invece è [ files ]
```
**3) Modificare, con un editor, il file comandi prova-inibizioni.sh e ricopiare la linea con il comando echo
andando a inibire TUTTE le sostituzioni. Mandarlo nuovamente in esecuzione. Quale è il risultato?**
```shell
  #!/bin/zsh
  a=ciao
  echo 'Il valore della variabile a è $a'
  echo 'La directory corrente è `pwd`'
  echo 'Il valore di asterisco invece è *'
```
```shell
  ./prova-inibizioni.sh
```
```
  Il valore della variabile a è $a
  La directory corrente è `pwd`
  Il valore di asterisco invece è *
```
**4) Modificare, con un editor, il file comandi prova-inibizioni.sh e ricopiare la linea con il comando echo
andando a inibire SOLO l’ultima sostituzione. Mandarlo nuovamente in esecuzione. Quale è il risultato?**
```shell
  #!/bin/zsh
  a=ciao
  echo "Il valore della variabile a è $a"
  echo "La directory corrente è `pwd`"
  echo "Il valore di asterisco invece è *"
```
```shell
  ./prova-inibizioni.sh
```
```
  Il valore della variabile a è ciao
  La directory corrente è /Users/marin/files
  Il valore di asterisco invece è *
```
## SEMPLICI FILE COMANDI
**5) Con un editor, scrivere un file comandi di nome provaExit.sh che semplicemente contenga il comando
exit invocato con valore negativo (ad esempio -1). Verificarne il funzionamento e giustificare il valore ottenuto!**
```shell
    nano provaExit.sh
```
```shell
    #!/bin/zsh
    exit -1
```
```shell
    chmod u+x provaExit.sh
```
```shell
    ./provaExit.sh
```
```shell
    echo $?
```
```
    255
```
**6) Copiare1 il file comandi DIR.sh visto a lezione (scaricabile da GITHUB) nel file comandi di nome DIRCTL.sh
e quindi, con un editor, aggiungere come prima cosa il controllo che il file comandi sia eseguito esattamente
con un solo parametro (CONTROLLO DEI PARAMETRI STRETTO). Verificarne il funzionamento per i vari casi.**
```shell
    cp -p DIR.sh DIRCTL.sh
```
```shell
    nano DIRCTL.sh
```
```shell
#!/bin/zsh
if    test $# -ne 1
then
    echo $# non è il numero di parametri giusto
    exit 1
else
    echo SONO DIR.sh
    echo 'Il valore di $0 ===>' $0
    echo 'Il valore di $1 ===>' $1
    echo "DEBUG-Ora eseguo ls -l $1"
    ls -l $1
fi
```
```shell
    chmod u+x DIRCTL.sh
```
```shell
    ./DIRCTL.sh 
```
```
    0 non è il numero di parametri giusto
```
```shell
    ./DIRCTL.sh p.txt
```
```
    SONO DIR.sh
    Il valore di $0 ===> ./DIRCTL.sh
    Il valore di $1 ===> p.txt
    DEBUG-Ora eseguo ls -l p.txt
    -rw-r--r--@ 1 marin  staff  17 14 Mar 11:02 p.txt
```
```shell
    ./DIRCTL.sh p.txt 2
```
```
    2 non è il numero di parametri giusto
```
**7) Copiare il file comandi DIRCTL.sh dell’esercizio precedente nel file comandi di nome DIRCTL1.sh e
quindi, con un editor, aggiungere (dopo il controllo sul numero di parametri) il controllo se il parametro è un
file o una directory, adattando il codice ai due diversi casi: in particolare, nel caso sia passato il nome di una
directory, si dovranno visualizzare le informazioni della directory vista come file, mentre nel caso sia passato
il nome di un file il comportamento dovrà essere lo stesso di prima! Verificarne il funzionamento per i vari casi.**
```shell
     cp -p DIRCTL.sh DIRCTL1.sh
```
```shell
    nano DIRCTL1.sh
```
```shell
#!/bin/zsh
#File DIRCTL1.sh
if      test $# -ne 1
then
        echo $# non è il numero di parametri giusto
        exit 1
elif    test -f $1
then
        echo SONO DIRCTL1.sh e sono un file
        echo 'Il valore di $0 ===>' $0
        echo 'Il valore di $1 ===>' $1
        echo "DEBUG-Ora eseguo ls -l $1"
        ls -l $1
elif    test -d $1
then
        echo SONO DIRCTL1.sh e sono una directory
        echo 'Il valore di $0 ===>' $0
        echo 'Il valore di $1 ===>' $1
        echo "DEBUG-Ora eseguo ls -dl $1"
        ls -dl $1
fi
```
**8) Copiare il file comandi DIRCTL1.sh dell’esercizio precedente nel file comandi di nome DIRCTL2.sh;
aggiungere che, nel caso non si passino parametri (CONTROLLO DEI PARAMETRI LASCO), si devono visualizzare
tutte le informazioni dei file e delle sottodirectory della directory corrente, in forma paginata. Osservazione:
nel caso nei due esercizi precedenti il controllo sul numero dei parametri è stato fatto con un if, in questo caso
è più opportuno fare il controllo con un case, in modo da intercettare i vari casi: il caso 0 parametri (corretto
e in cui bisogna eseguire quanto richiesto e conviene farlo direttamente nel codice dell’alternativa
corrispondente del case), il caso 1 parametro (corretto e in cui nel seguito, cioè dopo il case, verrà eseguito
quanto si faceva nel file DIRCTL1.sh), i casi 2 o più parametri, che come prima dovrà riportare una indicazione
di errore (casi NON corretti). Verificarne il funzionamento per i vari casi.**
```shell
    cp -p DIRCTL1.sh DIRCTL2.sh
```
```shell
    nano DIRCTL2.sh
```
```shell
#!/bin/zsh
#File DIRCTL2.sh
case $# in
0)      echo non sono stati passati parametri
        echo DEBUG-eseguo 'ls -l' paginato nella directory corrente
        ls -l | more
        exit 0;;
1)      if      test -f $1
        then
                echo SONO DIRCTL1.sh e sono un file
                echo 'Il valore di $0 ===>' $0
                echo 'Il valore di $1 ===>' $1
                echo "DEBUG-Ora eseguo ls -l $1"
                ls -l $1
        elif      test -d $1
        then
                echo SONO DIRCTL1.sh e sono una directory
                echo 'Il valore di $0 ===>' $0
                echo 'Il valore di $1 ===>' $1
                echo "DEBUG-Ora eseguo ls -dl $1"
                ls -dl $1
        fi;;
*)      echo $# non è il numero di parametri giusto
        exit 1;;
esac
```
**9) Con un editor, scrivere un file comandi di nome un-solo-parametro.sh che accetti un solo parametro
(CONTROLLO DEI PARAMETRI STRETTO) e, in tale caso, riporti sullo standard output se tale parametro
rappresenta un nome assoluto, relativo, o relativo semplice. Verificarne il funzionamento per i tre casi.**
```shell
    nano un-solo-parametro.sh
```
```shell
#!/bin/zsh
#File un-solo-parametro.sh
case $# in

1)      case $1 in
        /*) echo Il percorso di $1 è assoluto.;;
        */*) echo Il persorso di $1 è relativo.;;
        *)echo Il persorso di $1 è semplice.;;
        esac;;
*) echo $# non è il numero di parametri giusto
   exit 1;;
esac
```
```shell
    chmod u+x un-solo-parametro.sh
```
```shell
    ./un-solo-parametro.sh p.txt
```
```
    Il percorso di p.txt è semplice.
```
```shell
    ./un-solo-parametro.sh dirProva/p.txt
```
```
    Il percorso di dirProva/p.txt è relativo.
```
```shell
    ./un-solo-parametro.sh /Users/marin/files/p.txt
```
```
    Il percorso di /Users/marin/files/p.txt è assoluto.
```
**10) Copiare il file comandi un-solo-parametro.sh dell’esercizio precedente nel file comandi di nome un-
solo-parametro-bis.sh; aggiungere SOLO nel caso il nome sia assoluto, il controllo sul ‘tipo’ di
parametro e cioè se è un file o una directory traversabile o nessuno dei due casi. Verificarne il funzionamento
per i vari casi.**
```shell
    cp -p un-solo-parametro.sh un-solo-parametro-bis.sh
```
```shell
#!/bin/zsh
#File un-solo-parametro-bis.sh
case $# in
1)      case $1 in
        /*) echo Il percorso di $1 è assoluto.
                if test -f $1
                then
                        echo Sono un file
                elif test -d $1 -a -x $1
                then
                        echo Sono una directory traversabile
                else
                        echo Non sono nè un file nè una directory traversabile
                fi;;
        */*) echo Il persorso di $1 è relativo.;;
        *)echo Il persorso di $1 è semplice.;;
        esac;;
*) echo $# non è il numero di parametri giusto
   exit 1;;
esac
```
```shell
    chmod u+x un-solo-parametro-bis.sh
```
```shell
    ./un-solo-parametro-bis.sh
```
**11) Con un editor, scrivere un file comandi di nome trova-file.sh che controlli di essere invocato
esattamente con 1 parametro (CONTROLLO DEI PARAMETRI STRETTO) e che tale parametro deve essere un
nome relativo semplice (come fatto nei due esercizi precedenti). Quindi, dopo la fase di controllo del numero
e ‘tipo’ di parametri, lo script deve verificare se nella directory corrente esiste un file il cui nome è passato
come parametro e ne deve stampare il nome assoluto.**
```shell
    nano trova-file.sh
```
```shell
#!/bin/zsh
#File trova-file.sh
case $# in
1)      case $1 in
        /*) echo Il percorso di $1 è assoluto.
                exit 1;;
        */*) echo Il persorso di $1 è relativo.
                exit 2;;
        *)echo Il persorso di $1 è semplice.
                if test -f $1
                then
                        echo Il percorso è `pwd`/$1
                else
                        echo Il file non è presente nella direcotry attuale.
                fi;;
        esac;;
*) echo $# non è il numero di parametri giusto
   exit 1;;
esac
```
```shell
    chmod u+x trova-file.sh
```
```shell
    ./trova-file.sh p.txt
```
**12) Con un editor, scrivere un file comandi di nome append.sh che deve accettare uno o due parametri
(CONTROLLO DEI PARAMETRI LASCO), che devono essere nomi di file (in qualunque forma,
assoluti/relativi/relativi semplici). Nel caso di un solo parametro, il contenuto dello standard input deve essere
scritto in append sul file il cui nome è passato come unico parametro; nel caso di due parametri, il contenuto
del file il cui nome è passato come primo parametro deve essere scritto in append sul file il cui nome è passato
come secondo parametro. Verificarne il funzionamento per i due casi, sia passando nomi di file esistenti che
di file NON esistenti!**
```shell
    nv append.sh
```
```shell
#!/bin/zsh
#File append.sh
if test $# -gt 2
then
        echo Il numero di parametri $# non è correto
        exit 1
fi

case $# in
1)      if test -f $1
        then
                echo Sono $1 e sono un file
                cat >> $1
        else
                echo ERROR: $1 non è un file
                echo 2
        fi;;
2)      if test -f $1 -a -f $2
        then
                cat < $1 >> $2
        else
                if test -f $1
                then
                        echo ERROR: $2 non è un file
                        exit 2
                else
                        echo ERROR: $1 non è un file
                        exit 2
                fi
        fi
esac
```
```shell
    chmod u+x append.sh
```
```shell
    ./append.sh first second
```
**13) Con un editor, scrivere un file comandi di nome append1.sh che si deve comportare in modo simile al file
comandi append.sh, ma deve prevedere esattamente due parametri (CONTROLLO DEI PARAMETRI
STRETTO); devono essere poi introdotti diversi controlli: a) i due parametri devono essere nomi relativi
semplici; b) il file il cui nome è passato come primo parametro deve esistere ed essere leggibile; c) il file il cui
nome è passato come secondo parametro, se esiste, deve essere scrivibile, altrimenti se non esiste si deve
verificare che la directory corrente sia scrivibile. Verificarne il funzionamento nei vari casi.**
```shell
    nv append1.sh
```
```shell
#!/bin/zsh
#File append1.sh
if test $# -eq 2
then
	# controllo [a]
	for i
	do
		case $i in
			*/*) 	echo ERROR: il percorso "($1)" non è relativo semplice
			exit 2;;
		esac
	done

	# controllo [b]
	if ! test -r $1
	then
		echo ERROR: il file "($1)" non esiste o non è leggibile
		exit 3
	fi

	# controllo [c]
	if ! test -w $2
	then
		echo ERROR: il file "($2)" non esiste o non è scrivibile
		exit 4
	else
		if ! test -w .
		then
			echo ERROR: la directory corrente non è scrivibile
			exit 5
		fi
	fi

	# dopo i controlli implementiamo il funzionamento di append
	cat < $1 >> $2
	
else
	echo ERROR: Il numero di parametri "($#)" è sbagliato
	exit 1
fi
```
```shell
    chmod u+x append1.sh
```
```shell
    ./append1.sh first second
```
**14) Con un editor, scrivere un file comandi di nome tutti-par.sh che, dopo aver controllato che il numero di
parametri sia maggiore o uguale a 1 (CONTROLLO DEI PARAMETRI LASCO), riporti su standard output tutti i
parametri passati sia in forma aggregata che un parametro per volta. Verificarne il funzionamento nei vari casi.**
```shell
    nv tutti-par.sh
```
```shell
#!/bin/zsh
#File tutti-par.sh
# controllo dell'input
if test $# -lt 1
then
	echo ERROR: il numero di parametri "($#)" è sbagliato
	exit 1
fi

echo Parametri in forma aggregata: $*
echo Parametri uno per volta
for i in $*
do
	echo Parametro = $i
done
```
```shell
    chmod u+x tutti-par.sh
```
```shell
    ./tutti-par.sh vari comandi di verifica
```
**15) Copiare il file comandi tutti-par.sh dell’esercizio precedente nel file comandi di nome tutti-par-
bis.sh; aggiungere, all’interno del ciclo in cui si riporta su standard output il valore di ogni parametro
passato, l’indicazione del loro 'nome' (\$1, \$2, etc.). SUGGERIMENTO: Usare un contatore e poi stamparne il
valore insieme con \$. Verificarne il funzionamento.**
```shell
    cp -p tutti-par.sh tutti-par-bis.sh
```
```shell
    nv tutti-par-bis.sh
```
```shell
#!/bin/zsh
#File tutti-par-bis.sh
# controllo dell'input
if test $# -lt 1
then
	echo ERROR: il numero di parametri "($#)" è sbagliato
	exit 1
fi

echo Parametri in forma aggregata: $*
echo Parametri uno per volta
j=1
for i
do
	echo Parametro \$$j = $i
	j=`expr $j + 1`
done
```
```shell
    ./tutti-par.sh vari comandi di verifica
```
**16) Copiare il file comandi LeggiEMostra.sh visto a lezione (scaricabile da GITHUB) nel file comandi di nome
LeggiEMostra1.sh; con un editor, modificare la parte di controllo dei parametri in modo da poter
funzionare per un numero di parametri maggiore o uguale a 1 (CONTROLLO DEI PARAMETRI LASCO); quindi
su ogni parametro passato svolgere le stesse azioni presenti in LeggiEMostra.sh, ma usando un case per
verificare la risposta dell’utente (come fatto nel file comandi readCase.sh visto a lezione e sempre
scaricabile da GITHUB). Verificarne il funzionamento nei vari casi.**
```shell
    cp -p LeggiEMostra.sh LeggiEMostra1.sh
```
```shell
    nv LeggiEMostra1.sh
```
```shell
#!/bin/zsh
#file comandi LeggiEMostra1.sh
#CONTROLLO SU PRESENZA DI ALMENO UN PARAMETRO
if test $# -lt 1
then 	echo Errore: voglio almeno un parametro
	exit 1
fi

#chiediamo all'utente se vuole visualizzare il contenuto del file: N.B. forziamo l'output sul terminale corrente per non avere problemi se si usasse la ridirezione dello standard output
for i
do
	# controlliamo che il parametro sia un file leggibile
	if test ! -r $i
        then
                echo Errore: $i non file oppure non leggibile
                exit 2
        fi

	printf "vuoi visualizzare il file $i (y/n)? " >&1
	#leggiamo la risposta dell'utente
	read risposta

	#usiamo in questo caso un case per vincolare meno l'utente nelle risposte!
        case $risposta in
        S* | s* | Y* | y*)      echo info del file $i
                                ls -la $i       #potrebbe anche essere un nome che inizia con .                                			  # echo contenuto del file $i
                                cat $i;;
        *) echo niente stampa di $i;;
        esac
done
```
```shell
./LeggiEMostra.sh pippo prova-comandi.sh un-solo-parametro.sh
```
**17) Copiare il file comandi for1.sh visto a lezione (scaricabile da GITHUB) nel file comandi di nome
for1Bis.sh; con un editor, modificare il codice in modo che il corpo del ciclo sia eseguito solo per i nomi
dei file/directory nascosti. Verificarne il funzionamento, dopo aver verificato di avere almeno un file nascosto.**
```shell
    cp -p for1.sh for1Bis.sh
```
```shell
    nv for1Bis.sh
```
```shell
#!/bin/zsh
#File for1Bis.sh
for i in .*	#per tutti i file/directory nascosti della directory corrente
do
	echo ELEMENTO CORRENTE $i	#visualizziamo il nome del file/directory
done
```
```shell
    ./for1Bis.sh
```
**18) Copiare, nuovamente, il file comandi for1.sh visto a lezione (scaricabile da GITHUB) nel file comandi di
nome for2.sh ; con un editor, modificare il codice in modo che il corpo del ciclo sia eseguito solo per i nomi
che iniziano con la lettera ‘p’ (nella directory corrente) e, nel caso il nome corrisponda ad un file, si deve anche
visualizzarne il contenuto, mentre se è una directory bisogna segnalarlo. Verificarne il funzionamento.**
```shell
    cp -p for1.sh for2.sh
```
```shell
    nv for2.sh
```
```shell
#!/bin/zsh
#File for2.sh
for i in p*	#per tutti i file/directory che cominciano con la 'p'della directory corrente
do
	if test -f $i
	then
		echo Sono "($i)" e sono un file
		echo "==="
		cat < $i
		echo "==="
	else
		echo Sono "($i)" e sono una directory
	fi
done
```
```shell
    ./for2.sh
```
**19) Copiare il file comandi for2.sh dell’esercizio precedente nel file comandi di nome for2Bis.sh;
aggiungere, nel caso il nome che inizia con la lettera ‘p’ sia quello di un file, la scrittura del suo nome assoluto
in append su file di nome /tmp/t. Verificarne il funzionamento e in particolare ricavare il numero di file trovati.
Cosa succede se si esegue nuovamente for2Bis.sh?**
```shell
    cp -p for2.sh for2Bis.sh
```
```shell
    nv for2Bis.sh
```
```shell
#!/bin/zsh
#File for2Bis.sh
for i in p*	#per tutti i file/directory che cominciano con la 'p'della directory corrente
do
	if test -f $i
	then
		echo Sono "($i)" e sono un file
		echo "==="
		cat < $i
		echo "==="
		echo `pwd`/$i >> /tmp/t
	else
		echo Sono "($i)" e sono una directory
	fi
done
```
```shell
    ./for2Bis.sh
```
**20) Copiare il file comandi for4Bis.sh visto a lezione (scaricabile da GITHUB) nel file comandi di nome
for4Ter.sh con l’obiettivo di rendere più generale il codice: infatti, il nome del file usato per l’esecuzione
di for4Bis.sh deve essere un parametro di invocazione di for4Ter.sh. Quindi, si deve prevedere un
controllo sul numero dei parametri che deve essere esattamente uguale a 1 (CONTROLLO DEI PARAMETRI
STRETTO) e quindi il controllo che tale singolo parametro sia il nome relativo semplice di un file. Sul contenuto
del file passato come parametro si deve svolgere il for presente in for4Bis.sh. Per verificare il
funzionamento di questo script, innanzitutto si creino 3 file di testo con nome pippo.txt (con 4 linee), pluto.txt
(con 3 linee) e paperino.txt (con 6 linee), poi si crei un file di nome temp che deve avere il formato del file t
usato a lezione. Si verifichi quindi il funzionamento di for4Ter.sh passando il file temp.**
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



