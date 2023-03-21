
CC = /usr/bin/clang
CFLAGS = -I. -std=c99 -O3

OBJS = test-arc4.o arc4.o
TEST_PROG = test-arc4

.SUFFIXES: .c .o
.PHONY: all clean

all: $(TEST_PROG)

$(TEST_PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(TEST_PROG) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TEST_PROG) $(OBJS)

