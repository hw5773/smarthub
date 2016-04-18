#include "common.h"

double get_micro_seconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return tv.tv_sec + (tv.tv_usec/1000000.0);
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

// the unit of time is "us"
void print_log(FILE *fp, const char *str, double t)
{
	fprintf(fp, "%.6lf, %s\n", t, str);
}

