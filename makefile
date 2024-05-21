CC = gcc
CFLAGS = -Wall -pthread -pedantic 

# Cabeçalhos
DEPS_MAIN = main.h server.h client.h commandHandle.h globais.h
DEPS_LOG = log.h 

# Objetos
OBJ_MAIN = main.o server.o client.o commandHandle.o
OBJ_LOG = logAddEntry.o logFree.o logInitBuffer.o logPrintFile.o  

all: web_server clean_objs

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

main.o: main.c $(DEPS_MAIN)
	$(CC) -c -o $@ $< $(CFLAGS)

server.o: server.c server.h
	$(CC) -c -o $@ $< $(CFLAGS)

client.o: client.c client.h
	$(CC) -c -o $@ $< $(CFLAGS)

commandHandle.o: commandHandle.c commandHandle.h
	$(CC) -c -o $@ $< $(CFLAGS)

logAddEntry.o: logAddEntry.c log.h
	$(CC) -c -o $@ $< $(CFLAGS)

logFree.o: logFree.c log.h
	$(CC) -c -o $@ $< $(CFLAGS)

logInitBuffer.o: logInitBuffer.c log.h
	$(CC) -c -o $@ $< $(CFLAGS)

logPrintFile.o: logPrintFile.c log.h
	$(CC) -c -o $@ $< $(CFLAGS)

web_server: $(OBJ_MAIN) $(OBJ_LOG)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean clean_objs

clean: clean_objs
	rm -f web_server

clean_objs:
	rm -f *.o