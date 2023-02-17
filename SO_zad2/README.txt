

Katalog SO_zad2 zawiera dwa programy w jezyku C:
--------------------------------------------------------------------
zad2.c -  Program wypisujący identyfikatory UID, GID, PID, PPID i PGID dla danego procesu dla danego
	procesu macierzystego i potomnych, komunikaty procesów potomnych wypisywane są przez
	program zad22.c, uruchamiany przez funkcję execlp

zad22.c - Program wypisujący identyfikatory UID, GID, PID, PPID i PGID dla danych procesów potomnych

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================


Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby uruchomic program, nalezy wykonac komendę:
       make all
	
	A następnie:
	make run2

	Można też po "make run" przekazać argumenty manualnie przez:
	./zad2.x ./zad22.x zad22


-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

========================================================================



