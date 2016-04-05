#ifndef LOGGER
#define LOGGER

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#ifdef LOG_ON

#include "tls_msg_type.h"
#include "ipsec_msg_type.h"

extern FILE *fp;
extern char *filename;

#define printLog(var) fprintf(fp, "%lu, %d, "#var", %s\n", getMicroSecond(), var, filename); fflush(fp);
#define log_close() fclose(fp);


#elif PRINT_ON
#define printLog(var) printf(#var"\n");
#define log_close()

#else
#define printLog(var) 
#define log_close()

#endif

int log_init(char *filen);
unsigned long get_micro_seconds();

#endif
