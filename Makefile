CFLAGS = -m64

all: final

final: source/image.o source/main.o
	@echo "Linking and producing the final application"
	g++ $(CFLAGS) source/main.o source/image.o -o main.exe

image.o: source/image.cpp
	g++ $(CFLAGS) -c source/image.c

main.o: source/main.cpp
	g++ $(CFLAGS) -c source/main.cpp

clean:
	rm source/main.o source/image.o main.exe
	final