/* 
 Program wykonujący zadanie 2 - wypisywanie ID procesów potomnych
 ----------------------------------------------------------------------
 Autor: Natalia Kiełbasa                           Krakow, 26.03.2022
 ----------------------------------------------------------------------
*/ 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

    printf("\nUID: %i\nGID: %i\nPID: %i\nPPID: %i\nPGID: %i\n", getuid(), getgid(), getpid(), getppid(), getpgrp());

    return 0;

}