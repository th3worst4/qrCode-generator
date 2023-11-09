CFLAGS = -m64

all: final

final: source/image.o source/main.o
	@echo "Linking and producing the final application"
	g++ -g $(CFLAGS) source/main.o source/image.o -o main.exe

image.o: source/image.cpp
	g++ $(CFLAGS) -o source/image.o -c source/image.cpp

main.o: source/main.cpp
	g++ $(CFLAGS) -o source/main.o -c source/main.cpp

clean:
	rm source/main.o source/image.o main.exe
	final