#include <stdio.h>
#include <stdlib.h>

#include "../Headers/generic.h"

int safeMalloc(int sizeof_, char* errorMessage)
{
	int malloc_ = malloc(sizeof_);
	if(malloc_ == NULL)
	{
		printf("<safeMalloc> Error: %s", errorMessage);
		return 0;
	}
	else return malloc_;
}
