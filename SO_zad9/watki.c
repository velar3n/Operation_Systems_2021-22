/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 06.06.2022

program wykonujący zadanie 9
========================================================================
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

pthread_t watekUtworzenie(void *funkcja(void *), void *argument){
	pthread_t ID;
	int stan;

	stan = pthread_create(&ID, NULL, funkcja, argument);
	if(stan == EAGAIN){
		printf("Bład: Przekroczony został limit systemowy liczby wątków lub procesów LWP\n");
		exit(EXIT_FAILURE);
	}else if(stan == EINVAL){
		printf("Błąd: Nieprawidłowa wartość argumentu attr");
		exit(EXIT_FAILURE);
	}else if(stan == ENOMEM){
		printf("Błąd: Brak pamięci do utworzenia nowego wątku\n");
		exit(EXIT_FAILURE);
	}else if(stan != 0){
		printf("Błąd przy tworzeniu wątku\n");
		exit(EXIT_FAILURE);
	}
	return ID;
}

void watekPolaczenie(pthread_t watek){
	if(pthread_join(watek, NULL) != 0){
		printf("Błąd łączenia wątku\n");
		exit(EXIT_FAILURE);	
	}
}

void mutexInicjalizacja(pthread_mutex_t *mutex){			/*mutex - mutual exclusion, semafor 0-1*/
	if(pthread_mutex_init(mutex, NULL) != 0){
		printf("Błąd przy inicjalizacji mutexu\n");
		exit(EXIT_FAILURE);
	}
}

void mutexZamkniecie(pthread_mutex_t *mutex){
	if (pthread_mutex_lock(mutex) != 0){
		printf("Błąd zamykania mutexu\n");
		exit(EXIT_FAILURE);	
	}
}

void mutexOtwarcie(pthread_mutex_t *mutex){
	if (pthread_mutex_unlock(mutex) != 0){
		printf("Błąd otwierania mutexu\n");
		exit(EXIT_FAILURE);
	}
}

void mutexUsun(pthread_mutex_t *mutex){
	if (pthread_mutex_destroy (mutex) != 0){
		printf("Błąd usuwania mutexu\n");
		exit (EXIT_FAILURE);
	}
}