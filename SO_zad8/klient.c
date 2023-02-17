/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 05.06.2022

program wykonujący zadanie 8
========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>

#include "kolejki.h"

mqd_t serwer;


/*klient - tworzy kolejkę do odbierania komunikatów od serwera
	wysyła żądanie wykonania działania do serwera, poprzez wpisanie go do kolejki z której serwer je odbiera 
*/


void wyjscie(void) {
	kolejkaZamykanie(serwer);
}

void sygnal_wyjscie(int signal){
	printf ("\nSygnał przerwania, zamykanie kolejki\n");
	exit(EXIT_SUCCESS);
}

int main () {
	
	char kolejka_klient_nazwa[10], odczyt[30], string[40];
	mqd_t kolejka_klient;
	
	sprintf(kolejka_klient_nazwa, "/%d", getpid());
	

	sleep (1);
	
	serwer = kolejkaOtwarcie(KOLEJKA_NAZWA, O_WRONLY);
	printf ("Otwarcie kolejki \"%s\", deskryptor %d\n", KOLEJKA_NAZWA, serwer);
	
	if(atexit(wyjscie) != 0){
		perror("atexit error");
		_exit(EXIT_FAILURE);
	}
	
	if(signal(SIGINT,sygnal_wyjscie) == SIG_ERR){
		perror("Błąd signal");
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));
	sleep(rand()%4+1);
	
	while(1){
		printf("Proszę wpisać działanie na dwóch liczbach: \n");

		if(scanf("%s", odczyt) == EOF){										/*zakończenie przez Ctrl-D*/
			printf ("Koniec odczytu działań\n");
			exit(EXIT_SUCCESS);
		}

		sprintf(string, "%d %s", getpid(), odczyt);
		
		kolejkaWysylanie(serwer, string, 1);								/*wysyłanie wiadomości do serwera*/
		printf ("\nWysłano zapytanie do serwera");
		
		kolejka_klient = kolejkaStworzenie(kolejka_klient_nazwa, O_RDONLY);
		
		printf ("Oczekiwanie na odpowiedź z serwera\n");

		kolejkaOdbieranie(kolejka_klient, string, NULL);					/*odbieranie wiadomości przez serwer*/
		printf ("Odpowiedź z serwera: %s\n\n", string);

		kolejkaZamykanie(kolejka_klient);
		kolejkaUsuwanie(kolejka_klient_nazwa);
		
		sleep(rand()%4+1);
	}
	
	kolejkaZamykanie(serwer);
		
	printf ("\n\nKoniec: proces klienta\n");
	
	return 0;
}