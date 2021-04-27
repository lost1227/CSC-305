CC = clangcc
CXX = clang++

MAINS=list1

all: $(MAINS)

list1: List1.o ListMain1.o
	$(CC) List1.o ListMain1.o -o list1

List1.o: List1.cpp List1.h
	$(CC) List1.cpp -c

ListMain1.o: List1Main.cpp List1.h
	$(CC) List1Main.cpp -c
