CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main
CFLAGS := -g -O3 -std=c++11 -I include/ -I third_party/

all: main

events:
	@mkdir build/events/
	$(CC) $(CFLAGS) -c src/services/events/boate.cpp -o build/events/boate.o
	$(CC) $(CFLAGS) -c src/services/events/show.cpp -o build/events/show.o
	$(CC) $(CFLAGS) -c src/services/events/teatro_fantoche.cpp -o build/events/teatro_fantoche.o
	$(CC) $(CFLAGS) -c src/services/events/cinema.cpp -o build/events/cinema.o

users:
	@mkdir build/users/
	$(CC) $(CFLAGS) -c src/services/users/adulto.cpp -o build/users/adulto.o
	$(CC) $(CFLAGS) -c src/services/users/crianca.cpp -o build/users/crianca.o
	$(CC) $(CFLAGS) -c src/services/users/idoso.cpp -o build/users/idoso.o

machines:
	@mkdir build/machines/
	$(CC) $(CFLAGS) -c src/services/machines/maquina_fantoche.cpp -o build/machines/maquina_fantoche.o

main: clean events users machines
	$(CC) $(CFLAGS) build/events/*.o build/users/*.o build/machines/*.o program/main.cpp -o main

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)