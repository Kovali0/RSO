CFLAGS=-ggdb -Wall -pedantic -D_REENTRANT

%: %.c
	gcc $(CFLAGS) $< -o $@ -lpthread

EXECS = server netclient

all: $(EXECS)

netclient: netclient.cpp

server1: server.cpp

.PHONY: clean all

clean:
	rm -f $(EXECS)
