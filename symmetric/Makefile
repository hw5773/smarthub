COMPILER=gcc
OUT=aes_128_cbc aes_192_cbc aes_256_cbc \
    aes_128_ecb aes_192_ecb aes_256_ecb \
    aes_128_ctr aes_192_ctr aes_256_ctr \
    aes_128_gcm aes_192_gcm aes_256_gcm \
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

AES_128_CTR=openssl.o aes_128_ctr.o
AES_192_CTR=openssl.o aes_192_ctr.o
AES_256_CTR=openssl.o aes_256_ctr.o

AES_128_GCM=openssl.o aes_128_gcm.o
AES_192_GCM=openssl.o aes_192_gcm.o
AES_256_GCM=openssl.o aes_256_gcm.o

BF_128_CBC=openssl.o bf_128_cbc.o
BF_192_CBC=openssl.o bf_192_cbc.o
BF_256_CBC=openssl.o bf_256_cbc.o

OBJS=$(AES_128_CBC) $(AES_192_CBC) $(AES_256_CBC) \
     $(AES_128_ECB) $(AES_192_ECB) $(AES_256_ECB) \
     $(AES_128_CTR) $(AES_192_CTR) $(AES_256_CTR) \
     $(AES_128_GCM) $(AES_192_GCM) $(AES_256_GCM) \
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

aes_128_ctr: $(AES_128_ECB) $(HEADER)
	$(COMPILER) -o $@ $(AES_128_ECB) $(COMMON) $(LDFLAGS)

aes_192_ctr: $(AES_192_ECB) $(HEADER)
	$(COMPILER) -o $@ $(AES_192_ECB) $(COMMON) $(LDFLAGS)

aes_256_ctr: $(AES_256_ECB) $(HEADER)
	$(COMPILER) -o $@ $(AES_256_ECB) $(COMMON) $(LDFLAGS)

aes_128_gcm: $(AES_128_ECB) $(HEADER)
	$(COMPILER) -o $@ $(AES_128_ECB) $(COMMON) $(LDFLAGS)

aes_192_gcm: $(AES_192_ECB) $(HEADER)
	$(COMPILER) -o $@ $(AES_192_ECB) $(COMMON) $(LDFLAGS)

aes_256_gcm: $(AES_256_ECB) $(HEADER)
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
common.o: common.c
clean:
	rm -rf $(OUT) $(OBJS)
