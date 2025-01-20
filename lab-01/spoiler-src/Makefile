CC = gcc
CFLAGS = -O1 
OBJ = crackme.o base64.o

# Target binary
TARGET = crackme

# Compilation rules
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

base64.o: base64.c base64.h
	$(CC) $(CFLAGS) -c base64.c

main.o: main.c base64.h
	$(CC) $(CFLAGS) -c main.c

# Clean up object files and the binary
clean:
	rm -f *.o $(TARGET)
