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
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#define SCIEZKA "./"

/* powiela odpowiednią ilość razy program inkrementator.c */


char nazwa_sem[20], bufor[10];
bool synchronizacja;
int stat_lock, lb_inkrement, plik, i, odczyt, wartosc_semafora;

void wyjscie(void){
	if(synchronizacja){
		usun_semafor(nazwa_sem);
	}
}

void wyjscie_syg(int signal){
	if(synchronizacja){
		printf("Sygnał przerwania\n");
		usun_semafor(nazwa_sem);
	}
	_exit(EXIT_SUCCESS);
}

/* 1-inkrementator.c;  2-lb_inkrementacji (procesów);  3-lb_sekcji_krytycznych;  4-plik;  5-nazwa_semafora;  6-synchronizacja */
int main (int argc, char *argv[]){
	
	if(argc != 7){
		printf ("Błąd: podano niepoprawną liczbę argumentów!\n");
		exit (EXIT_FAILURE);
	}
	
	if(atexit(wyjscie) != 0){
		perror("atexit error");
		exit(EXIT_FAILURE);
	}
	
	if(signal (SIGINT, wyjscie_syg) == SIG_ERR){
		perror("Błąd sygnału");
		exit(EXIT_FAILURE);
	}
	
	char temp[strlen(SCIEZKA) + strlen(argv[1]) + 1];
	lb_inkrement = atoi(argv[2]);
	strcpy(nazwa_sem, argv[5]);
	
	if(atoi(argv[6]) == 0){
		synchronizacja = false;
	} else{
		synchronizacja = true;
	}
	
	if((plik = open (argv[4], O_WRONLY | O_CREAT, 0644)) == -1){
		printf("Błąd otwarcia pliku");
		exit(EXIT_FAILURE);
	}
	
	if(write(plik, "0", 2) == -1){
		perror("Błąd wpisywania do pliku");
		exit(EXIT_FAILURE);
	}
	
	if(close(plik) == -1){
		perror ("Błąd zamknięcia pliku");
		exit (EXIT_FAILURE);
	}
	
	if(synchronizacja){
		sem_t *semafor = stworz_semafor(nazwa_sem);
		wartosc_semafor(semafor, &wartosc_semafora);
		printf("Utworzono semafor %s o wartości %d\n\n", nazwa_sem, wartosc_semafora);
	}
	
	for(i=0; i<lb_inkrement; i++){													/* uruchomienie inkrementator.c */
		switch(fork()){
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				sprintf(temp, "%s%s", SCIEZKA, argv[1]);
				execl(temp, argv[1], argv[3], argv[4], argv[5], argv[6], NULL);
				perror("execl error");
				exit(EXIT_FAILURE);
				break;
			default:
				break;				
		}
	}
	
	for(i=0; i<lb_inkrement; i++){
		if(wait(&stat_lock) == -1){
			perror ("Błąd wait");
			exit (EXIT_FAILURE);
		}
	}
	
	if((plik = open(argv[4], O_RDONLY, 0644)) == -1){ 								/* odczytanie wartości z pliku */
		printf("Błąd otwarcia pliku");
		exit(EXIT_FAILURE);
	}
	
	odczyt = read(plik, &bufor, 10);
	if(odczyt == -1){
		printf("Błąd odczytu z pliku\n");
		exit(EXIT_FAILURE);
	}else if(odczyt == 0){
		printf("Plik jest pusty");
		exit(EXIT_FAILURE);
	}else{
		bufor[odczyt] = '\0';
		if(atoi(bufor) == (atoi(argv[2]) * atoi(argv[3]))){
			printf("\nInkrementacja zakończona: %s\n", bufor);
		}else{
			printf("\nInkremenatcja nie powiodła się");
		}
	}

	if(close(plik) == -1){
		perror ("Błąd zamknięcia pliku");
		exit (EXIT_FAILURE);
	}
	return 0;
}