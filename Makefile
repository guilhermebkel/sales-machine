CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main
CFLAGS := -g -O3 -std=c++11 -I include/

all: main

low:
	@mkdir build/low/
	$(CC) $(CFLAGS) -c src/services/low/boate.cpp -o build/low/boate.o
	$(CC) $(CFLAGS) -c src/services/low/idoso.cpp -o build/low/idoso.o
	$(CC) $(CFLAGS) -c src/services/low/show.cpp -o build/low/show.o
	$(CC) $(CFLAGS) -c src/services/low/teatro_fantoche.cpp -o build/low/teatro_fantoche.o

mid:
	@mkdir build/mid/
	$(CC) $(CFLAGS) -c src/services/mid/adulto.cpp -o build/mid/adulto.o
	$(CC) $(CFLAGS) -c src/services/mid/cinema.cpp -o build/mid/cinema.o
	$(CC) $(CFLAGS) -c src/services/mid/crianca.cpp -o build/mid/crianca.o

main: clean mid low
	$(CC) $(CFLAGS) build/mid/*.o build/low/*.o src/main.cpp -o main

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)