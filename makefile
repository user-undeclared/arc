.POSIX:

CFLAGS += -Wall -Wextra -pedantic -nostartfiles -nostdlib -nolibc -fno-stack-protector -std=c11 -ggdb3

a.out: start.o c_start.o std.o main.o
	$(LD) $^

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

start.o: start.asm
	fasm $^

.PHONY: clean
clean:
	$(RM) *.o
