#include "logger.h"


#ifdef LOG_ON
FILE *fp;
char *filename;
#endif

int log_init(char *filen){

#ifdef LOG_ON
	
	filename = filen;

   fp = fopen(filename, "w");

   if(fp == NULL)
      printf("Caanot open file\n");

#else
   return 1;

#endif
}

unsigned long get_micro_seconds(){

   struct timeval tv;
   gettimeofday(&tv, NULL);
   return 1000000*(tv.tv_sec) + tv.tv_usec;
}
