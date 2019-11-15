CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main
CFLAGS := -g -O3 -std=c++11 -I include/ -I third_party/ -I src/

all: main

eventos:
	@mkdir build/eventos/
	$(CC) $(CFLAGS) -c src/services/eventos/boate.cpp -o build/eventos/boate.o
	$(CC) $(CFLAGS) -c src/services/eventos/show.cpp -o build/eventos/show.o
	$(CC) $(CFLAGS) -c src/services/eventos/teatro_fantoche.cpp -o build/eventos/teatro_fantoche.o
	$(CC) $(CFLAGS) -c src/services/eventos/cinema.cpp -o build/eventos/cinema.o

usuarios:
	@mkdir build/usuarios/
	$(CC) $(CFLAGS) -c src/services/usuarios/adulto.cpp -o build/usuarios/adulto.o
	$(CC) $(CFLAGS) -c src/services/usuarios/crianca.cpp -o build/usuarios/crianca.o
	$(CC) $(CFLAGS) -c src/services/usuarios/idoso.cpp -o build/usuarios/idoso.o

maquinas:
	@mkdir build/maquinas/
	$(CC) $(CFLAGS) -c src/services/maquinas/maquina_fantoche.cpp -o build/maquinas/maquina_fantoche.o

main: clean eventos usuarios maquinas
	$(CC) $(CFLAGS) build/eventos/*.o build/usuarios/*.o build/maquinas/*.o program/main.cpp -o main

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)