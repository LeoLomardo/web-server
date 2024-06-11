PROJ_NAME = web_server
CC = gcc
# Utilizei flags com W para exibir erros mais detalhados
CFLAGS = -Wall -Wpedantic -Wextra -O2 -g 
# flags de linkagem 
LDFLAGS = -pthread 

all: $(PROJ_NAME)

$(PROJ_NAME): clientRequest.o extractCommandOptions.o LEntry.o LBufferInit.o LPrinfFile.o main.o serverRun.o sigHandler.o
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

clientRequest.o: clientRequest.c clientRequest.h sigHandler.h log.h
	$(CC) -c -o clientRequest.o clientRequest.c $(CFLAGS)

extractCommandOptions.o: extractCommandOptions.c extractCommandOptions.h
	$(CC) -c -o extractCommandOptions.o extractCommandOptions.c $(CFLAGS)

LEntry.o: LEntry.c log.h
	$(CC) -c -o LEntry.o LEntry.c $(CFLAGS)

LBufferInit.o: LBufferInit.c log.h
	$(CC) -c -o LBufferInit.o LBufferInit.c $(CFLAGS)

LPrinfFile.o: LPrinfFile.c log.h
	$(CC) -c -o LPrinfFile.o LPrinfFile.c $(CFLAGS)

main.o: main.c extractCommandOptions.h serverRun.h log.h
	$(CC) -c -o main.o main.c $(CFLAGS)

serverRun.o: serverRun.c serverRun.h log.h extractCommandOptions.h
	$(CC) -c -o serverRun.o serverRun.c $(CFLAGS)

sigHandler.o: sigHandler.c sigHandler.h clientRequest.h log.h serverRun.h
	$(CC) -c -o sigHandler.o sigHandler.c $(CFLAGS)

# limpa tudo e mantem executavel web_server
clean:
	rm -f $(filter-out web_server.o, *.o)

# Limpa tudo tudo
clean_all:
	rm -f *.o *.d $(PROJ_NAME) *~

.PHONY: all clean clean_all
