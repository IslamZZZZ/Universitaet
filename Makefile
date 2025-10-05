BUILD = build
SRC = src
CC = g++

all: $(BUILD)/rpn

$(BUILD)/rpn: $(BUILD)/main.o $(BUILD)/rpn.o | $(BUILD)
	$(CC) $(BUILD)/main.o $(BUILD)/rpn.o -o $(BUILD)/rpn

$(BUILD)/main.o: $(SRC)/main.cpp include/rpn.h | $(BUILD)
	$(CC) -c $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/rpn.o: $(SRC)/rpn.cpp include/rpn.h | $(BUILD)
	$(CC) -c $(SRC)/rpn.cpp -o $(BUILD)/rpn.o 

$(BUILD):
	mkdir -p $(BUILD)

run:
	./$(BUILD)/rpn

clean:
	rm -rf $(BUILD)