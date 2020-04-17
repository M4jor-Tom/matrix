#include <stdio.h>
#include <stdlib.h>

#include "../Headers/generic.h"

int safeMalloc(int sizeof_, char* errorMessage)
{
	int malloc_ = malloc(sizeof_);
	if(malloc_ == NULL)
	{
		printf("<safeMalloc> Error: %s\n", errorMessage);
		return 0;
	}
	else return malloc_;
}

int safeRealloc(int ptr, int sizeof_, char* errorMessage)
{
	int realloc_ = realloc(ptr, sizeof_);
	if(realloc_ == NULL)
	{
		printf("<safeRealloc> Error: %s\n", errorMessage);
		return 0;
	}
	else return realloc_;
}

int safeAlloc(int ptr, int sizeof_, char* errorMessage)
{
	if(ptr == NULL)
	{
		//printf("safealloc:malloc\n");
		return safeMalloc(sizeof_, errorMessage);
	}
	else 
	{
		//printf("safealloc:realloc\n");
		return safeRealloc(ptr, sizeof_, errorMessage);
	}
}

int array_search(char needle, int *haystack, int length)
{
	int i;
	for(i = 0; i < length; i++)
	{
		if(haystack[i] == needle)
			return i;
	}
	return - 1;
}
