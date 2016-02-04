#makefile

#Aliases used in build process
BUILD_DIR = build
EXECUTABLES = server

#Flags
CC = g++
CFLAGS = -Wall -g -pedantic

#Executables created
all: $(BUILD_DIR) $(EXECUTABLES)

server: $(BUILD_DIR)/main.o $(BUILD_DIR)/server_farm.o
	$(CC) $(CFLAGS) -o  server $(BUILD_DIR)/main.o $(BUILD_DIR)/server_farm.o

#Builds the main object files for this project
$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ -I. $<

.PHONY: clean

#create main build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

#Removes all object files and executables
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLES) random_output.txt *~

