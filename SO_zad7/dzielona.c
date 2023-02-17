/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 30.05.2022

program wykonujący zadanie 7
========================================================================
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int stworzenie_pamieci(const char *nazwa){
	int deskryptor;
	if((deskryptor = shm_open(nazwa, O_EXCL | O_RDWR | O_CREAT, 0644)) == -1){
		perror("Błąd tworzenia pamieci dzielonej");
		exit(EXIT_FAILURE);
	}else{
		return deskryptor;
	}
}

int otwieranie_pamieci(const char *nazwa){
	int deskryptor;
	if((deskryptor = shm_open(nazwa, O_RDWR, 0644)) == -1){
		perror("Błąd otwierania pamieci dzielonej");
		exit(EXIT_FAILURE);
	}else{
		return deskryptor;
	}
}

void zamknij_pamiec(int fd){
	if(close(fd) == -1){
		perror("Błąd zamykania pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
}

void usuwanie_pamieci(const char *nazwa){
	if(shm_unlink(nazwa) == -1){
		perror("Błąd usuwania pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
}

void *odwzorowanie_pamieci(int fd, size_t length){								/* w wirtualnej przestrzeni adresowej */
	void *adres = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(adres == MAP_FAILED){
		perror("Błąd odwzorowania pamieci dzielonej");
		exit(EXIT_FAILURE);
	}else{
		return adres;
	}
}

void usuwanie_odwzor_pamieci(void *adress, size_t length){
	if(munmap(adress, length) == -1){
		perror("Błąd usuwania odwzorowania pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
}
	
void rozmiar_pamieci(int fd, off_t length){										/*ustawianie długości pamięci dzielonej */
	if(ftruncate(fd, length) == -1){
		perror("Błąd inicjowania pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
}
