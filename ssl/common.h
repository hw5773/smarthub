#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <openssl/bio.h>

#ifndef NUM_OF_CRYPT
#define NUM_OF_CRYPT 100000
#endif

extern double log_time[16];
extern SSL *fake;

double		get_micro_seconds();
int 	   	seed_prng(int);
void	   	handle_errors();
void	   	print_log(FILE *, const char *, double);
