
CC = /usr/bin/clang
CFLAGS = -I. -std=c99 -O3

TEST_PROG = test-arc4
TEST_PROG2 = test-arc4-2

.SUFFIXES: .c .o
.PHONY: all clean

all: $(TEST_PROG) $(TEST_PROG2)

$(TEST_PROG2): test-arc4-2.o arc4.o
	$(CC) $(CFLAGS) -o $(TEST_PROG2) test-arc4-2.o arc4.o

$(TEST_PROG): test-arc4.o arc4.o
	$(CC) $(CFLAGS) -o $(TEST_PROG) test-arc4.o arc4.o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TEST_PROG) $(TEST_PROG2) arc4.o \
		test-arc4.o test-arc4-2.o

