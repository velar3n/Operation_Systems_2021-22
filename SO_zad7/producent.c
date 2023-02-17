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
#include "semafory.h"
#include "dzielona.h"

#define NELE 10 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 5 // Liczba elementow bufora

// Segment pamieci dzielonej - WAŻNE
typedef struct{
	char bufor[NBUF][NELE]; // Wspolny bufor danych
	int zapis;
	int odczyt;
} Segment_PD;

// argumenty [0] nazwa_programu [1] SEMAFOR_PRODUCENT [2] SEMAFOR_KONSUMENT [3] NAZWA_PD [4] PLIK_WE
int main (int argc, char *argv[]) {
	
	int plik, pamiec_dzielona, odczyt;
	Segment_PD *PD;
	sem_t *semafor_producent, *semafor_konsument;
	
	if(argc != 5){
		printf("Błąd: Podano niepoprawną liczbę argumentów\n");
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));
	
	if((plik = open(argv[4], O_RDONLY, 0644)) == -1){
		printf("Błąd otwarcia pliku in\n");
		exit(EXIT_FAILURE);
	}
	
	/*otwarcie semaforów i pamięci dzielonej*/
	semafor_producent = otworz_semafor(argv[1]);
	printf ("Producent: otwarto semafor producenta - deskryptor %p\n", (void *)semafor_producent);
	semafor_konsument = otworz_semafor(argv[2]);
	printf ("Producent: otwarto semafor konsumenta - deskryptor %p\n", (void *)semafor_konsument);
	
	pamiec_dzielona = otwieranie_pamieci(argv[3]);
	PD = (Segment_PD*) odwzorowanie_pamieci (pamiec_dzielona, sizeof(Segment_PD));
	printf ("Producent: pamięć dzielona %s - deskryptor %d - wielkość %ld\n\n", argv[3], pamiec_dzielona, sizeof(Segment_PD));
	
	PD->zapis = 0;
	
	while(1){ 				/*pętla nieskończona kończona przez break - zapis do pamięci dzielonej*/
		
		sleep(rand()%5+1);
		
		/* opuszczanie semafora */
		printf ("Producent: przed sekcją krytyczną semafora: %d\n", wartosc_semafor(semafor_producent));
		opusc_semafor(semafor_producent);

		/*czytanie z pliku do pamięci dzielonej*/
		odczyt = read(plik, PD->bufor[PD->zapis], NELE);

		if(odczyt == -1){
			printf("Błąd odczytu z pliku\n");
			exit(EXIT_FAILURE);
		} 
		if(odczyt != NELE){      						   /*koniec pętli while, zmiana na nullptr*/
			PD->bufor[PD->zapis][odczyt] = '\0';
			printf("\nProducent: koniec pliku\n");
			
			// podniesienie semafora konsumenta ostatni raz
			podnies_semafor (semafor_konsument);
			printf("Producent: po sekcji krytycznej semafora: %d\n", wartosc_semafor(semafor_konsument));
			break;
		}
		else{
			if(write(STDOUT_FILENO, PD->bufor[PD->zapis], NELE) == -1){
				perror("Błąd write na ekran");
				exit(EXIT_FAILURE);
			}
			printf("\n\nIndeks bufora: %d\n", PD->zapis);
		}

		/* inkrementacja indeksu*/
		PD->zapis = (PD->zapis+1) % NBUF;
		
		/* podniesienie semafora konsumenta*/
		podnies_semafor(semafor_konsument);
		printf("Producent: po sekcji krytycznej semafora: %d\n", wartosc_semafor(semafor_konsument));
	}
	
	if(close(plik) == -1){
		perror("Błąd zamknięcia pliku wyjścia");
		exit(EXIT_FAILURE);
	}
	
	/*zamknięcie pliku, pamięcie dzielonej i semaforów*/
	usuwanie_odwzor_pamieci(PD, sizeof(Segment_PD));
	
	zamknij_pamiec(pamiec_dzielona);
	zamknij_semafor(semafor_producent);
	zamknij_semafor(semafor_konsument);
	
	printf ("Producent: koniec procesu\n");
	
	return 0;
}