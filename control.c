#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/types.h>

#define KEY 10982

int main( int argc, char *argv[]){
	if(argc < 2){ //invalid number of args
		printf("not enough arguments: 1 or more arguments required\n");
	}
	else{
		if(!strcmp(argv[1], "-c") && argc == 3){ //create semaphore and set value
			//printf("%d\n", semdes);
			int semdes;
			if( semdes = semget(KEY, 1, IPC_EXCL | IPC_CREAT | 0644) != -1){
				//printf("semdes: %d\n", semdes);
				semdes = semget(KEY, 0, 0);
				int val;
				sscanf(argv[2], "%d", &val);
				//printf("%d\n", val);
				union semun semopts;
				semopts.val = val;
				semctl(semdes, 0, SETVAL, semopts);
				printf("semaphore created: %d\nvalue set: %d\n", semdes, val);
			}
			else{
				printf("semaphore already exists\n");
			}
		}
		else if(!strcmp(argv[1], "-v") && argc == 2){ //View the value of semaphore
			int semdes = semget(KEY, 0, 0);
			//printf("semdes: %d\n", semdes);
			int val = semctl(semdes, 0, GETVAL);
			printf("semaphore value: %d\n", val);
		}
		else if(!strcmp(argv[1], "-r") && argc == 2){ //Remove the semaphore
			int semdes = semget(KEY, 0, 0);
			//printf("semdes: %d\n", semdes);
			int val = semctl(semdes, 0, IPC_RMID);
			printf("semaphore removed: %d\n", val);
		}
		else{ //invalid arguments
			printf("invalid argument: %s\n", argv[1]);
		}
	}
}
