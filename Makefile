TARGET = bigsort
SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
	
RAND_FILE = "bin/random.txt"
	
CC = gcc
CFLAGS = -O3 -ansi -Wall -pedantic -std=c99
	
all: $(OBJS) $(TARGET)
	@echo Compilation complete

%.o: %.c
	@echo
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c $< -o $@	
	
$(TARGET): $(OBJS)
	@echo
	@echo Linking...
	$(CC) $(OBJS) -pg -o bin/$(TARGET) 
	
clean:
	@echo
	@echo Cleaning...
	rm -f bin/$(TARGET)
	rm src/*.o