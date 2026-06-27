CC = gcc
CFLAGS = -Wall -Wextra -g -I./src
SRC = src/main.c src/hash.c src/script.c 
TARGET = exec


ifeq ($(OS),Windows_NT)
	# Configurações exclusivas para Windows
	TARGET_NAME = $(TARGET).exe
	CLEAN_CMD = del /Q /F $(TARGET_NAME)
	RUN_CMD = .\$(TARGET_NAME)
else
	# Configurações exclusivas para Linux (Mint, Ubuntu, etc)
	TARGET_NAME = $(TARGET)
	CLEAN_CMD = rm -f $(TARGET_NAME)
	RUN_CMD = ./$(TARGET_NAME)
endif

all: $(TARGET_NAME)

$(TARGET_NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET_NAME) $(SRC)				

run: $(TARGET_NAME)
	$(RUN_CMD)				

clean:
	$(CLEAN_CMD)		