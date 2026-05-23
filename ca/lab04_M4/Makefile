CC = gcc
CFLAGS = -Wall

all: regex_replace

regex_replace: regex_replace.c
	$(CC) $(CFLAGS) -o regex_replace regex_replace.c

clean:
	rm -f regex_replace

.PHONY: all clean
