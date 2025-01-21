CC = gcc
CFLAGS = -O1
OBJ = crackme.o base64.o $(LEVELS)
LEVELS = $(patsubst %.c, %.o, $(wildcard level*.c)) # Automatically find all levelN.c files

# Target binary
TARGET = crackme

# Main target
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Pattern rule to compile levelN.c files
level%.o: level%.c
	$(CC) $(CFLAGS) -c $< -o $@

base64.o: base64.c base64.h
	$(CC) $(CFLAGS) -c $< -o $@

crackme.o: crackme.c base64.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the binary
clean:
	rm -f *.o $(TARGET)
