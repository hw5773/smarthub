#include "common.h"

unsigned long get_micro_seconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return 1000000*tv.tv_sec + tv.tv_usec;
}

int seed_prng(int bytes)
{
	srand(time(NULL));

	return 1;
}

void handle_errors(void)
{
	ERR_print_errors_fp(stderr);
	abort();
}