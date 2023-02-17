/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 30.05.2022

program wykonujący zadanie 7
========================================================================
*/

/*

WZAJEMNE WYKLUZCANIE - gdy jeden proces zmienia dane w sekcji krytycznej - żaden inny proces nie może tego robić
	sekcja wejściowa - krytyczna - wyjściowa

	1. Tylko jeden proces może nyć w sekcji krytycznej w jednym momencie
	2. Po zakończeniu - jeśli istnieje kolejny proces do wykonania zmian w sekcji krytycznej - wybranie go i uruchomienie
		sleep by procesy udawały że czekają
	3. Ustalić max czas czekania procesów czekających y nie trwało to w nieskończoność przez priorytyzację innych proesów

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/types.h>

sem_t *otworz_semafor(const char *nazwa){
	sem_t *adres;
	if((adres = sem_open(nazwa, 0)) == SEM_FAILED){
		perror("Błąd otwierania semafora");
		exit(EXIT_FAILURE);
	} else{
		return adres;
	}
}

void zamknij_semafor(sem_t *sem_t){
	if(sem_close(sem_t) == -1){
		perror("Błąd zamknięcia semafora");
		exit(EXIT_FAILURE);
	}
}

sem_t *stworz_semafor(const char *nazwa, int value){
	sem_t *adres;
	if ((adres = sem_open(nazwa, O_CREAT | O_EXCL, 0644, value)) == SEM_FAILED){
		perror("Błąd tworzenia semafora");
		exit(EXIT_FAILURE);
	} else{
		return adres;
	}
}

int wartosc_semafor(sem_t *sem){
	int sval;
	if(sem_getvalue(sem, &sval) == -1){
		perror("Błąd odczytywania wartości semafora");
		exit(EXIT_FAILURE);
	}
	else{
		return sval;
	}
}

void podnies_semafor(sem_t *sem){
	if(sem_post(sem) == -1){
		perror("Błąd podnoszenia semafora");
		exit(EXIT_FAILURE);
	}
}

void opusc_semafor(sem_t *sem){
	if(sem_wait(sem) == -1){
		perror("Błąd opuszczania semafora");
		exit(EXIT_FAILURE);
	}
}

void usun_semafor(const char *nazwa){
	if(sem_unlink(nazwa) == -1){
		perror("Błąd usuwania semafora");
		exit(EXIT_FAILURE);
	}
}