
SRC = $(filter-out test.c, $(wildcard *.c))
SRC += $(wildcard deps/*/*.c)
CFLAGS += -std=c99 -Wall -Ideps
OBJS = $(SRC:.c=.o)

default: test
	./$<

valgrind: test
	valgrind --leak-check=full --error-exitcode=1 ./$<

test: $(OBJS)
	$(CC) test.c $(SRC) -Ideps $(CFLAGS) -o test

clean:
	rm -f test
	rm -f $(OBJS)

.PHONY: clean default valgrind
