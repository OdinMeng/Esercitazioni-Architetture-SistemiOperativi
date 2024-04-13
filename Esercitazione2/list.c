#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h>
#include <grp.h>

#define MAXN 256


int stampa_dir(char *path) // Stampa ricorsivamente i contenuti della cartella data
{
	DIR * d = opendir(path);
	if(d==NULL)
	{
		printf("Warning: Errore nella lettura del directory. Chiusura del programma \n");
		exit(1);
	}
	// --- Codice principale
	struct dirent* entry; // directory name
	struct stat buf; // metadati
	int recursive;
	char type[MAXN];
	while( (entry = readdir(d) ) != NULL)
	{
		char filepath[MAXN];
		if( strlen(filepath) + strlen(entry->d_name) +1 >= MAXN)
		{
			printf("Lunghezza stringa andato oltre il massimo. Programma terminato. \n");
			exit (1);
		} // Se ottengo stringhe vanno oltre il buffer consentito, esco
		strcpy(filepath, path);
		strcat(filepath, "/");
		strcat(filepath, entry->d_name);
			// concateno stringhe finchè posso

		// Trattamento a seconda se ho file o path o symlink o FIFO (?) o coso malformato
		if( lstat(filepath, &buf) < 0)
		{
			printf("Errore nella lettura del file. Uscita. \n");
			exit (1);
		}

		recursive=0;
		if (S_ISREG(buf.st_mode) )
		{
			// ho file normale
			strcpy(type, "file");
			// Info interessati: Inode, type, size, owner, group, node (path)
		}

		else if (S_ISDIR(buf.st_mode))
		{
			// ho direttorio
			recursive = 1;
			strcpy(type, "directory");
			if(strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0){ continue; } // evito ., .. sennò cicli infiniti ; alternativamente posso ignorarli del tutto
		}

		else if (S_ISLNK(buf.st_mode))
		{
			strcpy(type, "symbolic link");
			// ho link simbolico; se è un link ad una cartella NON lo visito, per evitare cicli infiniti. Altrimenti lo visito
		}

		else if (S_ISFIFO(buf.st_mode))
		{
			strcpy(type, "FIFO");
			// ho FIFO, non so che voglia dire
		}

		else
		{
			continue; //ignoro e skippo!
		}

		// Find owner and group name
		struct passwd *user = getpwuid(buf.st_uid);
		char *owner = user->pw_name; // Assegno puntatori a puntatori

		struct group *gr = getgrgid(buf.st_gid);
		char *group1 = gr->gr_name;

                printf("Node: %s \n\tInode: %ld \n\tType: %s \n\tSize: %ld \n\tOwner: %ld %s \n\tGroup: %ld %s \n\n",filepath, (long int)buf.st_ino, type, (long int)buf.st_size, (long int)buf.st_uid, owner,
			(long int)buf.st_gid, group1);
		if(recursive){ stampa_dir(filepath); }
	}
	int closedir(DIR *dir);
	// ---
	return 0;
}


int main(int argc, char * argv[])
{
	struct stat buf; // Info sul file
    	if (argc!=2)
	{
       		 printf("Specifica un path\n");
       		 return 1;
  	 }

    	if ( stat(argv[1], &buf) < 0)
	{
		printf("Errore nella lettura del file/cartella\n");
		exit (1);
	}

else{ // se va tutto bene...
	if (!S_ISDIR(buf.st_mode))
	{
		printf("Errore: il path specificato non è una directory \n");
		exit (1);
	}
	else
	{
		stampa_dir(argv[1]);
	}
	return 0;
}

}
