
SRC = $(wildcard *.c)
SRC += $(wildcard deps/*/*.c)
CFLAGS += -std=c99 -Wall -Ideps
OBJS = $(SRC:.c=.o)

default: test; ./$<

valgrind: test
	valgrind --leak-check=full --error-exitcode=1 ./$<

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f test $(OBJS)

.PHONY: clean default valgrind
