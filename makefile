PROJ_NAME = web_server
CC = gcc
# Utilize flags com W para exibir erros mais detalhados
CFLAGS = -Wall -Wpedantic -Wextra -O2 -g 
# flags de linkagem 
LDFLAGS = -pthread 
C_SOURCE = clientRequest.c extractCommandOptions.c logAddEntry.c logInitBuffer.c logPrintFile.c main.c serverRun.c sigHandler.c

# Arquivos objeto
OBJ = $(C_SOURCE:.c=.o)
# Arquivos de dependência
DEPS := $(OBJ:.o=.d)

# Regra padrão
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Limpa tudo, EXCETO web_server.o
clean:
	rm -f $(filter-out web_server.o, $(OBJ))

# Limpa TODOS arquivos .o 
clean_all:
	rm -f *.o *.d $(PROJ_NAME) *~

#explica aqui
%.d: %.c
	@$(CC) $< -MM -MT $(@:%.d=%.o) >$@

-include $(DEPS)

.PHONY: all clean clean_all
