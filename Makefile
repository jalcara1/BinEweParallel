CFLAGS = -O3
CC = g++
SRC = src/Main.cpp src/ControlEwe.cpp src/InterEwe.cpp
OBJ = $(SRC:.cpp = .o)
ControlEwe: $(OBJ)
	$(CC) $(CFLAGS) -o BinEweInterpreter $(OBJ) -lrt -lpthread
clean:
	rm -f BinEweInterpreter
	rm -f src/*.o src/*~ 
