#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <openssl/x509.h>

double		get_micro_seconds();
int 	   	seed_prng(int);
void	   	handle_errors();
void	   	print_log(FILE *, const char *, double);
