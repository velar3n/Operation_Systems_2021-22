

Katalog SO_zad3 zawiera cztery programy w jezyku C:
--------------------------------------------------------------------
zad3a.c -  Program do obsługi sygnałów z możliwościami: (1) wykonania operacji domyslnej, 
	(2) ignorowania oraz (3) przechwycenia i własnej obsługi sygnału.

zad3b.c - Program jak zad3a.c, tylko że uruchamiany jest przez funkcję exec w procesie potomnym.

zad3c.c - Jak zad3a.c, ale  procesie macierzystym tworzy się proces potomny, który staje
	się liderem nowej grupy procesów.

zad3cc.c - Program do procesów potomnych z zad3c.c

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================


Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby uruchomic program, nalezy wykonac komendę:
	make all
	
	A następnie:
	make run3a ARG1="opcja_sygnału" ARG2="numer_sygnału"
		(lub zamiast run3a analogicznie run3b lub run3c

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

========================================================================



