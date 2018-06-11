CC = g++
CFLAGS = -c -Wall -o3
LDFLAGS = -lrt -pthread
CONTROL_SOURCES = src/BinEweControl.cpp src/ControlEwe.cpp
INTERPRETER_SOURCES = src/BinEweInterpreter.cpp src/InterEwe.cpp
CONTROL_OBJECTS = $(CONTROL_SOURCES:.cpp=.o)
INTERPRETER_OBJECTS = $(INTERPRETER_SOURCES:.cpp=.o)
CONTROL_EXECUTABLE = BinEweControl
INTERPRETER_EXECUTABLE = BinEweInterpreter

.PHONY: all control interpreter

all: control interpreter

control: $(CONTROL_EXECUTABLE)

interpreter: $(INTERPRETER_EXECUTABLE)

$(CONTROL_EXECUTABLE): $(CONTROL_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(INTERPRETER_EXECUTABLE): $(INTERPRETER_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f BinEweControl BinEweInterpreter
	rm -f src/*.o src/*~
