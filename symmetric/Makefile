COMPILER=gcc
OUT=aes_128_cbc
HEADER=crypto.h
COMMON_DIR=../common
COMMON=$(COMMON_DIR)/common.o
AES_128_CBC=openssl.o aes_128_cbc.o
OBJS=$(AES_128_CBC)
CFLAGS=-g -Wall -I/usr/local/include -L/usr/local/lib
LDFLAGS=-lssl -lcrypto -ldl

aes_128_cbc: $(AES_128_CBC) $(HEADER)
	$(COMPILER) -o $@ $(AES_128_CBC) $(COMMON) $(LDFLAGS)

.c.o:
	$(COMPILER) $(CFLAGS) -c $<

openssl.o: openssl.c
aes_128_cbc.o: aes_128_cbc.c
common.o: common.c

clean:
	rm -rf $(OUT) $(OBJS)
