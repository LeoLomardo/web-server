PROJ_NAME = web_server
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -O2 -g -pthread -fsanitize=address -fsanitize=undefined


C_SOURCE = client.c commandHandle.c logAddEntry.c logFree.c logInitBuffer.c logPrintFile.c main.c server.c saveStats.c
H_SOURCE = client.h commandHandle.h log.h main.h server.h statsInfo.h

# Arquivos objeto
OBJ = $(C_SOURCE:.c=.o)

# Regra padrão
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

# Limpa tudo, EXCETO web_server.o
clean:
	rm -f $(filter-out web_server.o, $(OBJ))

# Limpa TODOS arquivos .o 
clean_all:
	rm -f *.o $(PROJ_NAME) *~

.PHONY: all clean clean_all
