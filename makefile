export PATH := C:/raylib/w64devkit/bin:$(PATH)

CC = gcc #compilador
EXE = main.exe
CFLAGS = -O1 -Wall -std=c99 -Wno-missing-braces -g #parâmetros de compilação
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm #bibliotecas que serão utilizadas

SRCS = $(wildcard *.c) #salva todos os arquivos de código fonte na pasta src
HDRS = $(wildcard *.h) #salva todos os cabeçalhos na pasta src

#atribui os valores das variáveis na linha de comando para compilar -> make
$(EXE):
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS) $(HDRS) $(LIBS)

#limpa a compilação -> make clean
clean:
	rm -f $(EXE) 

#executa a compilação -> make run
run:
	./$(EXE)

#define os comandos
.PHONY: clean run