CC = g++
FLAGS = -pthread -std=c++17

EXEC = createdir ssooiigle  
DIR = exec results

all: compile run



compile: $(EXEC)

createdir: 
	mkdir $(DIR)
ssooiigle: 
	$(CC) src/main.cpp -o exec/main $(FLAGS)

run:
	exec/main

clean:
	rm -r $(DIR)