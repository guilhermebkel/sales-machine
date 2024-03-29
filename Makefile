CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main
CFLAGS := -g -O3 -std=c++11 -I include/ -I third_party/ -I src/

all: main

totem:
	@mkdir build/totem/
	$(CC) $(CFLAGS) -c src/totem/totem.cpp -o build/totem/totem.o

eventos:
	@mkdir build/eventos/
	$(CC) $(CFLAGS) -c src/eventos/boate.cpp -o build/eventos/boate.o
	$(CC) $(CFLAGS) -c src/eventos/show.cpp -o build/eventos/show.o
	$(CC) $(CFLAGS) -c src/eventos/teatro_fantoche.cpp -o build/eventos/teatro_fantoche.o
	$(CC) $(CFLAGS) -c src/eventos/cinema.cpp -o build/eventos/cinema.o

usuarios:
	@mkdir build/usuarios/
	$(CC) $(CFLAGS) -c src/usuarios/adulto.cpp -o build/usuarios/adulto.o
	$(CC) $(CFLAGS) -c src/usuarios/crianca.cpp -o build/usuarios/crianca.o
	$(CC) $(CFLAGS) -c src/usuarios/idoso.cpp -o build/usuarios/idoso.o

maquinas:
	@mkdir build/maquinas/
	$(CC) $(CFLAGS) -c src/maquinas/maquina_fantoche.cpp -o build/maquinas/maquina_fantoche.o
	$(CC) $(CFLAGS) -c src/maquinas/maquina_cinema.cpp -o build/maquinas/maquina_cinema.o
	$(CC) $(CFLAGS) -c src/maquinas/maquina_boate.cpp -o build/maquinas/maquina_boate.o
	$(CC) $(CFLAGS) -c src/maquinas/maquina_show.cpp -o build/maquinas/maquina_show.o

main: dir clean eventos usuarios maquinas totem
	$(CC) $(CFLAGS) build/eventos/*.o build/usuarios/*.o build/maquinas/*.o build/totem/*.o program/main.cpp -o main

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)

dir: 
	mkdir -p $(BUILDDIR)