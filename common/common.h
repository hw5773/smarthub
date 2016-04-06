#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

double 	get_micro_seconds();
int 	   seed_prng(int);
void	   handle_errors();
void	   print_log(FILE *, unsigned char *, double);
