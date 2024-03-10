# Lab 01 - 07/03/2024 *SHELL*

## LOGIN-LOGOUT
**2) Eseguire la fase di logout.**
```
    exit
```
## DIRECTORY E FILE DI SISTEMA
**3) Dopo avere nuovamente fatto il login, senza spostarsi dalla propria HOME directory, visualizzare il contenuto
della directory / (root).**
```
    ls /
```
**4) Sempre senza spostarsi dalla propria HOME directory, verificare il contenuto del file /etc/passwd.**
```
    cat /etc/passwd
```
**5) Visualizzare quale è la directory corrente.**
```
    pwd
```
**6) Cambiare la directory corrente spostandosi nella directory di sistema /etc.**
```
    cd etc
```
**7) Senza spostarsi dalla directory /etc, visualizzare quale è la propria HOME directory.**
```
    echo $HOME
```
**8) Visualizzare nuovamente il file passwd.**
```
    cat passwd
```
**9) Provare a visualizzare il file shadow.**
```
    cat shadow
```
**10) Tornare nella propria HOME directory e verificarlo con lo stesso comando usato al punto 5).**
```
    cd
```
## MULTIUTENZA E MULTIPROCESSING
**11) Visualizzare le informazioni relative a UID e GID dell’utente corrente.**
```
    id
```
**12) Visualizzare i processi della sessione interattiva corrente, sia nella forma sintetica che nelle due forme più**
```
    ps
```
```
    ps -f
```
```
    ps -fl
```
**13) Visualizzare tutti i processi attivi nel sistema, sia nella forma sintetica che nelle due forme più estese.**
```
    ps -e
```
```
    ps -fe
```
```
    ps -fle
```
## MISCELLANEA
**14) Verificare il manuale di almeno uno dei comandi usati finora.**
```
    man ps
```
**15) Verificare dove si trova il file eseguibile di almeno uno dei comandi usati finora.**
```
    which ps
```
**16) Verificare anche dove si trova il suo manuale.**
```
    whereis ps
```
## SHELL DIVERSE
**17) Lanciare un’altra shell, ad esempio sh, e verificare i processi attivi e in particolare la relazione padre-figlio.**
```
    sh
```
```
    ps -fl
```
**18) All’interno della nuova shell precedentemente lanciata, lanciare un’altra shell, ad esempio bash, e verificare i
processi attivi e in particolare la relazione padre-figlio.**
```
    bash
```
```
    ps -fl
```
## NOMI FILE E COMANDO LS
**19) Dopo aver verificato di essere nella propria HOME directory, con l’editor vi (o qualunque altro editor) creare
un file che abbia un nome molto lungo; si scrivano almeno alcune linee in tale file. Si verifichi l’esistenza di tale
file con l’opportuno comando.**
```
    cd
```
```
    vi nomefilemoltolungo
```
```
    scrivo una serie di righe
    di prova per verificare l'esecuzione
```
```
    ls -l nomefilemoltolungo
```
**20) Sempre nella propria HOME directory, con un editor creare un file che abbia un nome che contenga più
occorrenze del carattere ‘.’; come prima, si scrivano almeno alcune linee in tale file. Si verifichi l’esistenza di
tale file con l’opportuno comando.**
```
    nano file.di.prova.molto.lungo
```
```
    scrivo una serie di righe
    di prova per verificare l'esecuzione
```
```
    ls -l file.di.prova.molto.lungo
```
**21) Sempre nella propria HOME directory, con un editor creare un file che abbia un nome che inizi con il carattere
‘.’; come prima, si scrivano almeno alcune linee in tale file; si verifichi quindi il contenuto della home directory,
forzando le due visualizzazioni che consentono di ‘vedere’ anche i file il cui nome inizia con ‘.’ .**
```
    nano .filenascosto
```
```
    scrivo una serie di righe
    di prova per verificare l'esecuzione
```
```
    ls -A file.di.prova.molto.lungo
```
## ALTRE OPZIONI DEL COMANDO LS
**22) Cambiare la directory corrente spostandosi nella directory di sistema /home e visualizzare la sottogerarchia
che parte da lì facendo vedere tutti i dettagli, anche sul ‘tipo’ dei file.**
```
    ls -RlF home
```
**23) Rimanendo nella directory di sistema /home, visualizzare il contenuto della propria HOME directory partendo
dal file modificato più recentemente; aggiornare la data di modifica di uno dei file meno recenti e quindi
verificarne l’effetto ripetendo la visualizzazione della propria HOME directory.**
```
    cd
```
```
    ls -tl
```
```
    touch -f
```
```
    ls -tl
```
**24) Rimanendo nella directory di sistema /home, visualizzare il contenuto della propria HOME directory in ordine
alfabetico inverso.**
```
    ls -r
```
**25) Rimanendo nella directory di sistema /home, visualizzare le informazioni relative al file che rappresenta la
propria HOME directory.**
```
    ls -ld
```
## PATTERN MATCHING CON * E ?
**26) Ritornare nella propria HOME directory e creare con un editor alcuni file per verificare le regole del pattern
matching sui nomi dei file.**
```
    nano file1 file2 file3 ile4
```
**27) Verificare le sostituzioni del pattern matching invocando una shell che mostri appunto tali sostituzioni.**
```
    sh -x
```
```
    ls *f?
```
```
    ls *f*
```
```
    ls ?f*
```
**28) Verificare il pattern matching anche con il comando per visualizzare sullo standard output delle stringhe.**
```
    echo f*
```
```
    echo *f*
```
## DIRITTI DI ACCESSO PER I FILE
**29) Verificare i diritti di accesso dei file /etc/passwd e /etc/shadow.**
```
    ls -l /etc/passwd
```
```
    ls -l /etc/shadow
```
**30) Eliminare, per l’utente corrente, il diritto di scrittura ad uno dei propri file e verificare il comportamento di un
editor su quel file.**
```
    chmod u-w file1
```
```
    [ Cannot open file for writing: Permission denied ]
```
**31) Eliminare anche il diritto di lettura sullo stesso file e provare a visualizzare il file.**
```
    chmod u-r file1
```
```
    [ cat: file1: Permission denied ]
```
**32) Usando la notazione ottale, ripristinare per l’utente corrente sia il diritto di lettura che quello di scrittura,
togliendo qualunque altro diritto a gruppo e altri (indipendentemente da quali diritti potevano avere
precedentemente).**
```
    chmod 600 file1
```
## CREAZIONE E CANCELLAZIONE DIRECTORY
**33) Creare una sottodirectory nella propria HOME directory dandogli nome provaDir. Si verifichi l’esistenza di tale
sottodirectory con l’opportuno comando.**
```
    mkdir porvaDir
```
```
    ls -ld porvaDir
```
**34) Controllare il contenuto di tale sottodirectory con l’opportuno comando.**
```
    ls -la provaDir
```
**35) Cancellare la sottodirectory appena creata.**
```
    rmdir provaDir
```
## COPIA DI FILE
**36) Creare nuovamente la sottodirectory provaDir e creare, in tale sottodirectory, una copia di un file presente
nella propria HOME directory e verificare l’esistenza di tale copia.**
```
    mkdir provaDir
```
```
    cp file1 provaDir file1.copia
```
```
    ls -l provaDir
```
**37) Modificare la copia e verificare che la modifica non abbia avuto effetto sul file ‘sorgente’**
```
    nano /provaDir/file1
```
```
    cat file1
```
**38) Fare la copia di un file presente nella propria HOME directory (si può usare, volendo, anche lo stesso file di prima) nella sottodirectory provaDir lasciando lo stesso nome del file originale e mantenendo/preservando in
particolare la data del file e verificare l’esistenza di tale copia.**
```
    cp -p file3 provaDir/
```
```
    ls -tl /provaDir/file3
```
**39) Fare la copia della sottodirectory provaDir utilizzando un singolo comando e usando come nome della copia
provaDir.Originale.**
```
    cp -r provaDir provaDir.Originale
```
## CANCELLAZIONE FILE E DIRECTORY
**40) Cancellare il file creato al punto 36), facendo attenzione che il S.O. vi chieda la conferma, usando il nome
relativo alla directory corrente e quindi rimanendo nella propria HOME directory.**
```
    rm -i provaDir/file1.copia
```
**41) Cancellare il file creato al punto 38), facendo attenzione che il S.O. vi chieda la conferma, dopo essersi spostati
nella sottodirectory provaDir e quindi usando il nome relativo semplice.**
```
    cd provaDir
```
```
    rm -i file3c
```
**42) Creare nella sottodirectory provaDir almeno un file con un editor. Si verifichi l’esistenza di tale file con
l’opportuno comando.**
```
    nano provaDir/filediprova
```
```
    ls -l provaDir/filediprova
```
**43) Cancellare la sottodirectory provaDir.**
```
    rm -ri provaDir
```
## RIDIREZIONE *CAT*
**44) Usando la ridirezione dello standard output del comando-filtro cat,
creare un file di nome prova (inserire almeno 5-6 linee con più parole per linea). Ricordarsi che la fine dei
caratteri dallo standard input, se collegato (default) alla tastiera, si ottiene con ^D (CTRL-D).**
```
    cat > prova
```
```
    varie linee di prova
```
**45) Usando la ridirezione dello standard output del comando pwd e del comando ls -l, aggiungere tale output al
file prova precedentemente creato.**
```
    pwd >> prova
```
```
    ls -l >> prova
```
**46) Usando il comando-filtro cat con le opportune ridirezioni, creare una copia del file prova e dargli nome p.txt.**
```
    cat prova >> p.txt
```
**47) Usando il comando-filtro cat con l’opportuna ridirezione, controllare il contenuto finale del file prova.**
```
    cat < prova
```
**48) Usando il comando cat con la ridirezione dello standard output in append aggiungere il contenuto del file
prova al file p.txt almeno altre 5 volte in modo da avere un file che contenga molte linee. Verificare, poi, il
contenuto del file p.txt.**
```
    cat prova >> p.txt >> p.txt >> p.txt >> p.txt
```
```
    cat prova
```
## RIDIREZIONE *MORE*
**49) Usando la ridirezione dello standard input e il comando-filtro more, visualizzare nuovamente il contenuto del
file p.txt. Ricordarsi che per andare avanti di una videata si deve usare la barra spaziatrice, per avanzare di una
singola linea si deve usare il tasto enter (invio) e per uscire se non si vuole più proseguire si deve usare il tasto
q (QUIT).**
```
    more p.txt
```
**50) Verificare il comportamento del comando more, usando il comando more p\*.**
```
    more p*
```
## DIRITTI DELLE DIRECTORY
**51) Creare una sottodirectory nella propria HOME directory dandogli nome dir ed inserire in essa alcuni file;
quindi, eliminare, per l’utente corrente, il diritto di lettura sulla directory e verificare le azioni che si possono
fare e quelle che sono impedite.**
```
    mkdir dir
```
```
    cp f* dir
```
```
    chmod u-r dir
```
```
    [ ls: .: Permission denied ]
```
**52) Rimettere il diritto di lettura e procedere con l’eliminazione del diritto di scrittura e di nuovo verificare le azioni
che si possono fare e quelle che sono impedite.**
```
    chmod u+r-w dir
```
```
    [ Cannot open file for writing: Permission denied ]
```
**53) Rimettere il diritto di scrittura e procedere con l’eliminazione del diritto di esecuzione e di nuovo verificare le
azioni che si possono fare e quelle che sono impedite.**
```
    chmod u+w-x dir
```
```
    [ cd: permission denied: dir ]
```
**54) Provare anche ad eliminare due diritti alla volta, invece che uno, provando le varie combinazioni: eliminare
diritto di lettura e di scrittura; eliminare diritto di lettura e di esecuzione; eliminare diritto di scrittura e di
esecuzione.**
```
    chmod u-r-w dir
```
```
    chmod u-w-x dir 
```
```
    chmod u-r-x dir
```
