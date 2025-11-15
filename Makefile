# Makefile para POKEWAR

# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c99

# Nombre del ejecutable
TARGET = pokewar

# Archivos objeto
OBJS = main.o pokemon.o ui.o combate.o

# Regla principal
all: $(TARGET)

# Enlazar todos los objetos
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilar main.c
main.o: main.c pokemon.h ui.h combate.h
	$(CC) $(CFLAGS) -c main.c

# Compilar pokemon.c
pokemon.o: pokemon.c pokemon.h
	$(CC) $(CFLAGS) -c pokemon.c

# Compilar ui.c
ui.o: ui.c ui.h pokemon.h
	$(CC) $(CFLAGS) -c ui.c

# Compilar combate.c
combate.o: combate.c combate.h pokemon.h ui.h
	$(CC) $(CFLAGS) -c combate.c

# Limpiar archivos compilados
clean:
	del /Q *.o $(TARGET).exe 2>nul || echo Limpieza completada

# Compilar y ejecutar
run: all
	.\$(TARGET).exe

.PHONY: all clean run
