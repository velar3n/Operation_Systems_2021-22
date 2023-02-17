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

void wyjscie(void){
	kolejkaUsuwanie(KOLEJKA_NAZWA);
}

void sygnal(int signal){
	printf ("\nSygnał przerwania, usuwanie kolejki\n");
	exit(EXIT_SUCCESS);
}

int main () {
	
	char string[30], dzialnie, wynik_dzialania[30];
	int PID_klienta, lb1, lb2, wynik;
	mqd_t kolejka_desk;
	mqd_t odpowiedz;

	srand(time(NULL));
	
	kolejka_desk = kolejkaStworzenie(KOLEJKA_NAZWA, O_RDONLY);
	printf ("Stworzono kolejkę \"%s\" deskryptor: %d\n", KOLEJKA_NAZWA, kolejka_desk);
	
	if(atexit(wyjscie) != 0){
		perror("atexit error");
		exit(EXIT_FAILURE);
	}
	
	if(signal(SIGINT, sygnal) == SIG_ERR){
		perror("Błąd signal");
		exit(EXIT_FAILURE);
	}
	
	while (1){
		kolejkaOdbieranie(kolejka_desk, string, NULL);										/*odbieranie wiadomości od klienta*/
		
		sscanf(string, "%d %d%c%d", &PID_klienta, &lb1, &dzialnie, &lb2);
		
		printf("Działanie od klienta %d: %d %c %d\n", PID_klienta, lb1, dzialnie, lb2);
		
		if(dzialnie == '+'){
			wynik = lb1 + lb2;
			sprintf(wynik_dzialania, "%d", wynik);
		}else if(dzialnie == '-'){
			wynik = lb1 - lb2;
			sprintf(wynik_dzialania, "%d", wynik);
		}else if(dzialnie == '*'){
			wynik = lb1 * lb2;
			sprintf(wynik_dzialania, "%d", wynik);
		}else if(dzialnie == '/'){
			wynik = lb1 / lb2;
			sprintf(wynik_dzialania, "%d", wynik);
		}else{
			sprintf(wynik_dzialania, "Niedozwolone działanie");
		}
		
		sleep(rand()%4+1);
		
		sprintf(string, "/%d", PID_klienta);
		odpowiedz = kolejkaOtwarcie(string, O_WRONLY);
		
		printf("Wysyłanie odpowiedzi %s do procesu %d\n", wynik_dzialania, PID_klienta);
		kolejkaWysylanie(odpowiedz, wynik_dzialania, 1);
		kolejkaZamykanie(odpowiedz);
	}
	
	kolejkaUsuwanie(KOLEJKA_NAZWA);
	
	printf("\n\nSerwer: koniec procesu\n");
	
	return 0;
}



/* export DISPLAY=$(ip route|awk '/^default/{print $3}'):0.0 */