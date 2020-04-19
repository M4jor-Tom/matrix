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
			//R�cursion/Prochain maillon
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
		//Obtention du dernier node � partir d'un de la cha�ne
		link* lastLinkPtr = lastLink(headLinkPtr);

		//Cr�ation de ce nouveau node et ajout en fin de cha�ne
		lastLinkPtr -> nextLinkPtr = toInsertLinkPtr;
		return headLinkPtr;
	}
}

link* updateLetterChain(link* lettersChainHeadPtr, char letter_, matress* mat, int resize)
{
	if(lettersChainHeadPtr == NULL)
	{
		//Liste nulle: On retourne une liste � un maillon avec la stat
		link* newLetterLinkPtr = newLink("updateLetterChain/lettersChainHeadPtr == NULL");
		newLetterLinkPtr -> letter = letter_;
		newLetterLinkPtr -> letterCount = 1;
		
		if(resize) mat -> size++;
		
		//printf("%d\n", mat -> size);
		return newLetterLinkPtr;
	}
	else if(lettersChainHeadPtr -> letter != letter_)
	{
		//Liste pas nulle, mais lettre non correspondante: On relance la fonction avec le maillon d'apr�s
		lettersChainHeadPtr -> nextLinkPtr = updateLetterChain(lettersChainHeadPtr -> nextLinkPtr, letter_, mat, resize);
		
		if(lettersChainHeadPtr -> nextLinkPtr == NULL)
		{
			//Fin de cha�ne de stats: la lettre n'a pas �t� trouv�e
			//On cr�e une nouvelle stat de lettre
			lettersChainHeadPtr -> nextLinkPtr = newLink("updateLetterChain/else/while");
			//On lui donne la valeur cl� (la lettre)
			lettersChainHeadPtr = lettersChainHeadPtr -> nextLinkPtr;
			lettersChainHeadPtr -> letter = letter_;
			lettersChainHeadPtr -> letterCount = 1;
			if(resize) mat -> size++;
		}
	}
	else 
		//Lettre existante, incr�ment du compteur
		lettersChainHeadPtr -> letterCount++;
	
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

link* getLetters(link *wordChainPtr, link *lettersChainHeadPtr, matress* mat, int resize)
{
	if(wordChainPtr != NULL)
	{
		//Cha�ne contenant les mots pas nulle
		int i = 0;
		for(i = 0; i < strlen(wordChainPtr -> word); i++)
			if(wordChainPtr -> word[i] != ' ' && wordChainPtr -> word[i] != '\n')
			{
				//Pour chaque lettre du mot (sauf espace et entrer)
				lettersChainHeadPtr = updateLetterChain(lettersChainHeadPtr, wordChainPtr -> word[i], mat, resize);
				if(strlen(wordChainPtr -> word) > i)
				{
					//Pas le dernier cycle
					//mat -> m[]
				}
			}
	}
		
	if(wordChainPtr -> nextLinkPtr != NULL)
		//R�cursion avec le mot suivant
		return getLetters(wordChainPtr -> nextLinkPtr, lettersChainHeadPtr, mat, resize);
		
	else return lettersChainHeadPtr;
}

void setMatressSize(matress* matPtr, link* wordChainHeadPtr)
{
	link *lettersListHeadPtr = NULL;
		
	if(wordChainHeadPtr == NULL) 
		printf("<setMatressSize> Error: wordChainHeadPtr == NULL\n");
	else lettersListHeadPtr = getLetters(wordChainHeadPtr, lettersListHeadPtr, matPtr, 1);
}

matress getProbasMatressFromWordsChain(link* wordChainHeadPtr)
{
	if(wordChainHeadPtr == NULL) printf("<getProbasMatressFromWordsChain> Error: wordChainHeadPtr == NULL\n");
	else
	{
		//Initialiser la matrice nulle
		matress mat;
		mat.size = 0;
		mat.label = NULL;
		mat.m = NULL;
		
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
		
		//Cr�er la liste de lettres
		link *lettersListHeadPtr = getLetters(wordChainHeadPtr, NULL, &mat, 0);
		
		//Visualiser la liste de lettres
		displayChain(lettersListHeadPtr, LETTERS);
		
				
		//Cr�er un array � partir de la liste
		int lettersCount;
		mat.label = linkPtrToLettersArray(lettersListHeadPtr, &lettersCount);
		
		plotMatress(mat);
	}
}

void plotMatress(matress mat)
{
	int i = 0;
	printf("|X|");
	for(i = 0; i < mat.size; i++)
	{
		//Pour chaque lettre diff�rente
		printf("|%c        |", mat.label[i]);
	}
	printf("\n");
	for(i = 0; i < mat.size; i++)
	{
		//Pour chaque lettre diff�rente
		printf("|%c|", mat.label[i]);
		int j = 0;
		for(j = 0; j < mat.size; j++)
		{
			printf("|P%c-%c:%.2f|", mat.label[i], mat.label[j], mat.m[i][j]);
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
