#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 512
#define MAXPRC 256
#define MAXLINES 128
// eventually other libraries...

int main(int argc, char* argv[])
{
	// Phase 0: Check arguments for validity
	FILE* f;

	if(argc != 4)
	{
		printf("Usage: ./parallel [filename] [n] [command] \n");
		exit(-1);
	}

	if(atoi(argv[2]) <= 0)
	{
		printf("Usage: ./parallel [filename] [n] [command], with [n] as a valid integer \n");
		exit(-1);
	}

	if (fopen(argv[1], "r") == NULL)
	{
		printf("File %s not readable", argv[1]);
		exit(-1);
	}


	// Note: command won't be checked for

	// Phase 1: Command replacement
	char* to_replace;
	char command[MAXN];
	char commands[MAXLINES][MAXN];
	char buffer[MAXN];
	char preserved[MAXN];
	int ctr=0;
	f = fopen(argv[1], "r");

	while(fgets(buffer,sizeof(buffer), f)!=NULL)
	{
		// remove newline from buffer
		buffer[strlen(buffer)-1] = '\0';

		// magic (should check for string length, but...)
		strcpy(command, argv[3]);
		to_replace = strstr(command, "%");
		strcpy(preserved, to_replace);
		strcpy(to_replace, buffer);
		strcat(command, preserved+1);

		if(ctr>=MAXN){ printf("Maximum commands limit exceeded.\n"); exit(-1); }
		strcpy(commands[ctr], command);
		ctr++;
	} // Note: ctr keeps the number of commands to run

	// Phase 2: Forking
	int pipes[MAXPRC][2];

	int n = atoi(argv[2]);
	for(int i=0; i<n;i++)
	{
		int* pipe_n = pipes[i];
		pipe(pipe_n);

		if(fork()){ // Father
			close(pipe_n[0]);
			for(int j=i; j<n; j+=n)
			{
				write(pipe_n[1], commands[j], MAXN);
			}
			close(pipe_n[1]);
			continue; // Continues reproducing

		}

		else
		{ // Son
			close(pipe_n[1]);
			char to_execute[MAXN];
			while(read(pipe_n[0], to_execute, MAXN)>0 ){ system(to_execute); }
			exit(0);
		}
	}

	// Phase 3: Wait for all children to die
	while(wait(NULL)>0){}
	return 0;
}

