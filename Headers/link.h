#define WORD_SIZE 40

typedef struct link
{
	char word[WORD_SIZE];
	char letter;
	int letterCount;
	
	struct link* nextFollowingLetterPtr;
	
	struct link* nextLinkPtr;
}link;

typedef struct matress
{
	int size;
	char *label;
	float **m;
}matress;

//Creates a new link structure adress with malloc. If it fails to, it prompts errorMessage
link* newLink(char* errorMessage);

//Get the last link of a chain from a link of it
link* lastLink(link* currentLinkPtr);

//Inserts a previously created toInsertLinkPtr at the end of a chain designed by a headLinkPtr
link* insertLink(link* headLinkPtr, link* toInsertLinkPtr);

//Updates the letters stat chain with a new value
link* updateLetterChain(link* lettersChainHeadPtr, char letter_, matress* mat, int setSize);

char* linkPtrToLettersArray(link* linkPtr, int* count);

void setMatressSize(matress* matPtr, link* wordChainHeadPtr);

//Outputs a matress from a wordChain pointor
matress getProbasMatressFromWordsChain(link* wordlettersChainHeadPtr);

int list_search(link* lettersListPtr, char letter);

//Manages every sum a matress' lines to be equal to 1.0
void ponderateMatress(matress* mat);

//Generates a word from a matress
char* generateWord(matress* mat, int* length);

//Plots an inputed matress of probas
void plotMatress(matress mat);

//Counts letters in a chain of link words
link* getLetters(link *wordChainPtr, link *lettersChainHeadPtr, matress* mat, int setSize, int setProba);

//Displays a link
void displayLink(link* linkPtr, int type);

//Displays a chain, with a given type of display (WORD or LETTERS_COUNT)
void displayChain(link* lettersChainHeadPtr, int type);
