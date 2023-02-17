DIR = `basename $(CURDIR)`

NAME1 = zad7
NAME2 = producent
NAME3 = konsument
NAME4 = semafory
NAME5 = dzielona
LIB1 = semafory
LIB2 = dzielona
PLIK_WE = surowce.txt
PLIK_WY = skonsumowane.txt

EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x
EXEC3  = $(NAME3).x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o
OBJS5  = $(NAME5).o

LIBS1  = $(LIB1).c
LIBS2  = $(LIB2).c

LIB_OBJS = $(OBJS4) $(OBJS5)
HEADS4 = $(NAME4).h
HEADS5 = $(NAME5).h

CFLAGS = -Wall -std=gnu99 -pedantic -O -pthread
LDLIBS = -lrt

CO = gcc
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1) $(LIBS1) $(LIBS2)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

$(EXEC2): $(OBJS2) $(LIBS1) $(LIBS2)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

$(EXEC3): $(OBJS3) $(LIBS1) $(LIBS2)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

.PHONY: run7

run7: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) $(EXEC2) $(EXEC3)
	@diff -s $(PLIK_WE) $(PLIK_WY)

.PHONY: clean tar

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
