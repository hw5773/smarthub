COMPILER=gcc
OBJ=aes_128_cbc
SRC=aes_128_cbc.c
CFLAGS=-g -Wall -I/usr/local/include -L/usr/local/lib
LDFLAGS=-lssl -lcrypto -ldl

all:
	$(COMPILER) -o $(OBJ) $(SRC) $(CFLAGS) $(LDFLAGS)
