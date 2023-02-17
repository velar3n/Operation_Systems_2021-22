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

int main(int argc, char *argv[]){

    char* path_out = argv[2];
    char* fifo = argv[3];
    char byte_kons[32];
    int fileout, fifoout, byte_readpipe;

    if(argc != 6){
        printf("Błędna liczba argumentów\n");
        exit(1);
    }

    if((fileout = open(path_out, O_WRONLY | O_CREAT, 0644)) == -1){
        perror("Błąd otwarcia pliku out");
        exit(EXIT_FAILURE);
    }
    if((fifoout = open(fifo, O_RDONLY)) == -1){
        perror("Błąd otwarcia potoku");
        exit(EXIT_FAILURE);
    }
    
    while((byte_readpipe = read(fifoout, byte_kons, 13)) > 0){
        printf("Odebranie danych z potoku:\n");
        if(write(1, byte_kons, byte_readpipe) == -1){
            perror("Błąd wypisania na ekran");
        }
        printf("\n");
        if(write(fileout, byte_kons, byte_readpipe) == -1){
            perror("Błąd wypisania do pliku");
        }
        sleep(rand()%3+1);
    }

    if(byte_readpipe == -1){
        perror("Błąd czytania z potoku");
    }
        
    printf("\nDane skopiowane pomyślnie!\n");

    if(close(fileout) == -1){
        perror("Błąd zamknięcia pliku out");
        exit(EXIT_FAILURE);
    }
    
    if(close(fifoout) == -1){
        perror("Błąd zamknięcia potoku");
        exit(EXIT_FAILURE);
    }   
}

