CC = gcc
CFLAGS = -Wall -pthread -pedantic 
DEPS = main.h server.h client.h commandHandle.h log.h 
OBJ = main.o server.o client.o commandHandle.o logAddEntry.o logFree.o logInitBuffer.o logPrintFile.o  

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

web_server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o web_server
