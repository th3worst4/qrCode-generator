CFLAGS = -m64
SHELL = pwsh

all: final debug

final: source/image.o source/main.o
	g++ $(CFLAGS) source/main.o source/image.o -o main.exe
	@echo final application built successfully

image.o: source/image.cpp
	g++ $(CFLAGS) -o source/image.o -c source/image.cpp

main.o: source/main.cpp
	g++ $(CFLAGS) -o source/main.o -c source/main.cpp

debug: debug/main-debug.o debug/image-debug.o
	g++ $(CFLAGS) -g debug/main-debug.o debug/image-debug.o -o debug/main-debug.exe
	@echo debug application built successfully
	@echo you can run gdb on "main-debug.exe"

debug/image-debug.o: source/image.cpp
	g++ $(CFLAGS) -g -o debug/image-debug.o -c source/image.cpp

debug/main-debug.o: source/main.cpp
	g++ $(CFLAGS) -g -o debug/main-debug.o -c source/main.cpp

clean-all: clean clean-debug

clean:
	del source\main.o 
	del source\image.o 
	del main.exe
	del out.png

clean-debug:
	del debug\main-debug.o
	del debug\image-debug.o
	del debug\main-debug.exe
	del debug\out.png