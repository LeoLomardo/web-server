CC = gcc
CFLAGS = -Wall -pthread
DEPS = main.h server.h sigHandler.h log.h parse.c calcStatistics.c
OBJ = main.o server.o sigHandler.o log.o parse.o calcStatistics.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

web_server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o web_server