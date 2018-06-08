CFLAGS = -O3
CC = g++
SRC = src/Main.cpp src/ControlEwe.cpp src/InterEwe.cpp
OBJ = $(SRC:.cpp = .o)
ControlEwe: $(OBJ)
	$(CC) $(CFLAGS) -o ControlEwe $(OBJ) -lrt -lpthread
clean:
	rm -f ControlEwe
	rm -f src/*.o src/*~ 
