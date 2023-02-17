DIR = $(notdir $(CURDIR))

NAME1 = zad3a
NAME2 = zad3b
NAME3 = zad3c
NAME4 = zad3cc

EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x
EXEC3  = $(NAME3).x
EXEC4  = $(NAME4).x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o

LFLAGS = -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all run3a run3b run3c clean tar

all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^
	
$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^

run3a: $(EXEC1)
	./$(EXEC1) $(ARG1) $(ARG2)
	
run3b: $(EXEC2)
	./$(EXEC2) $(ARG1) $(ARG2)

run3c: $(EXEC3)
	./$(EXEC3) $(ARG1) $(ARG2)

run3cc: $(EXEC4)
	./$(EXEC4) $(ARG1) $(ARG2)

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
