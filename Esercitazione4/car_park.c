#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

#define MAXSEM 256
// Maximum car limit: MAXN

#define MAXLINE 128
// Maximum string length for line in filepath: MAXLINE


int my_is_in(char element[MAXLINE], char array[MAXSEM][MAXLINE], int size)
{
	for(int i=0; i<size; i++)
	{
		int result = strcmp(element, array[i]);
		if(result==0)
		{
			return i; // Returns index
		}
	}

	return -1; // Epic fail!
}

int main(void)
{
	// Phase 1: Initialize stuff
	FILE * f;
	char pathname[] = "./catalog.txt"; // FIlepath

	f = fopen(pathname, "r");

	if(f==NULL)
	{
		printf("Fatal error: file %s does not exist\n", pathname);
		exit(-1);
	}

	// Global variables (relative to main)
	sem_t * semaphore_array[MAXSEM];
	char semaphore_names_array[MAXSEM][MAXLINE];
	int ctr = 0;

	{
		char buffer[MAXLINE];
		while(fgets(buffer, sizeof(buffer), f)!=NULL )
		{
			buffer[strlen(buffer)-1] = '\0';
			sem_t * new_semaphore = sem_open(buffer, O_CREAT | O_EXCL ,S_IREAD | S_IWRITE,1);
			if(new_semaphore == NULL)
				{
					// Semaphore already exists; open it without initial value
					sem_t * old_semaphore = sem_open(buffer, O_CREAT);
					semaphore_array[ctr] = old_semaphore;
					if(old_semaphore==NULL)
					{
						printf("Warning. Attempt in opening the semaphore failed.\n");
						continue;
					}
				}
			else
				{
					semaphore_array[ctr] = new_semaphore;
				}
			// Increment counter and insert semaphore name
			strcpy(semaphore_names_array[ctr], buffer);
			ctr++;

			if(ctr >= MAXSEM-1) {printf("Critical error: exceeded maximum slots. Interrupting database retrieval.\n"); break;}
		}

		fclose(f);
	}

	// Phase 2: Do stuff!
	int run=1;
	while(run)
	{
		char command[MAXLINE];
		char arg1[MAXLINE];
		char arg2[MAXLINE];

		printf("Command: ");
		fgets(command, sizeof(command), stdin);
		// Parses command in arg1, arg2
		command[strlen(command)-1] = '\0';
		sscanf(command, "%s %s", arg1, arg2);

{ // those brackets are an optical illusion

		if(strcmp("view", arg1)==0)
		{ // View mode
			for(int i=0; i<ctr; i++)
			{
				// name: semaphore_names_array[i] -> char[MAXLINE]
				// semaphore: semaphore_array[i] -> sem_t *
				char status[MAXLINE];
				int attempt;

				attempt = sem_trywait(semaphore_array[i]);

				if(attempt==-1)
				{ // Epic fail!
					strcpy(status, "busy");
				}
				else{ strcpy(status, "free"); sem_post(semaphore_array[i]); }
				printf("Car: %s, status: %s\n", semaphore_names_array[i], status);
			}
			continue;
		}

		if(strcmp(arg1, "lock")==0)
		{ // Lock mode
			int found;
			found = my_is_in(arg2, semaphore_names_array, ctr);
			if(found==-1)
			{
				printf("Cannot find car %s\n", arg2);
			}
			else
			{
				int attempt;
				attempt = sem_trywait(semaphore_array[found]);
				if(attempt == -1)
				{
					printf("Error. Car %s already locked\n", arg2);
				}
				else
				{
					printf("Car: %s is now locked\n", arg2);
				}
			}
			continue;
		}

		if(strcmp(arg1, "release")==0)
		{ // Release mode
			int found;
			found = my_is_in(arg2, semaphore_names_array, ctr);
			if(found==-1)
			{
				printf("Cannot find car %s\n", arg2);
				continue;
			}
			else
			{
				int sem_value;
				sem_getvalue(semaphore_array[found], &sem_value);
				if(sem_value >= 1){ printf("Error. Car %s already free\n", arg2); }
				else{ sem_post(semaphore_array[found]); printf("Car %s is now free\n", arg2); }
			}
			continue;
		}

		if(strcmp(arg1, "quit")==0)
		{
			run=0;
		}

		else
		{
			printf("Unknown Command\n");
			continue;
		}




}
	}

	// Phase 3: Exit
	for(int i=0; i<ctr; i++)
	{
		sem_close(semaphore_array[ctr]);
	}
	return 0;
}

