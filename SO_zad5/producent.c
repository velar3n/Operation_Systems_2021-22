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

    char* path_in = argv[1];
    char* fifo = argv[3];
    char byte_prod[32];
    int filein, fifoin, read_bytes;

    if(argc != 6){
        printf("Błędna liczba argumentów\n");
        exit(1);
    }

    if((filein = open(path_in, O_RDONLY)) == -1){
        perror("Błąd otwarcia pliku in");
        exit(EXIT_FAILURE);
    }
    if((fifoin = open(fifo, O_WRONLY | O_CREAT, 0644)) == -1){
        perror("Błąd otwarcia potoku");
        exit(EXIT_FAILURE);
    }

    while((read_bytes = read(filein, byte_prod, 32)) > 0){
            sleep(0.5);
            printf("Wpisanie danych do potoku:\n");
            if(write(1, byte_prod, read_bytes) == -1){
                perror("Błąd wypisania danych na ekran");
            }
            printf("\n");
            if(write(fifoin, byte_prod, read_bytes) == -1){
                perror("Błąd wpisania danych do potoku");
            }
            sleep(rand()%15+1);
    }

    if(read_bytes == -1){
        perror("Błąd czytania z pliku:");
    }

    if(close(filein) == -1){
        perror("Błąd zamknięcia pliku in");
        exit(EXIT_FAILURE);
    }
    
    if(close(fifoin) == -1){
        perror("Błąd zamknięcia potoku");
        exit(EXIT_FAILURE);
    }    
}

