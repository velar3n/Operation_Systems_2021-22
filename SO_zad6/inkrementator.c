/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 14.05.2022

program wykonujący zadanie 6 - semafory
========================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "semafory.h"
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

/* odczyt liczby z pliku - inkrementacja - zapis nowej liczby do pliku */

/* 1-lb_sekcji_kryt; 2-plik_we_wy; 3-nazwa_semafora; 4-synchronizacja */


int main(int argc, char *argv[]){
	
	int odczyt, i, lb, lb_sekcji_kryt, wartosc_sem, plik;
	char bufor[100];
	sem_t *semafor;
	bool synchronizacja;

	lb_sekcji_kryt = atoi(argv[1]);
	
	if(argc != 5){
		printf("Podano niepoprawną liczbę argumentów!\n");
		_exit(EXIT_FAILURE);
	}
	
	if(atoi(argv[4]) == 0){
		synchronizacja = false;
	} else{
		synchronizacja = true;
		semafor = otworz_semafor(argv[3]);
	}
	
	for(i=0; i<lb_sekcji_kryt; i++){
		
		srand(time(NULL));
		sleep(rand()%4+1);
		
		if(synchronizacja){
			wartosc_semafor(semafor, &wartosc_sem);
			printf("\tPID %d przed sekcją krytyczną semafora: %d\n", getpid(), wartosc_sem);
			opusc_semafor(semafor);
		}
		
		if((plik = open(argv[2], O_RDONLY, 0644)) == -1){
			printf("Błąd otwarcia pliku");
			_exit(EXIT_FAILURE);
		}
		
		odczyt = read(plik, &bufor, 10);

		if(odczyt == -1){
			printf("Błąd odczytu z pliku\n");
			_exit(EXIT_FAILURE);
		} else if(odczyt == 0){
			break;
		} else{
			bufor[odczyt] = '\0';
			wartosc_semafor(semafor, &wartosc_sem);
			printf("PID %d semafor %d odczytany numer: %s Sekcja krytyczna: %d", getpid(), wartosc_sem, bufor, i);
		}
		
		if(close (plik) == -1){
			perror("Błąd zamknięcia pliku");
			exit(EXIT_FAILURE);
		}
		
		lb = atoi(bufor);
		lb++;

		sprintf(bufor, "%d", lb);
		printf("\nNumer: %d\n", lb);
		
		sleep(rand()%4+1);
		
		if((plik = open (argv[2], O_WRONLY | O_CREAT, 0644)) == -1){
			printf("Błąd otwarcia pliku");
			_exit(EXIT_FAILURE);
		}
		
		if(write(plik, &bufor, strlen(bufor)) == -1){
			perror("Błąd wpisywania do pliku");
			_exit(EXIT_FAILURE);
		}
		
		if(close(plik) == -1){
			perror ("Błąd zamknięcia pliku");
			exit (EXIT_FAILURE);
		}
		
		if(synchronizacja){
			podnies_semafor(semafor);
			wartosc_semafor(semafor, &wartosc_sem);
			printf ("\tPID %d po sekcji krytycznej semafora: %d\n", getpid(), wartosc_sem);
		}
	}
	if(synchronizacja){
		zamknij_semafor(semafor);
	}
	return 0;
}