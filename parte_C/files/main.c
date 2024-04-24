#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define PERM 0644

int copyfile(char *f1, char * f2) { 
	int infile, outfile, nread;
	char buffer [BUFSIZ]; /* usato per i caratteri */

	if ((infile = open (f1, O_RDONLY)) < 0 ) {
		return 2;
	}

	/* ERRORE se non si riesce ad aprire in LETTURA il primo file */
	if ((outfile = creat(f2, PERM)) <0 ) {
		/* ERRORE se non si riesce a creare il secondo file */
		close(infile); 
		return 3; 
	}

	while ((nread = read(infile, buffer, BUFSIZ)) > 0 ) { 
		if (write(outfile , buffer, nread) < nread) { 
			/* ERRORE se non si riesce a SCRIVERE */
			close (infile); close (outfile); 
			return 4; 
		}
	}

	close (infile); 
	close (outfile);

	/* se arriviamo qui, vuol dire che tutto è andato bene */
	return 0;
}

int main(int argc, char **argv) { 
	int status;
	if (argc != 3) 	{ 
		/* controllo sul numero di argomenti */
		printf ("Errore: numero di argomenti sbagliato\n");
		exit (1); 
	}

	status = copyfile(argv[1], argv[2]);
	if (status != 0) {
		printf("Ci sono stati degli errori nella copia\n");
	}
	exit(status);
	
}
