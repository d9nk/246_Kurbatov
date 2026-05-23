CC = gcc
CFLAGS = -Wall -fPIC

all: program libinterpos.so

# Static library: fred + john
libfoo.a: fred.o john.o
	ar crv libfoo.a fred.o john.o

fred.o: fred.c
	$(CC) $(CFLAGS) -c fred.c

john.o: john.c
	$(CC) $(CFLAGS) -c john.c

# Shared library: bill + sam
libbar.so: bill.c sam.c
	$(CC) $(CFLAGS) -shared -o libbar.so bill.c sam.c -lm

# Link-time interposition object
interpos_link.o: interpos_link.c
	$(CC) $(CFLAGS) -c interpos_link.c

# Load-time interposition shared library
libinterpos.so: interpos_load.c
	$(CC) $(CFLAGS) -shared -o libinterpos.so interpos_load.c -ldl

# Build the program
program: program.c libfoo.a libbar.so interpos_link.o
	$(CC) $(CFLAGS) -o program program.c interpos_link.o \
		-Wl,--wrap=fred -Wl,--wrap=john \
		-L. -lfoo -lbar -lm

run: program libinterpos.so
	LD_LIBRARY_PATH=. LD_PRELOAD=./libinterpos.so ./program

clean:
	rm -f *.o *.a *.so program

.PHONY: all run clean
