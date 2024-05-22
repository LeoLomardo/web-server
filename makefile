# Defini��es de compilador e flags
CC = gcc
CFLAGS = -Wall -pthread -pedantic

# Arquivos de cabe�alho
DEPS = client.h commandHandle.h globals.h log.h main.h server.h statisticsFile.h

# Arquivos objeto
OBJ = client.o commandHandle.o logAddEntry.o logFree.o logInitBuffer.o logPrintFile.o main.o server.o statisticsFile.o

# Regra padr�o
all: web_server

# Regras para compilar arquivos objeto
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Regra para compilar o execut�vel
web_server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Regra para limpar arquivos compilados
.PHONY: clean
clean:
	rm -f *.o web_server
