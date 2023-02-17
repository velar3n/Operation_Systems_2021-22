/* 
 Program wykonujący zadanie 3c
 ----------------------------------------------------------------------
 Autor: Natalia Kiełbasa                           Krakow, 03.04.2022
 ----------------------------------------------------------------------
*/ 

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<wait.h>
extern const char * const sys_siglist[];

int main(int argc, char *argv[]){
    int ID, d;
    char *end;
    int nr_sygnalu = strtol(argv[2], &end, 10);
    
    if(argc != 3){
        printf("Błędna liczba argumentów\n");
        exit(1);
    }
    
    printf("Grupa macierzysta: %d\n", getpgrp());

    switch(ID = fork()){
            case -1:
                perror("fork error");
                exit(1);
                break;

            case 0:
                execv("./zad3cc.x", argv);
                break;
        }

    sleep(3);

    if(killpg(ID, nr_sygnalu) == -1){
        perror("Signal error");
    }
        
    d = wait(NULL);

    if(d == -1){
        perror("wait error");
    }

    printf("\nZakończony potomek z wait: %d\n\n",d);
}

