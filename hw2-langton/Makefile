CC = g++
FLAGS = -std=c++17
FILE = ant
OUT = game.out

all: dep
	$(CC) $(FLAGS) -o $(OUT) $(FILE).o

dep:
	$(CC) $(FLAGS) -c $(FILE).cpp

.PHONY: clean
clean:
	@-del $(OUT) *.o .depend
	@echo clean done
