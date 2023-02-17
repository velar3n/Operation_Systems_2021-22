/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 30.05.2022

program wykonujący zadanie 7
========================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include "dzielona.h"
#include "semafory.h"

#define NELE 20 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5 // Liczba elementow bufora

#define SCIEZKA "./"
#define SUROWCE "surowce.txt"
#define SKONSUMOWANE "skonsumowane.txt"
#define SEMPROD "/sem_producent"
#define SEMKONS "/sem_konsument"
#define PAMIEC "/prod_kons_pd"

// Segment pamieci dzielonej
typedef struct {
	char bufor[NBUF][NELE]; // Wspolny bufor danych
	int zapis;
	int odczyt;
} SegmentPD;

void sygnal(int signal){
	printf("\nSygnał przerwania, usuwanie semaforów i pamięci dzielonej\n");
	exit(EXIT_SUCCESS);
}

void usun_sem(void){
	usuwanie_pamieci(PAMIEC);
	usun_semafor(SEMPROD);
	usun_semafor(SEMKONS);
}

// argumenty [0] nazwa_programu  [1] program_producent  [2] program_konsument
int main (int argc, char *argv[]){
	
	int pamiec_dzielona, stat_lock, i;
	char sciezka_prod[] = "./producent.x";
	char sciezka_kons[] = "./konsument.x";
	sem_t *semafor;
	
	// sprawdzenie poprawności argumentów
	if(argc != 3){
		printf("Błąd: Podano niepoprawną liczbę argumentów\n");
		exit(EXIT_FAILURE);
	}

	if(atexit(usun_sem) != 0){
		perror("atexit error");
		_exit(EXIT_FAILURE);
	}
		
	if(signal (SIGINT,sygnal) == SIG_ERR){
		perror("Błąd signal");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));
	
	semafor = stworz_semafor(SEMPROD, NBUF);
	printf("\nUtworzono semafor producenta %p o wartości %d\n", (void *)semafor, wartosc_semafor(semafor));
	semafor = stworz_semafor(SEMKONS, 0);
	printf("Utworzono semafor producenta %p o wartości %d\n", (void *)semafor, wartosc_semafor(semafor));
	
	pamiec_dzielona = stworzenie_pamieci(PAMIEC);
	rozmiar_pamieci(pamiec_dzielona, sizeof(SegmentPD));
	printf("Utworzono pamięć dzieloną %s o deskryptorze %d i rozmiarze %ld\n\n", PAMIEC, pamiec_dzielona, sizeof(SegmentPD));
	
	for(i=0; i<2; i++){
		switch(fork()){
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				if(i == 0){
					execl(sciezka_prod, argv[1], SEMPROD, SEMKONS, PAMIEC, SUROWCE, NULL); /* uruchamia producent.c */
					perror("błąd execl");
					exit(EXIT_FAILURE);
				} else{
					execl(sciezka_kons, argv[2], SEMPROD, SEMKONS, PAMIEC, SKONSUMOWANE, NULL); /* uruchamia konsument.c */
					perror("błąd execl");
					exit(EXIT_FAILURE);
				}
				break;
				
			default:
				break;	
		}
	}
	
	if(wait(&stat_lock) == -1){				/*na procesy potomne waitujemy*/
		perror("Błąd wait");
		_exit(EXIT_FAILURE);
	}
	
	if(wait(&stat_lock) == -1){
		perror("Błąd wait");
		_exit(EXIT_FAILURE);
	}
	
	zamknij_pamiec(pamiec_dzielona);
		
	printf("\n\nProgram główny: koniec procesu\n");
	
	return 0;
}