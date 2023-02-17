/*
========================================================================
Autor: Natalia Kiełbasa                               Krakow, 05.06.2022

program wykonujący zadanie 8
========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "kolejki.h"

mqd_t kolejkaStworzenie(const char *nazwa, int oflag){
	struct mq_attr attr;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 30;
	mqd_t deskryptor = mq_open(nazwa, O_CREAT | O_EXCL | oflag, 0644, &attr);
	if(deskryptor == -1){
		perror("Błąd tworzenia kolejki");
		exit(EXIT_FAILURE);
	}
	return deskryptor;
}

mqd_t kolejkaOtwarcie(const char *nazwa, int oflag){
	mqd_t deskryptor = mq_open(nazwa, oflag);
	if(deskryptor == -1){
		perror("Błąd otwierania kolejki");
		exit(EXIT_FAILURE);
	}
	return deskryptor;
}

void kolejkaWysylanie(mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio){
	if(mq_send(mq_des, msg_ptr, 30, msg_prio) == -1){
		perror("Błąd wysyłania komunikatu");
		exit(EXIT_FAILURE);
	}
}

void kolejkaOdbieranie(mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio){
	if(mq_receive(mq_des, msg_ptr, 30, msg_prio) == -1){
		perror("Błąd odbierania komunikatu");
		exit(EXIT_FAILURE);
	}
}

void kolejkaZamykanie(mqd_t mq_des){
	if(mq_close(mq_des) == -1){
		perror("Błąd zamykania kolejki");
		exit(EXIT_FAILURE);
	}
}

void kolejkaUsuwanie(const char *nazwa){
	if(mq_unlink(nazwa) == -1){
		perror("Błąd usuwania kolejki");
		exit(EXIT_FAILURE);
	}
}