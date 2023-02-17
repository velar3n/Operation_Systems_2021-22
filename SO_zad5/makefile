DIR = $(notdir $(CURDIR))

NAME1 = zad5
NAME2 = producent
NAME3 = konsument

ARG1 = pipein.txt
ARG2 = pipeout.txt
ARG3 = FIFO
ARG4 = ./producent.x
ARG5 = ./konsument.x

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

LFLAGS = -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all run5a run5b diff2 clean tar

all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1) $(LIBS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(LIBS2)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3) $(LIBS3)
	$(LD) -o $@ $(LFLAGS) $^

run5a: $(EXEC1)  
	./$(EXEC1) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5); diff -s $(ARG1) $(ARG2)

run5b: $(EXEC2) $(EXEC3)  
	mkfifo $(ARG3) 
	xterm -hold -title PRODUCENT -e ./$(EXEC2) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5) &
	xterm -hold -title KONSUMENT -e ./$(EXEC3) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5)
	diff -s $(ARG1) $(ARG2) 
	rm -f $(ARG3) 

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR))
