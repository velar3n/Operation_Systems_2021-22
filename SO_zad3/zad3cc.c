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

extern const char * const sys_siglist[];

int main(int argc, char *argv[]){
    int i;

    char *end;
    int nr_sygnalu = strtol(argv[2], &end, 10);
    
    if(argc != 3){
        printf("Błędna liczba argumenów\n");
        exit(1);
    }
    
    signal(nr_sygnalu, SIG_IGN); 

    if(setpgid(0,0) == -1){
        perror("setpgid error");
    }
                
        for(i=0; i < 4; i++){
            switch(fork()){
                case -1:
                    perror("fork error");
                    exit(1);
                    break;
                case 0:
                    execv("./zad3a.x",argv);
                break;            
            }
        }
            
    if(wait(NULL) == -1){ 
        perror("wait error"); 
    } 
}

