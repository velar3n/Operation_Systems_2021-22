/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 06.06.2022

program wykonujący zadanie 9
========================================================================
*/

#define _REENTRANT			/*kod wielokrotnego użytku*/
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "watki.h"

#define max_lb_watkow 10

/* program implementuje problem wzajemnego wykluczania wątków z użyciem muteksów
	globalna liczba jest inkrementowana przez wątki, a muteks zabezpiecza przed jednoczesnym dostępem dwóch wątków do zasobu dzielonego */

int lb;
unsigned int lb_watkow, lb_sekcji;
pthread_t watki[max_lb_watkow];
pthread_mutex_t mutex;

void kursor(unsigned x, unsigned y){
	printf("\033[%d;%dH\033[2K", y, x);
}

void *watek_start(void *funkcja_nr_watku){					/*uruchamiana w wątkach*/
	
	int licznik, nr_watku, i;

	licznik = 0;
	nr_watku = *(int *)funkcja_nr_watku;
	
	printf("Wątek nr: %d o indentyfikatorze: %ld \n", nr_watku + 1, watki[nr_watku]);

	srand(time (NULL));
	
	sleep(1);
	for (i = 0; i<lb_sekcji; i++){
		
		kursor(0, 6 + lb_watkow + nr_watku);
		printf("Wątek nr: %d, sekcja prywatna: %d, liczba: %d\n", nr_watku + 1, i + 1, lb);
		
		sleep(rand()%4+1);
		
		mutexZamkniecie(&mutex);
		
		kursor(40, 6 + lb_watkow + nr_watku);
		printf("Wątek nr: %d, sekcja krytyczna: %d, liczba: %d\n", nr_watku + 1, i + 1, lb);
		
		licznik = lb;										/*inkrementacja liczby licznika*/
		licznik++;
		
		sleep(rand()%4+1);
		
		lb = licznik;
		
		mutexOtwarcie (&mutex);								/*koniec sekcji krytycznej*/
		
		kursor(0, 6 + lb_watkow + nr_watku);
		printf("Wątek nr: %d, sekcja prywatna: %d, lb: %d\n", nr_watku + 1, i + 1, lb);
		
		sleep(rand()%4+1);
	}
	return 0;
}





int main(int argc, char *argv[]){

	int i;
	
	if(argc != 3){
		printf("Błąd: niepoprawna liczba argumentów!\n");
		exit(EXIT_FAILURE);
	}
	
	lb_sekcji = atoi(argv[2]);
	lb_watkow = atoi(argv[1]);

	if(lb_watkow > max_lb_watkow){
		printf("Błąd: zbyt duża ilość wątków\n");
		exit(EXIT_FAILURE);
	}
	
	mutexInicjalizacja(&mutex);											/*w funkcji inicjacja na NULL(0)*/
	printf("Zainicjalizowano mutex o adresie %p\n\n", (void *)&mutex);
	
	lb = 0;
	
	for(i = 0; i < lb_watkow; i++){										/*tworzenie n wątków*/
		int  *pamiec = malloc(sizeof (int));
		*pamiec = i;
		sleep((double)i/lb_watkow);
		watki[i] = watekUtworzenie(watek_start, (void *)pamiec);		/*utworzenie wątku, jako argument jego nr*/
	}
	
	for(int i = 0; i < lb_watkow; i++){									/*czekanie na zakończenie wątków*/
		watekPolaczenie(watki[i]);
	}
	
	kursor(0, 4 + lb_watkow * 2);
	
	if(lb != lb_watkow * lb_sekcji) {									/*sprawdzenie czy liczba jest odpowiednia*/
		printf("\nSynchronizacja zakończona niepowodzeniem\nOczekiwano: %d      Otrzymano: %d\n", (lb_watkow * lb_sekcji), lb);
	} else{
		printf("\nSynchronizacja zakończona powodzeniem\nOczekiwano: %d      Otrzymano: %d\n", (lb_watkow * lb_sekcji), lb);
	}
	
	mutexUsun(&mutex);
	
	return 0;
}