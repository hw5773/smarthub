COMPILER=gcc
OUT=aes_128_cbc aes_192_cbc aes_256_cbc bf_cbc
HEADER=crypto.h
COMMON_DIR=../common
COMMON=$(COMMON_DIR)/common.o
AES_128_CBC=openssl.o aes_128_cbc.o
AES_192_CBC=openssl.o aes_192_cbc.o
AES_256_CBC=openssl.o aes_256_cbc.o
BF_CBC=openssl.o bf_cbc.o
OBJS=$(AES_128_CBC) $(AES_192_CBC) $(AES_256_CBC) $(BF_CBC)
CFLAGS=-g -Wall -I/usr/local/include -L/usr/local/lib
LDFLAGS=-lssl -lcrypto -ldl

aes_128_cbc: $(AES_128_CBC) $(HEADER)
	$(COMPILER) -o $@ $(AES_128_CBC) $(COMMON) $(LDFLAGS)

aes_192_cbc: $(AES_192_CBC) $(HEADER)
	$(COMPILER) -o $@ $(AES_192_CBC) $(COMMON) $(LDFLAGS)

aes_256_cbc: $(AES_256_CBC) $(HEADER)
	$(COMPILER) -o $@ $(AES_256_CBC) $(COMMON) $(LDFLAGS)

bf_cbc: $(BF_CBC) $(HEADER)
	$(COMPILER) -o $@ $(BF_CBC) $(COMMON) $(LDFLAGS)

.c.o:
	$(COMPILER) $(CFLAGS) -c $<

openssl.o: openssl.c
aes_128_cbc.o: aes_128_cbc.c
aes_192_cbc.o: aes_192_cbc.c
aes_256_cbc.o: aes_256_cbc.c
common.o: common.c
bf_cbc.o: bf_cbc.c

clean:
	rm -rf $(OUT) $(OBJS)
