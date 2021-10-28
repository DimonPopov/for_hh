CC = g++
CCFLAG = -Wall -std=c++17
DIR = ./Source/
OBJ_1 = main_1.o
OBJ_2 = main_2.o

.PHONY: all clean


all: lab5_1 lab5_2

lab5_1: $(OBJ_1)
	$(CC) $(CCFLAG) $< -o $@

main_1.o: $(DIR)main_1.cpp
	$(CC) $(CCFLAG) -c $<


lab5_2: $(OBJ_2)
	$(CC) $(CCFLAG) $< -o $@

main_2.o: $(DIR)main_2.cpp
	$(CC) $(CCFLAG) -c $<




clean:
	rm *.o lab5_1 lab5_2