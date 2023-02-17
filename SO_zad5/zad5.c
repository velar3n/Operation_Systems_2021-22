/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 23.04.2022

program wykonujący zadanie 5 (potoki)
========================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <signal.h>

char* fifo;

void usun(){
    unlink(fifo);
}

void sygnal(int signal){
    printf ("Sygnał przerwania\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){

    fifo = argv[3];

    if(argc != 6){
        printf("Błędna liczba argumentów\n");
        exit(1);
    }

    if(mkfifo(fifo, 0644) == -1){
        perror("Błąd tworzenia potoku");
        _exit(EXIT_FAILURE);
    }

    if(signal(SIGINT, sygnal) == SIG_ERR){
        perror("Błąd signal");
        exit(EXIT_FAILURE);
    }

    switch(fork()){
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            execv(argv[4], argv);
            _exit(1);
            break;
        default:
            break;
    }

    switch(fork()){
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            execv(argv[5], argv);
            exit(1);
            break;  
        default:
            break;    
    }

    if(wait(NULL) == -1){
        perror("Błąd wait");
        _exit(EXIT_FAILURE);
    }

    if(atexit(usun) != 0){
        perror("atexit error");
        _exit(EXIT_FAILURE);
    }
}

