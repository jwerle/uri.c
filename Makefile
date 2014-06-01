
SRC = $(filter-out test.c, $(wildcard *.c))
SRC += $(wildcard deps/*/*.c)
CFLAGS += -std=c99 -Wall -Ideps
OBJS = $(SRC:.c=.o)

uri: clean test

$(OBJS):
	$(CC) $(CFLAGS) $(@:.o=.c) -c -o $(@)

test: $(OBJS)
	$(CC) test.c $(SRC) -Ideps $(CFLAGS) -o test
	./test

clean:
	rm -f test
	rm -f $(OBJS)
