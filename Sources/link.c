#define WORD 1
#define LETTERS 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/link.h"

link* newLink(char* errorMessage)
{
	link* ret = (link*)safeMalloc(sizeof(link), errorMessage);
	strcpy(ret -> word, "\0");
	ret -> letter = '\0';
	ret -> letterCount = 0;
	ret -> nextLinkPtr = NULL;
	return ret;
}

link* lastLink(link* currentLinkPtr)
{
	if(currentLinkPtr != NULL)
	{
		if(currentLinkPtr -> nextLinkPtr == NULL)
			//Dernier chainon
			return currentLinkPtr;
			
		else 
			//Récursion/Prochain maillon
			return lastLink(currentLinkPtr -> nextLinkPtr);
	}
	else return NULL;
}

link* insertLink(link* headLinkPtr, link* toInsertLinkPtr)
{
	if(headLinkPtr == NULL)
	{
		//Cas d'une liste nulle
		toInsertLinkPtr -> nextLinkPtr = NULL;
		return toInsertLinkPtr;
	}
	else
	{
		//Obtention du dernier node à partir d'un de la chaîne
		link* lastLinkPtr = lastLink(headLinkPtr);

		//Création de ce nouveau node et ajout en fin de chaîne
		lastLinkPtr -> nextLinkPtr = toInsertLinkPtr;
		return headLinkPtr;
	}
}

link* updateLetterChain(link* lettersChainHeadPtr, char letter_, matress* mat, int setSize)
{
	/*int i;
	for(i = 0; i < 'a' - 'z'; i++)
	{
		lettersChainHeadPtr -> letter = 'a' + i;
		mat -> size++;
		lettersChainHeadPtr = newLink("updateLetterChain/fast for");
		if('a' + i != 'z')
			lettersChainHeadPtr = lettersChainHeadPtr -> nextLinkPtr;
	}*/
	if(lettersChainHeadPtr == NULL)
	{
		//Liste nulle: On retourne une liste à un maillon avec la stat
		link* newLetterLinkPtr = newLink("updateLetterChain/lettersChainHeadPtr == NULL");
		newLetterLinkPtr -> letter = letter_;
		newLetterLinkPtr -> letterCount = 1;
		
		if(setSize)
		{
			mat -> size++;
			//printf("new: %c\n", letter_);
		} 
		
		return newLetterLinkPtr;
	}
	else if(lettersChainHeadPtr -> letter != letter_)
	{
		//Liste pas nulle, mais lettre non correspondante: On relance la fonction avec le maillon d'après
		//printf("%c ", letter_);
		lettersChainHeadPtr -> nextLinkPtr = updateLetterChain(lettersChainHeadPtr -> nextLinkPtr, letter_, mat, setSize);
		
		if(lettersChainHeadPtr -> nextLinkPtr == NULL)
		{
			//Fin de chaîne de stats: la lettre n'a pas été trouvée
			//On crée une nouvelle stat de lettre
			lettersChainHeadPtr -> nextLinkPtr = newLink("updateLetterChain/else/while");
			//On lui donne la valeur clé (la lettre)
			lettersChainHeadPtr = lettersChainHeadPtr -> nextLinkPtr;
			lettersChainHeadPtr -> letter = letter_;
			lettersChainHeadPtr -> letterCount = 1;
			if(setSize) mat -> size++;
		}
	}
	/*else 
		//Lettre existante, incrément du compteur
		lettersChainHeadPtr -> letterCount++;*/
		
	
	return lettersChainHeadPtr;
}

char* linkPtrToLettersArray(link* linkPtr, int* count)
{
	if(linkPtr != NULL)
	{
		int size = sizeof(char);
		char* recipient = safeMalloc(size, "linkPtrToLettersArray/Init");
		*count = 0;
		do
		{
			recipient[(*count)++] = linkPtr -> letter;
			
			//Maillon suivant
			if(linkPtr -> nextLinkPtr != NULL)
			{
				size = size + sizeof(char);
				recipient = safeRealloc(recipient, size, "linkPtrToLettersArray/Init");
			}
			linkPtr = linkPtr -> nextLinkPtr;
		}while(linkPtr != NULL);
		
		return recipient;
	}
	else return NULL;
}

link* getLetters(link *wordChainPtr, link *lettersChainHeadPtr, matress* mat, int setSize, int setProba)
{
	if(wordChainPtr != NULL)
	{
		//Chaîne contenant les mots pas nulle
		
		//On prend un mot sur...
		int i;
		for(i = 1; i < 2; i++)
			if(wordChainPtr -> nextLinkPtr != NULL)
				wordChainPtr = wordChainPtr -> nextLinkPtr;
				
				
		strToLower(wordChainPtr -> word);
		for(i = 0; i < strlen(wordChainPtr -> word); i++)
			if
			(
				wordChainPtr -> word[i] != '\0' && 
				wordChainPtr -> word[i] != '\n'
			)
			{
				//Pour chaque lettre du mot (sauf espace et entrer)
				lettersChainHeadPtr = updateLetterChain(lettersChainHeadPtr, wordChainPtr -> word[i], mat, setSize);
			}
			
		if(setProba)	
			for(i = 0; i < strlen(wordChainPtr -> word); i++)
				if
				(
					wordChainPtr -> word[i] != '\0' && 
					wordChainPtr -> word[i] != '\n'
				)
				{
					//Pour chaque lettre du mot (sauf espace et entrer)
					link *tempLettersChainHeadPtr = lettersChainHeadPtr;
					
					if(!setSize)
					{
						int j = 0, jprev = 0, jnext = 0, prevSet = 0, nextSet = 0;
						//Obtenir jprev et jnext
						while(tempLettersChainHeadPtr != NULL)
						{
							if(wordChainPtr -> word[i] == tempLettersChainHeadPtr -> letter)
							{
								//La lettre de la chaine correspond à celle du mot
								jprev = j;
								prevSet = 1;
							}
							
							if(wordChainPtr -> word[i + 1] == tempLettersChainHeadPtr -> letter)
							{
								//La lettre de la chaine correspond à celle d'après du mot
								jnext = j;
								nextSet = 1;
							}
							
							/*printf("scan: word[%d] = %c ? letter[%d] = %c", i, wordChainPtr -> word[i], j, tempLettersChainHeadPtr -> letter);
							if(jprev == j && prevSet) printf(" before ");
							if(jnext == j && nextSet) printf(" after");
							printf("\n");*/
							
							tempLettersChainHeadPtr = tempLettersChainHeadPtr -> nextLinkPtr;
							j++;
						}
						
						float former = - 1.0;
						if(wordChainPtr -> word[i] != '\n' && wordChainPtr -> word[i + 1] != '\0' && prevSet && nextSet)
							//Si le caractère suivant n'est pas fin de mot / chaîne
							former = mat -> m[jprev][jnext]++;
							
						prevSet = 0;
						nextSet = 0;
						
						/*printf
						(
							"Word: %s\nLetters: %c-%c: %.2f -> %.2f (%d/%d)\n\n",
							wordChainPtr -> word,
							wordChainPtr -> word[i],
							wordChainPtr -> word[i + 1],
							former,
							mat -> m[jprev][jnext],
							jprev,
							jnext
						);*/
					}
				}
	}
		
	if(wordChainPtr -> nextLinkPtr != NULL)
		//Récursion avec le mot suivant
		return getLetters(wordChainPtr -> nextLinkPtr, lettersChainHeadPtr, mat, setSize, setProba);
		
	else return lettersChainHeadPtr;
}

int list_search(link* lettersListPtr, char letter)
{
	int i = 0;
	while(lettersListPtr != NULL)
	{
		if(lettersListPtr -> letter == letter)
			return i;
		i++;
		lettersListPtr = lettersListPtr -> nextLinkPtr;
	}
	return -1;
}

void ponderateMatress(matress* mat)
{
	//Init
	float *sum = NULL, avg = 0.0;
	sum = safeMalloc(sizeof(float), "ponderateMatress/Init");
	
	//Summing
	int i, j;
	for(i = 0; i < mat -> size; i++)
		for(j = 0; j < mat -> size; j++)
		sum[i] = sum[i] + mat -> m[i][j];
		
	//Avging
	for(i = 0; i < mat -> size; i++)
		for(j = 0; j < mat -> size; j++)
			if(sum[i])
			mat -> m[i][j] = mat -> m[i][j] / sum[i];
}

char* generateWord(matress* mat, int* length)
{
	int _length = *length == 0 ? rand() % 7 + 2 : *length;
	char* word = safeMalloc(sizeof(char) * _length, "generateWord/Init");
	
	//0.0 < rng < 1.0
		
	word[0] = (rand() % ('a' - 'z')) + 'a';
	//printf("<generateWord> length: %d, first letter: %c\n", _length, word[0]);
	printf("<generateWord> ");
	int i, j;
	for(i = 0; i < _length; i++)
	{
		float rng = (float)(rand() % 1000) / 1000;
		int choice = 0;
		//printf("After letter: %c, ", word[i - 1]);
		
		//Chercher l'index de lettre dans le label
		int letterIndex = array_search(word[i], mat -> label, mat -> size);
		if(letterIndex != -1)
			for(j = 0; j < mat -> size; j++)
			{
				//printf("label[%d] = %c -> rng(%.2f) -> label[%d] = %c\n", letterIndex, mat -> label[letterIndex], rng, j, mat -> label[j]);
				
				if(rng > 0.0) 
				{
					//Choix si rng encore > 0.0
					choice = j;
				}
				
				//Baisse du rng
				rng = rng - mat -> m[letterIndex][j];
			}
		else printf("<generateWord> Error: Unfound letter\n");
		//printf("index %d chosen, letter %c chosen\n", choice, mat -> label[choice]);
		printf("%c", word[i]);
		word[i + 1] = mat -> label[choice];
	}
	*length = _length;
	return word;
}

void setMatressSize(matress* matPtr, link* wordChainHeadPtr)
{
	link *lettersListHeadPtr = NULL;
		
	if(wordChainHeadPtr == NULL) 
		printf("<setMatressSize> Error: wordChainHeadPtr == NULL\n");
	else lettersListHeadPtr = getLetters(wordChainHeadPtr, lettersListHeadPtr, matPtr, 1, 0);
}

matress getProbasMatressFromWordsChain(link* wordChainHeadPtr)
{
	//Initialiser la matrice nulle
	matress mat;
	mat.size = 0;
	mat.label = NULL;
	mat.m = NULL;
	
	if(wordChainHeadPtr == NULL) printf("<getProbasMatressFromWordsChain> Error: wordChainHeadPtr == NULL\n");
	else
	{
		setMatressSize(&mat, wordChainHeadPtr);
		mat.m = safeMalloc(sizeof(float*) * mat.size, "getProbasMatressFromWordsChain/else");
		int i;
		for(i = 0; i < mat.size; i++)
		{
			mat.m[i] = safeMalloc(sizeof(float) * mat.size, "getProbasMatressFromWordsChain/else");
			int j;
			for(j = 0; j < mat.size; j++)
				mat.m[i][j] = 0.0;
		}
		
		printf("size: %d\n", mat.size);
		
		//Créer la liste de lettres
		link *lettersListHeadPtr = getLetters(wordChainHeadPtr, NULL, &mat, 0, 0);
		
		//Visualiser la liste de lettres
		//displayChain(lettersListHeadPtr, LETTERS);
		
		//Pondérer la matrice
		getLetters(wordChainHeadPtr, lettersListHeadPtr, &mat, 0, 1);
		ponderateMatress(&mat);
				
		//Créer un array à partir de la liste
		int lettersCount;
		mat.label = linkPtrToLettersArray(lettersListHeadPtr, &lettersCount);
		
		plotMatress(mat);
	}
	return mat;
}

void plotMatress(matress mat)
{
	int i = 0;
	printf("|X|");
	for(i = 0; i < mat.size; i++)
	{
		//Pour chaque lettre différente
		//printf("|%c        |", mat.label[i]);
		printf("|%c   |", mat.label[i]);
	}
	printf("\n");
	for(i = 0; i < mat.size; i++)
	{
		//Pour chaque lettre différente
		printf("|%c|", mat.label[i]);
		int j = 0;
		for(j = 0; j < mat.size; j++)
		{
			//printf("|P%c-%c:%.2f|", mat.label[i], mat.label[j], mat.m[i][j]);
			printf("|%.2f|", mat.m[i][j]);
		}
		printf("\n");
	}
	
	printf("\nMatress size: %d\n", mat.size);
}

void displayLink(link* linkPtr, int type)
{
	if(linkPtr != NULL)
	{
		if(type == WORD)
		{
			printf("%s", linkPtr -> word);
		}
		else if(type == LETTERS)
		{
			printf("%c;\n", linkPtr -> letter);
		}
	}
	
	else printf("<displayLink> Error: linkPtr == NULL\n");
}

void displayChain(link* chainListPtr, int type)
{
	if(chainListPtr == NULL) printf("<displayChain> Error: chainListPtr == NULL\n");
	else 
	{
		displayLink(chainListPtr, type);
		if(chainListPtr -> nextLinkPtr != NULL)
			displayChain(chainListPtr -> nextLinkPtr, type);
	}
	printf("\n");
}
