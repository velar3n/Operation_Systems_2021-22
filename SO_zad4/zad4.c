/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 11.04.2022

program wykonujący zadanie 4 (potoki)
========================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    int filedes[2];                                              /*deskryptory plików do pipe - 0: zapis, 1:odczyt*/
    int filein, fileout, byte_readpipe, read_bytes;
    char byte_prod[32], byte_kons[32];

    char* path_in = argv[1];
    char* path_out = argv[2];

    if(argc != 3){
        printf("Błędna liczba argumentow\n");
        exit(1);
    }

    if(pipe(filedes) == -1){
        perror("Błąd tworzenia potoku:");
    }

    if((filein = open(path_in, O_RDONLY)) == -1){                   /*otwarcie pliku do czytania*/
        perror("Błąd otwarcia pliku in");
    }
    if((fileout = open(path_out, O_WRONLY | O_CREAT, 0644)) == -1){ /*otwarcie pliku do pis | stwórz go jeśli nie istnieje*/
        perror("Błąd otwarcia pliku out");                          /* 0644 - prawa dostępu rw-r---r--- */
    }
    
    switch(fork()){
        case -1:
            perror("fork error");
            exit(1);
            break;

        case 0:
            if(close (filedes[1]) == -1){
                perror ("Błąd zamknięcia potoku");
                exit (EXIT_FAILURE);
            }

            while((byte_readpipe = read(filedes[0], byte_kons, 13)) > 0){
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

            if(close (filedes[0]) == -1){
                perror ("Błąd zamknięcia potoku");
                exit (EXIT_FAILURE);
            }
            exit(1);
            break;

        default:
            if(close (filedes[0]) == -1){
                perror ("Błąd zamknięcia potoku");
                exit (EXIT_FAILURE);
            }
            while((read_bytes = read(filein, byte_prod, 32)) > 0){
                    sleep(0.5);
                    printf("Wpisanie danych do potoku:\n");
                    if(write(1, byte_prod, read_bytes) == -1){
                        perror("Błąd wypisania danych na ekran");
                    }
                    printf("\n");
                    if(write(filedes[1], byte_prod, read_bytes) == -1){
                        perror("Błąd wpisania danych do potoku");
                    }
                    sleep(rand()%15+1);
            }
            if(read_bytes == -1){
                perror("Błąd czytania z pliku:");
            }
            if(close (filedes[1]) == -1){
                perror ("Błąd zamknięcia potoku");
                exit (EXIT_FAILURE);
            }
            break;
        }

    printf("Dane skopiowane pomyślnie!\n");

    if(close(filein) == -1){
        perror ("Błąd zamknięcia pliku in");
        exit (EXIT_FAILURE);
    }

    if(close(fileout) == -1){
        perror ("Błąd zamknięcia pliku out");
        exit (EXIT_FAILURE);
    }
}

