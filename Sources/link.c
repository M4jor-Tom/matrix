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

link* updateLetterChain(link* chainHeadPtr, char letter_, int* countPtr)
{
	if(chainHeadPtr == NULL)
	{
		//Liste nulle: On retourne une liste à un maillon avec la stat
		link* ret = newLink("updateLetterChain/chainHeadPtr == NULL");
		ret -> letter = letter_;
		(*countPtr)++;
		return ret;
	}
	else if(chainHeadPtr -> letter != letter_)
	{
		//Liste pas nulle, mais lettre non correspondante: On relance la fonction avec le maillon d'après
		chainHeadPtr -> nextLinkPtr = updateLetterChain(chainHeadPtr -> nextLinkPtr, letter_, countPtr);
		
		if(chainHeadPtr -> nextLinkPtr == NULL)
		{
			//Fin de chaîne de stats: la lettre n'a pas été trouvée
			//On crée une nouvelle stat de lettre
			chainHeadPtr -> nextLinkPtr = newLink("updateLetterChain/else/while");
			
			//On lui donne la valeur clé (la lettre)
			chainHeadPtr = chainHeadPtr -> nextLinkPtr;
			chainHeadPtr -> letter = letter_;
			(*countPtr)++;
		}
	}
	
	return chainHeadPtr;
}

link* getLetters(link *wordChainPtr, link *lettersChainHeadPtr, int* countPtr)
{
	int i = 0;
	
	if(wordChainPtr != NULL)
		//Chaîne contenant les mots pas nule
		for(i = 0; i < strlen(wordChainPtr -> word); i++)
		{
			//Pour chaque lettre du mot
			lettersChainHeadPtr = updateLetterChain(lettersChainHeadPtr, wordChainPtr -> word[i], countPtr);
		}
		
	if(wordChainPtr -> nextLinkPtr != NULL)
		//Récursion avec le mot suivant
		return getLetters(wordChainPtr -> nextLinkPtr, lettersChainHeadPtr, countPtr);
		
	else return lettersChainHeadPtr;
}


matress getProbasMatressFromWordsChain(link* wordChainHeadPtr)
{
	if(wordChainHeadPtr == NULL) printf("<getProbasMatressFromWordsChain> Error: wordChainHeadPtr == NULL\n");
	else
	{
		matress mat;
		mat.size = 0;
		int count;
		link* lettersList = getLetters(wordChainHeadPtr, NULL, &mat.size);
		float *arrayHeadPtr = safeMalloc(sizeof(float*) * mat.size, "getProbasMatressFromWordsChain/else");
		
		for(count = 0; count < mat.size; count++)
		{
			//Pour chaque lettre différente
			arrayHeadPtr[count] = safeMalloc(sizeof(float) * mat.size, "getProbasMatressFromWordsChain/else/for");
			//*arrayHeadPtr[count] = ...
		}
		
		printf("\nMatress size: %d\n", mat.size);
	}
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
			if(linkPtr -> letter == '\n')
				printf("Enter;");
			else if(linkPtr -> letter == ' ')
				printf("Space;");
			else printf("%c;", linkPtr -> letter);
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
		while(chainListPtr -> nextLinkPtr != NULL)
		{
			chainListPtr = chainListPtr -> nextLinkPtr;
			displayLink(chainListPtr, type);
		}
	}
	printf("\n");
}
