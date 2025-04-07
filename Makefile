CC=gcc
CFLAGS=-I.

all: server
server: *.c 
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f server
