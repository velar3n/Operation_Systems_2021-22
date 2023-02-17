#ifndef SEMAFORY_H
#define SEMAFORY_H

sem_t *otworz_semafor(const char *nazwa);
void zamknij_semafor(sem_t *sem_t);
sem_t *stworz_semafor(const char *nazwa);
void wartosc_semafor(sem_t *sem, int *sval);
void podnies_semafor(sem_t *sem);
void opusc_semafor(sem_t *sem);
void usun_semafor(const char *nazwa);

#endif