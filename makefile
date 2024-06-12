PROJ_NAME = web_server

CC = gcc
# Utilizei flags com W para exibir erros mais detalhados 
CFLAGS = -Wall -Wpedantic -Wextra -O2 -g
# flags de linkagem 
LDFLAGS = -pthread 

RM = rm -f

all: $(PROJ_NAME)

$(PROJ_NAME): clientRequest.o extractCommandOptions.o LEntry.o LBufferInit.o LPrintFile.o main.o serverRun.o sigHandler.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
 
clientRequest.o: clientRequest.c clientRequest.h sigHandler.h log.h serverRun.h extractCommandOptions.h
	$(CC) -c $(CFLAGS) -o clientRequest.o clientRequest.c

extractCommandOptions.o: extractCommandOptions.c extractCommandOptions.h
	$(CC) -c $(CFLAGS) -o extractCommandOptions.o extractCommandOptions.c

LEntry.o: LEntry.c log.h
	$(CC) -c $(CFLAGS) -o LEntry.o LEntry.c

LBufferInit.o: LBufferInit.c log.h
	$(CC) -c $(CFLAGS) -o LBufferInit.o LBufferInit.c

LPrintFile.o: LPrintFile.c log.h
	$(CC) -c $(CFLAGS) -o LPrintFile.o LPrintFile.c

main.o: main.c extractCommandOptions.h serverRun.h log.h
	$(CC) -c $(CFLAGS) -o main.o main.c

serverRun.o: serverRun.c serverRun.h log.h extractCommandOptions.h clientRequest.h sigHandler.h
	$(CC) -c $(CFLAGS) -o serverRun.o serverRun.c

sigHandler.o: sigHandler.c sigHandler.h clientRequest.h log.h serverRun.h extractCommandOptions.h
	$(CC) -c $(CFLAGS) -o sigHandler.o sigHandler.c

# limpa tudo e mantem executavel web_server
clean:
	$(RM) $(filter-out web_server.o, *.o)

# Limpa tudo tudo
clean_all:
	$(RM) *.o *.d $(PROJ_NAME) *~

.PHONY: all clean clean_all


