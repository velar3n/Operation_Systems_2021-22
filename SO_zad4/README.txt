

Katalog SO_zad4 zawiera jeden programy w jezyku C oraz plik producent.txt:
--------------------------------------------------------------------
zad4.c -  Program pobierający porcje danych z pliku producent.txt, wstawia
	go do potok, a następnie pobiera porcje danych z potoku i wstawia
	je do pliku konsument.txt (tworzy plik jeśli on nie istnieje).
	Program na bieżąco drukuje na ekranie jakie porcje plików są 
	aktualnie przenoszone.

producent.txt - plik tekstowy z przykładowym tekstem z którego pobierane do
	potoku są dane

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program Makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby uruchomic program, nalezy wykonac komendę:
	make all
	
	A następnie:
	make run4 (porównuje od razu pliki producent.txt i konsument.txt)

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

========================================================================



