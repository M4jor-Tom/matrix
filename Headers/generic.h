int safeMalloc(int sizeof_, char* errorMessage);

int safeRealloc(int ptr, int sizeof_, char* errorMessage);

int safeAlloc(int ptr, int sizeof_, char* errorMessage);

int array_search(char needle, int *haystack, int length);
