#ifndef DZIELONA_H
#define DZIELONA_H

int stworzenie_pamieci(const char *nazwa);
int otwieranie_pamieci(const char *nazwa);
void zamknij_pamiec(int fd);
void usuwanie_pamieci(const char *nazwa);
void *odwzorowanie_pamieci(int fd, size_t length);
void usuwanie_odwzor_pamieci(void *adress, size_t length);
void rozmiar_pamieci(int fd, off_t length);

#endif