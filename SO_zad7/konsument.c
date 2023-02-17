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

// Segment pamieci dzielonej
typedef struct{
	char bufor[NBUF][NELE]; // Wspolny bufor danych
	int zapis;
	int odczyt;
} Segment_PD;

int koniec(Segment_PD *PD){
	int i;
	for(i = 0; i < NELE; i++){
		if(PD->bufor[PD->odczyt][i] == '\0'){
			return 1;
		}
	}
	return 0;
}

// argumenty [0] nazwa_programu [1] SEMAFOR_PRODUCENT [2] SEMAFOR_KONSUMENT [3] NAZWA_PD [4] PLIK_WY
int main(int argc, char *argv[]){
	
	int plik, pamiec_dzielona;
	Segment_PD *PD;
	sem_t *semafor_producent, *semafor_konsument;
	
	// sprawdzenie poprawności argumentów
	if(argc != 5){
		printf("Błąd: Podano niepoprawną liczbę argumentów\n");
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));
	
	if((plik = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
		printf("Błąd otwarcia pliku do zapisu");
		exit(EXIT_FAILURE);
	}
	
	/*otwarcie semaforów i pamięci dzielonej*/
	semafor_producent = otworz_semafor(argv[1]);
	printf("Konsument: otwarto semafor producenta %s deskryptor %p\n", argv[1], (void *)semafor_producent);
	semafor_konsument = otworz_semafor(argv[2]);
	printf("Konsument: otwarto semafor konsumenta %s deskryptor %p\n", argv[2], (void *)semafor_konsument);
	
	pamiec_dzielona = otwieranie_pamieci(argv[3]);
	PD = (Segment_PD *) odwzorowanie_pamieci (pamiec_dzielona, sizeof(Segment_PD));
	printf ("Konsument: pamięć dzielona %s - deskryptor %d - wielkość %ld\n\n", argv[3], pamiec_dzielona, sizeof(Segment_PD));

	PD->odczyt = 0;
	
	/* zapisywanie skosumowanych produktów do plk */
	while(1){
		
		sleep(rand()%5+1);
		
		/* opuszczanie semafora */
		printf("Konsument: przed sekcją krytyczną semafora: %d\n", wartosc_semafor(semafor_konsument));
		opusc_semafor(semafor_konsument);

		/* czytanie z pamięci do pliku */
		if(!koniec(PD)){

			/* kopiowanie danych */
			if(write(plik, PD->bufor[PD->odczyt], NELE) == -1){
				perror("Błąd write do potoku");
				exit(EXIT_FAILURE);
			}
			if(write(STDOUT_FILENO, PD->bufor[PD->zapis], NELE) == -1){
				perror("Błąd write na ekran");
				exit(EXIT_FAILURE);
			}
			printf("\n\nIndeks bufora odczyt: %d\n", PD->odczyt);
		} else {
			if(write(plik, PD->bufor[PD->odczyt], strlen(PD->bufor[PD->odczyt])) == -1){
				perror("Błąd write do potoku");
				exit(EXIT_FAILURE);
			}
			printf("Konsument: koniec odczytu\n");

			podnies_semafor(semafor_producent);
			printf("\nKonsument: po sekcji krytycznej semafora: %d\n", wartosc_semafor (semafor_producent));
			
			break;
		}
		
		PD->odczyt = (PD->odczyt+1) % NBUF;
		
		podnies_semafor(semafor_producent);
		printf("Konsument: po sekcji krytycznej semafor: %d\n", wartosc_semafor (semafor_producent));
	}
	
	if(close(plik) == -1){
		perror("Błąd zamknięcia pliku wyjścia");
		exit(EXIT_FAILURE);
	}
	
	usuwanie_odwzor_pamieci(PD, sizeof(Segment_PD));
	
	zamknij_pamiec(pamiec_dzielona);
	zamknij_semafor(semafor_konsument);
	zamknij_semafor(semafor_producent);
	
	printf("Konsument: koniec procesu\n");
	
	return 0;
}