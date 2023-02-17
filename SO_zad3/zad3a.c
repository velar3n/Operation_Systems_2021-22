/* 
 Program wykonujący zadanie 3a
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

/*  1. SIG_DFL - domyślna obsługa sygnału
    2. SIG_IGN - ignorowanie sygnału (bez 9. - SIG_KILL i 19. - SIG_STOP)
    3. SIG_obsluga - przechwycenie i własna obsługa sygnału (z listy sys_syglist)*/

/* kill - Sends a signal to a specified process, to all members of a specified process group, or to  all processes on the system*/

void SIG_obsluga(int nr_sygnalu){
    printf("\nOdebranie sygnału");
    printf("\nNumer sygnału: %d", nr_sygnalu);
    printf("\nNazwa sygnału: %s", sys_siglist[nr_sygnalu]);
    printf("\nPID: %d\n\n", getpid());
}

void print(){
    printf("\nOBSLUGA SYGNAŁÓW");
    printf("\nPID:%d PGID: %d", getpid(), getpgrp());
    printf("\nOCZEKIWANIE NA SYGNAŁ\n");
}

void printID(){
    printf("\nPID:%d \n\n", getpid());
}

int main(int argc, char *argv[]){
    char *end;
    int opcja = argv[1][0] -'0';
    int nr_sygnalu = strtol(argv[2], &end, 10);
    
    if(argc != 3){
        printf("Błędna liczba argumentów\n");
        exit(1);
    }

    switch(opcja){
        case 1:
            print();
            if (signal(nr_sygnalu, SIG_DFL) == SIG_ERR){
                perror("signal error");
                exit(EXIT_FAILURE);
                }
            break;

        case 2:
            printID();
            if (signal(nr_sygnalu, SIG_IGN) == SIG_ERR){
                print();
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            break;
        case 3:
            print();
            if (signal(nr_sygnalu, SIG_obsluga) == SIG_ERR){
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            break;
         default:
            printf("Niepoprawna metoda obsługi\n");
            exit(1);
    }

    pause(); /*suspends execution until any signal is caught*/

    return 0;
}

