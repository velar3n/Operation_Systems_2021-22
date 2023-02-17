#ifndef KOLEJKI_H
#define KOLEJKI_H

#define KOLEJKA_NAZWA "/kolejka_komunikatow"
#define MAX_WIADOMOSCI 10
#define DLUGOSC_KOMUNIKATU 30


mqd_t kolejkaStworzenie(const char *nazwa, int oflag);
mqd_t kolejkaOtwarcie(const char *nazwa, int oflag);
void kolejkaWysylanie(mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio);
void kolejkaOdbieranie(mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio);
void kolejkaZamykanie(mqd_t mq_des);
void kolejkaUsuwanie(const char *nazwa);

#endif