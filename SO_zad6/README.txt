


Katalog SO_zad6 zawiera cztery programy w jezyku C oraz plik numer.txt:
-----------------------------------------------------------------------

semafory.c - otwieranie, zamykanie i inne potrzebne operacje semaforów

semafory.h - nagłówki do pliku semafory.c (osobna biblioteka)

inkrementator.c - odczytyje numer z plik.txt, dodaje 1, wpisuje nowy numer do pliku, a następnie wykonuje potrzebne procesy.
		Następnie sprawdza poprawność numeru i wypisuje komunikat o poprawności.


powielacz.c - tworzy podaną ilość kopii programu inkrementator który implementuje problem korzystania z zasobu współdzielonego. Powiela 		procesy by wzajemnie się wykluczały (exec + fork)
		1. tworzy semafor
		2. inicjuje semafor
		3. ~~~~~~procesy~~~~~~
		4. usuwa semafor (w funkcji przez atexit + przez sygnał)

		w odniesieniu do txt
		1. tworzy numer.txt
		2. wypisuje w nim 0

numer.txt - plik tworzony przez powielacz.c

------------------------------------------------------------------------

* Jak uruchomic programy:
=========================

Katalog zawiera program makefile do kompilacji, linkowania
i uruchamiania powyzszych programow, a takze czyszczenia katalogu 
i jego archiwizacji.

-> Aby uruchomic program, nalezy wykonac komendę:
	make all
	
	A następnie:
	make run6 (porównuje od razu pliki pipein.txt i pipeout.txt)

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

========================================================================