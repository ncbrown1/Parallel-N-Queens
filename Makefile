# Makefile for Parallel-N-Queens
CC = icc
CFLAGS = -Wall -O2 -std=c++11

AR = ar
ARFLAGS = cr
RANLIB = ranlib

LIB = -lm
TARGET = nqueens

SRC = *.cpp #$(addsuffix .cpp, $(TARGET))

all: $(TARGET)

$(TARGET): $(SRC) Makefile
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LIB)

clean:
	rm -f *.o *~ $(TARGET) core*
