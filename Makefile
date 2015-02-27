
SRC = $(filter-out test.c, $(wildcard *.c))
SRC += $(wildcard deps/*/*.c)
CFLAGS += -std=c99 -Wall -Ideps
OBJS = $(SRC:.c=.o)

default: test; ./$<

valgrind: test
	valgrind --leak-check=full --error-exitcode=1 ./$<

test: test.o $(OBJS)
	$(CC) $< $(OBJS) -Ideps $(CFLAGS) -o $@

clean:
	rm -f test test.o
	rm -f $(OBJS)

.PHONY: clean default valgrind
