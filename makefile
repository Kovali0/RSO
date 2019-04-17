CFLAGS=-ggdb -Wall -pedantic -D_REENTRANT

%: %.c
	gcc $(CFLAGS) $< -o $@ -lpthread -lm

EXECS = server netclient Message

all: $(EXECS)

netclient: netclient.cpp

server1: server.cpp

Message: Message.hpp

.PHONY: clean all

clean:
	rm -f $(EXECS)
