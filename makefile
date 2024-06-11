PROJ_NAME = web_server
CC = gcc
# Utilize flags com W para exibir erros mais detalhados
CFLAGS = -Wall -Wpedantic -O2 -g -pthread -fsanitize=address

C_SOURCE = client.c commandHandle.c logAddEntry.c logInitBuffer.c logPrintFile.c main.c server.c usrSig.c
H_SOURCE = client.h commandHandle.h log.h main.h server.h usrSig.h

# Arquivos objeto
OBJ = $(C_SOURCE:.c=.o)

# Regra padrão
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

client.o: client.c client.h log.h server.h
	$(CC) -c -o $@ $< $(CFLAGS)

commandHandle.o: commandHandle.c commandHandle.h
	$(CC) -c -o $@ $< $(CFLAGS)

logAddEntry.o: logAddEntry.c log.h
	$(CC) -c -o $@ $< $(CFLAGS)

logInitBuffer.o: logInitBuffer.c log.h
	$(CC) -c -o $@ $< $(CFLAGS)

logPrintFile.o: logPrintFile.c log.h
	$(CC) -c -o $@ $< $(CFLAGS)

main.o: main.c main.h commandHandle.h server.h
	$(CC) -c -o $@ $< $(CFLAGS)

server.o: server.c server.h log.h usrSig.h client.h
	$(CC) -c -o $@ $< $(CFLAGS)

usrSig.o: usrSig.c usrSig.h
	$(CC) -c -o $@ $< $(CFLAGS)

# Limpa tudo, EXCETO web_server.o
clean:
	rm -f $(filter-out web_server.o, $(OBJ))

# Limpa TODOS arquivos .o 
clean_all:
	rm -f *.o $(PROJ_NAME) *~

.PHONY: all clean clean_all
