
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
!/bin/zsh
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

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```



