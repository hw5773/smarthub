COMPILER=gcc
OUT=aes_128_cbc aes_192_cbc aes_256_cbc \
    aes_128_ecb aes_192_ecb aes_256_ecb \
    bf_128_cbc bf_192_cbc bf_256_cbc
HEADER=crypto.h
COMMON_DIR=../common
COMMON=$(COMMON_DIR)/common.o

AES_128_CBC=openssl.o aes_128_cbc.o
AES_192_CBC=openssl.o aes_192_cbc.o
AES_256_CBC=openssl.o aes_256_cbc.o

AES_128_ECB=openssl.o aes_128_ecb.o
AES_192_ECB=openssl.o aes_192_ecb.o
AES_256_ECB=openssl.o aes_256_ecb.o

BF_128_CBC=openssl.o bf_128_cbc.o
BF_192_CBC=openssl.o bf_192_cbc.o
BF_256_CBC=openssl.o bf_256_cbc.o

OBJS=$(AES_128_CBC) $(AES_192_CBC) $(AES_256_CBC) \
     $(AES_128_ECB) $(AES_192_ECB) $(AES_256_ECB) \
     $(BF_128_CBC) $(BF_192_CBC) $(BF_256_CBC)
CFLAGS=-g -Wall -I/usr/local/include -L/usr/local/lib
LDFLAGS=-lssl -lcrypto -ldl

aes_128_cbc: $(AES_128_CBC) $(HEADER)
	$(COMPILER) -o $@ $(AES_128_CBC) $(COMMON) $(LDFLAGS)

aes_192_cbc: $(AES_192_CBC) $(HEADER)
	$(COMPILER) -o $@ $(AES_192_CBC) $(COMMON) $(LDFLAGS)

aes_256_cbc: $(AES_256_CBC) $(HEADER)
	$(COMPILER) -o $@ $(AES_256_CBC) $(COMMON) $(LDFLAGS)

aes_128_ecb: $(AES_128_ECB) $(HEADER)
	$(COMPILER) -o $@ $(AES_128_ECB) $(COMMON) $(LDFLAGS)

aes_192_ecb: $(AES_192_ECB) $(HEADER)
	$(COMPILER) -o $@ $(AES_192_ECB) $(COMMON) $(LDFLAGS)

aes_256_ecb: $(AES_256_ECB) $(HEADER)
	$(COMPILER) -o $@ $(AES_256_ECB) $(COMMON) $(LDFLAGS)

bf_128_cbc: $(BF_128_CBC) $(HEADER)
	$(COMPILER) -o $@ $(BF_128_CBC) $(COMMON) $(LDFLAGS)

bf_192_cbc: $(BF_192_CBC) $(HEADER)
	$(COMPILER) -o $@ $(BF_192_CBC) $(COMMON) $(LDFLAGS)

bf_256_cbc: $(BF_256_CBC) $(HEADER)
	$(COMPILER) -o $@ $(BF_256_CBC) $(COMMON) $(LDFLAGS)

.c.o:
	$(COMPILER) $(CFLAGS) -c $<

openssl.o: openssl.c
aes_128_cbc.o: aes_128_cbc.c
aes_192_cbc.o: aes_192_cbc.c
aes_256_cbc.o: aes_256_cbc.c
common.o: common.c
bf_128_cbc.o: bf_128_cbc.c
bf_192_cbc.o: bf_192_cbc.c
bf_256_cbc.o: bf_256_cbc.c

clean:
	rm -rf $(OUT) $(OBJS)
