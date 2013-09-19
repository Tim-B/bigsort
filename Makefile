TARGET = bigsort
SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
	
RAND_FILE = "bin/random.txt"
	
CC = mpicc
CFLAGS = -O3 -ansi -Wall -pedantic -std=c99
LFLAGS = -pg -fopenmp
	
all: $(OBJS) $(TARGET)
	@echo Compilation complete

%.o: %.c
	@echo
	@echo Compiling $<...
	$(CC) $(LFLAGS) $(CFLAGS) -c $< -o $@	
	
$(TARGET): $(OBJS)
	@echo
	@echo Linking...
	$(CC) $(OBJS) $(LFLAGS) -o bin/$(TARGET) 
	
clean:
	@echo
	@echo Cleaning...
	rm -f bin/$(TARGET)
	rm src/*.o