CFLAGS = -O3
CC = g++
SRC = src/main.cpp src/ControlEwe.cpp src/InterEwe.cpp
OBJ = $(SRC:.cpp = .o)
ControlEwe: $(OBJ)
	$(CC) $(CFLAGS) -o ControlEwe $(OBJ) -lrt
clean:
	rm -f ControlEwe
	rm -f *.o *~ 
