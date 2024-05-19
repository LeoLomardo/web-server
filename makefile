CC = gcc
CFLAGS = -Wall -pthread
DEPS = main.h server.h sigHandler.h parse.h log.h
OBJ = main.o server.o sigHandler.o parse.o addLog.o freeLog.o initLogBuffer.o writeLog.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

web_server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o web_server
