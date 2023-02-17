


Katalog SO_zad5 zawiera trzy programy w jezyku C oraz plik producent.txt:
--------------------------------------------------------------------
zad5.c -  Program pobierający porcje danych z pliku pipein.txt, wstawia
	go do potoku fifo, a następnie pobiera porcje danych z potoku i wstawia
	je do pliku pipeout.txt (tworzy plik jeśli on nie istnieje).
	Program na bieżąco drukuje na ekranie jakie porcje plików są 
	aktualnie przenoszone.

producent.c - pobiera dane z pliku pipein.txt i przekazuje je do potoku

konsument.c - pobiera dane z potoku i przekazuje je do pliku pipeout.txt

pipein.txt - plik tekstowy z przykładowym tekstem z którego pobierane do
	potoku są dane

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby uruchomic program, nalezy wykonac komendę:
	make all
	
	A następnie:
	make run5a (porównuje od razu pliki pipein.txt i pipeout.txt)

	make run5b (prorównuje od razu pliki i usuwa potok)s

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

========================================================================

sudo umount -l /mnt/c
sudo mount -t drvfs C: /mnt/c -o metadata

export DISPLAY=$(ip route|awk '/default/{print $3}'):0.0



