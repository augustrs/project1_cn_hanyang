CC = g++
CFLAGS = -Wall -std=c++11 -pthread
TARGET = myserver
SRCS = server.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)

run: $(TARGET)
    ./$(TARGET) 8080