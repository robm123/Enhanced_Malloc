#include <stdio.h>
#include <stdlib.h>
#include "myMalloc.h"
#define BLOCK 5000



static char memblock[BLOCK]; 
static const int mementriesSize = BLOCK/sizeof(struct memEntry)+1; 
static void *memEntries[BLOCK/sizeof(struct memEntry)+1] = {0};


static int getFreeIndex() 
{
	int i;
	for (i = 0; i < mementriesSize; i++)
	{
		if (memEntries[i] == 0)
		return i;
	}		
	return 1; 
}


void *myMalloc(unsigned int userSize, char *file, int line)
{
	if (userSize == 0) 
	{
		fprintf(stderr, "Can't Allocate 0 bytes In FILE: '%s' on LINE: '%d'\n", file, line);
		return 0;
	}
	
	static int initialized = 0;
	struct memEntry *ptr;
	struct memEntry *next;
	static struct memEntry *head;
	


	if(!initialized)	
	{
		memEntries[getFreeIndex()] = memblock;
		head = (struct memEntry*) memblock;
		head->prev =0;
		head->next = 0;
		head->size = BLOCK - sizeof(struct memEntry);
		head->free = 1;
		initialized = 1;
		
	}

	ptr = head;
	
	
	while (ptr != 0)
	{
		if(ptr->size < userSize || !ptr->free)
		 {
			ptr = ptr->next;
		 }

		else
		 {
			
			next = (struct memEntry*)((char*)ptr + sizeof(struct memEntry) + userSize);
			next->prev = ptr;
			next->next = ptr->next;
			next->size = ptr->size - sizeof(struct memEntry) - userSize;
			next->free = 1;
			memEntries[getFreeIndex()] = next;
			ptr->size = userSize;
			ptr->free = 0;
			ptr->next = next;
			return (char*)ptr + sizeof(struct memEntry);
		}
	} 

		fprintf(stderr, "No Enough Memory (%d bytes) in FILE: '%s' on LINE: '%d'\n", userSize, file, line);
		return 0;
}


void myfree(void *p, char *file, int line)
{
	
	
	if (p == NULL)
	{
		fprintf(stderr, "Can't Free Null Pointer in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}
	
	struct memEntry *ptr;
	struct memEntry *next;
	struct memEntry *prev;
	struct memEntry *temp;
	ptr = (struct memEntry*)((char*)p - sizeof(struct memEntry));
	
	if(ptr != next)
	{
		fprintf(stderr, "\nBAD POINTER!! in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}
	
	
	
	
	next=ptr->next;
	prev=ptr->prev;
	temp=ptr;
	
	
	int i;
	int found = 0;
	for (i = 0; i < mementriesSize; i++) 
	{
		if (ptr == memEntries[i] && !ptr->free) 
		{
			found = 1; 
			break;
		}
	}
	if (!found) 
	{
		fprintf(stderr, "memory NOT FOUND in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}

	if(prev != 0 && prev->free)
	{

		prev->size += sizeof(struct memEntry) + ptr->size;
		memEntries[i] = 0;
	}
	else
	{ 
		ptr->free = 1;
		temp = ptr;	
	}
	if(next != 0 && next->free)
	{
		temp->size += sizeof(struct memEntry) + next->size;
		temp->next = next->next;
		for (i = 0; i < mementriesSize; i++) 
		{
			if (next == memEntries[i]) 
			{
				memEntries[i] = 0; 
				break;
			}
		}
	}
}


/*
main()
{
		
	int* ptr = (int*)malloc(2000);
	int* ptr1 = (int*)malloc(2000);
	int* ptr2 = (int*)malloc(1000);
	
	
//	int* ptr3 = (int*)malloc(1000);
//	int* ptr4 = (int*)malloc(1000);
	

//	int x;
//	free(&x);
	

	return 0;
}
*/
