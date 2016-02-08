#makefile

#Aliases used in build process
BUILD_DIR = build
EXECUTABLES = painting

#Flags
CC = g++
CFLAGS = -Wall -g -pedantic -std=c++11

#Executables created
all: $(BUILD_DIR) $(EXECUTABLES)

painting: $(BUILD_DIR)/main.o $(BUILD_DIR)/painting.o
	$(CC) $(CFLAGS) -o  painting $(BUILD_DIR)/main.o $(BUILD_DIR)/painting.o

#Builds the main object files for this project
$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ -I. $<

.PHONY: clean

#create main build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

#Removes all object files and executables
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLES) painting *~ *.swp

