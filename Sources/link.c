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

link* updateLetterChain(link* lettersChainHeadPtr, char letter_, matress* mat)
{
	if(lettersChainHeadPtr == NULL)
	{
		//Liste nulle: On retourne une liste à un maillon avec la stat
		link* newLetterLinkPtr = newLink("updateLetterChain/lettersChainHeadPtr == NULL");
		newLetterLinkPtr -> letter = letter_;
		newLetterLinkPtr -> letterCount = 1;
		
		mat -> size++;
		
		//printf("%d\n", mat -> size);
		return newLetterLinkPtr;
	}
	else if(lettersChainHeadPtr -> letter != letter_)
	{
		//Liste pas nulle, mais lettre non correspondante: On relance la fonction avec le maillon d'après
		lettersChainHeadPtr -> nextLinkPtr = updateLetterChain(lettersChainHeadPtr -> nextLinkPtr, letter_, mat);
		
		if(lettersChainHeadPtr -> nextLinkPtr == NULL)
		{
			//Fin de chaîne de stats: la lettre n'a pas été trouvée
			//On crée une nouvelle stat de lettre
			lettersChainHeadPtr -> nextLinkPtr = newLink("updateLetterChain/else/while");
			//On lui donne la valeur clé (la lettre)
			lettersChainHeadPtr = lettersChainHeadPtr -> nextLinkPtr;
			lettersChainHeadPtr -> letter = letter_;
			lettersChainHeadPtr -> letterCount = 1;
			mat -> size++;
		}
	}
	else 
		//Lettre existante, incrément du compteur
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

link* getLetters(link *wordChainPtr, link *lettersChainHeadPtr, matress* mat)
{
	if(wordChainPtr != NULL)
	{
		//Chaîne contenant les mots pas nulle
		int i = 0;
		link* previousLetterPtr = NULL;
		int size = sizeof(char);
		for(i = 0; i < strlen(wordChainPtr -> word); i++)
			if(wordChainPtr -> word[i] != ' ' && wordChainPtr -> word[i] != '\n')
			{
				//Pour chaque lettre du mot (sauf espace et entrer)
				lettersChainHeadPtr = updateLetterChain(lettersChainHeadPtr, wordChainPtr -> word[i], mat);
				if(previousLetterPtr != NULL)
				{
					//Arriver en fin de liste des caractères suivant ce caractère
					while(previousLetterPtr -> nextFollowingLetterPtr != NULL)
						previousLetterPtr = previousLetterPtr -> nextFollowingLetterPtr;
						
					//On rajoute une structure pour la lettre qui arrive
					previousLetterPtr -> nextFollowingLetterPtr = newLink("getLetters/previousLetterPtr -> nextFollowingLetterPtr");
					
					//On la complète avec la lettre courante
					//Pour le caractère précédent, on ajoute le caractère courant à sa liste interne
					previousLetterPtr -> nextFollowingLetterPtr -> letter = wordChainPtr -> word[i];
					
					//Visualiser ce que comprend le programme en termes d'enchainement des lettres
					printf("%c then %c\n", previousLetterPtr -> letter, previousLetterPtr -> nextFollowingLetterPtr -> letter);
				}
				
				//Fin de processus, préparation du cycle suivant
				previousLetterPtr = lettersChainHeadPtr;
			}
	}
		
	if(wordChainPtr -> nextLinkPtr != NULL)
		//Récursion avec le mot suivant
		return getLetters(wordChainPtr -> nextLinkPtr, lettersChainHeadPtr, mat);
		
	else return lettersChainHeadPtr;
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
		
		//Créer la liste de lettres
		link *lettersListHeadPtr = getLetters(wordChainHeadPtr, NULL, &mat);
		
		//Visualiser la liste de lettres
		displayChain(lettersListHeadPtr, LETTERS);
		mat.m = safeMalloc(sizeof(float*) * mat.size, "getProbasMatressFromWordsChain/else");
		
				
		//Créer un array à partir de la liste
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
		//Pour chaque lettre différente
		printf("|%c        |", mat.label[i]);
	}
	printf("\n");
	for(i = 0; i < mat.size; i++)
	{
		//Pour chaque lettre différente
		printf("|%c|", mat.label[i]);
		mat.m[i] = safeMalloc(sizeof(float) * mat.size, "getProbasMatressFromWordsChain/else/for");
		int j = 0;
		for(j = 0; j < mat.size; j++)
		{
			mat.m[i][j] = 0.0;
			printf("|P%c-%c:%.2f|", mat.label[i], mat.label[j]);
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
			while(linkPtr -> nextFollowingLetterPtr != NULL)
			{
				linkPtr = linkPtr -> nextFollowingLetterPtr;
				printf("-%c;\n", linkPtr -> letter);
			}
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
