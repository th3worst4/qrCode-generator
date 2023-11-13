CC = g++
CFLAGS = -m64

CFILES = image.cpp main.cpp
OBJECTS = image.o main.o
DOBJECTS = main-debug.o image-debug.o

SHELL := pwsh.exe
.SHELLFLAGS := -Command

all: final debug

final: $(OBJECTS)
	$(CC) $(CFLAGS) $(addprefix bin/, $(OBJECTS)) -o bin/main.exe
	@echo final application built successfully

$(OBJECTS): %.o: source/%.cpp
	$(CC) $(CFLAGS) -o bin/$@ -c $^

debug: $(DOBJECTS)
	$(CC) $(CFLAGS) -g $(addprefix debug/, $(DOBJECTS)) -o debug/main-debug.exe
	@echo debug application built successfully
	@echo you can run gdb on "main-debug.exe"

$(DOBJECTS): %-debug.o: source/%.cpp
	$(CC) $(CFLAGS) -g -o debug/$@ -c $^

clean-all: clean clean-debug

clean:
	del bin\main.o 
	del bin\image.o 
	del bin\main.exe
	del bin\out.png

clean-debug:
	del debug\main-debug.o
	del debug\image-debug.o
	del debug\main-debug.exe
	del debug\out.png