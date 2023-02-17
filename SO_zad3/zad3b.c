/* 
 Program wykonujący zadanie 3b
 ----------------------------------------------------------------------
 Autor: Natalia Kiełbasa                           Krakow, 03.04.2022
 ----------------------------------------------------------------------
*/ 

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

extern const char * const sys_siglist[];

int main(int argc, char *argv[]){
    char *end;
    int nr_sygnalu = strtol(argv[2], &end, 10);
    int ID = fork();
    
    if(argc != 3){
        printf("Błędna liczba argumentów\n");
        exit(1);
    }

    switch(ID){
            case -1:
                perror("fork error");
                exit(1);
                break;
            case 0:
                execv("./zad3a.x", argv);
                break;
            default:
                sleep(2);
                if(kill(ID, nr_sygnalu) == -1){
                    perror("signal error");
                }
        }

        sleep(2);
}

