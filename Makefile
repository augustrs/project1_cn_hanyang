CC = gcc                   # Compiler
CFLAGS = -Wall -Wextra     # Compiler flags (show warnings)
TARGET = myserver          # Output executable name
SRC = server.c             # Source file(s)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
