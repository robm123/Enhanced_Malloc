#ifndef MYMALLOC_H   
#define MYMALLOC_H     
#include <stdio.h>
#include <stdlib.h>
#define malloc( x ) myMalloc( x , __FILE__ , __LINE__ )
#define free( x ) myfree( x , __FILE__ , __LINE__ )

void *mymalloc(unsigned int size, char *file, int line);

void myfree(void *p, char *file, int line);




struct memEntry
{
	struct memEntry *prev;
   // struct memEntry *cur;
	struct memEntry *next;
	int free;   				 //1 = NOT FREE------0 = FREE
	int size;
								//keep track of pointer variable???
	
};
typedef struct memEntry memEntry;





#endif
