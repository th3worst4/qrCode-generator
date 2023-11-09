CFLAGS = -m64
SHELL = pwsh

all: final

final: source/image.o source/main.o
	@echo "Linking and producing the final application"
	g++ -g $(CFLAGS) source/main.o source/image.o -o main.exe

image.o: source/image.cpp
	g++ $(CFLAGS) -o source/image.o -c source/image.cpp

main.o: source/main.cpp
	g++ $(CFLAGS) -o source/main.o -c source/main.cpp

clean:
	del source\main.o 
	del source\image.o 
	del main.exe
	make all