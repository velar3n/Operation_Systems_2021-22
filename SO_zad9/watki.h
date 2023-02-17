#ifndef WATKI_H
#define WATKI_H

#include <pthread.h>

pthread_t watekUtworzenie(void *funkcja(void *), void *argument);
void watekPolaczenie(pthread_t watek);
void mutexInicjalizacja(pthread_mutex_t *mutex);
void mutexZamkniecie(pthread_mutex_t *mutex);
void mutexOtwarcie(pthread_mutex_t *mutex);
void mutexUsun(pthread_mutex_t *mutex);

#endif