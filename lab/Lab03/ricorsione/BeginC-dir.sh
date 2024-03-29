#!/bin/zsh
#file comandi BeginC-dir.sh
d=	#la variabile d serve per memorizzare o il primo parametro oppure la directory corrente
dd=	#la variabile f serve per memorizzare il parametro che rappresenta il nome relativo semplice della directory (primo o secondo parametro a seconda dei casi)
case $# in
0) echo "POCHI PARAMETRI - Usage is: $0 [directory] directory" 
   exit 1;;
1) d=`pwd`; dd=$1;;
2) d=$1; dd=$2;;
*) echo "TROPPI PARAMETRI - Usage is: $0 [directory] directory"
   exit 2;;
esac
#controllo che d sia dato in forma assoluta
case $d in
/*) ;;
*) echo Errore: $d non in forma assoluta
   exit 3;;
esac
#controllo che dd sia dato in forma relativa semplice 
case $dd in
*/*) echo Errore: $dd non in forma relativa semplice 
     exit 4;;
*) ;;
esac
#controllo che d sia una directory e che sia traversabile 
if test ! -d $d -o ! -x $d
then echo Errore: $d non directory o non attraversabile; exit 5
fi

PATH=`pwd`:$PATH
export PATH
echo BeginC-dir.sh: Stiamo per esplorare la directory $d
./Cercadir.sh $d $dd	#invocazione del secondo file comandi (che e' quello RICORSIVO e fa in questo caso tutto il 'lavoro'!)
echo HO FINITO TUTTO
