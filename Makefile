TARGET = bigsort
SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
	
RAND_FILE = "bin/random.txt"
	
CC = gcc
CFLAGS = -ansi -Wall -pedantic
	
all: $(OBJS) $(TARGET)
	@echo Compilation complete

%.o: %.c
	@echo
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c $< -o $@	
	
$(TARGET): $(OBJS)
	@echo
	@echo Linking...
	$(CC) $(OBJS) -o bin/$(TARGET) 
	
clean:
	@echo
	@echo Cleaning...
	rm  bin/*