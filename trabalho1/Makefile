# Nome do executável
PROG = programa

# Compilador e flags
CC = gcc
CFLAGS = -Wall -O2

# Arquivos fonte e objetos
SRCS = main.c grafo.c fila.c
OBJS = $(SRCS:.c=.o)

# Regra padrão: compilar tudo
all: $(PROG)

# Como gerar o executável
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

# Como compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f *.o $(PROG)
