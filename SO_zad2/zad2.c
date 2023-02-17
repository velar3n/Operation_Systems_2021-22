/* 
 Program wykonujący zadanie 2
 ----------------------------------------------------------------------
 Autor: Natalia Kiełbasa                           Krakow, 26.03.2022
 ----------------------------------------------------------------------
*/ 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){

	int i;

	if(argc!=3){
        printf("Nieprawidłowa liczba argumentów\n");
        exit(1);
    }

	printf("\nProces macierzysty: \n");
	printf("UID: %i\nGID: %i\nPID: %i\nPPID: %i\nPGID: %i\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
	printf("\n\nProcesy potomne: \n");

	for(i=0; i<3; i++){

		switch(fork()){

			case -1: 
				perror("fork error");
				exit(1);
				break;
			case 0:
				execlp(argv[1], argv[2], NULL);
				perror("execlp error");
				exit(2);
				break;
			default:
				wait(NULL);
		}
		
	}

	return 0;

}