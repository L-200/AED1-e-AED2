TARGET = main_arvores
INCLUDE_DIR = include
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -I$(INCLUDE_DIR)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: clean
