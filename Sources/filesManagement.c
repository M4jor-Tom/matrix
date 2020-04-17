#define WORD_SIZE 40

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/generic.h"
#include "../Headers/link.h"
#include "../Headers/filesManagement.h"

link* readFile(char* path)
{
	FILE* filePtr = fopen(path, "r+");
	char newWord[WORD_SIZE];
	link* recipientHeadListPtr = NULL;
	
	if(filePtr == NULL)
	{
		printf("\n\nError: readFile\n\n");
	}
	else if(fgets(newWord, WORD_SIZE, filePtr))
	{
		//Création du premier chaînon
		recipientHeadListPtr = newLink("readFile/elseif");
		recipientHeadListPtr -> nextLinkPtr = NULL;
		strcpy(recipientHeadListPtr -> word, newWord);
		
		while(fgets(newWord, WORD_SIZE, filePtr))
		{
			//Création du prochain chaînon
			link * newLinkPtr = newLink("readFile/while");
			newLinkPtr -> nextLinkPtr = NULL;
			strcpy(newLinkPtr -> word, newWord);
			
			recipientHeadListPtr = 
				insertLink(
					recipientHeadListPtr,
					newLinkPtr
				);
			
		}
	}
	
	if(recipientHeadListPtr == NULL) 
		printf("<readFile> Warning: NULL return\n");
	
	return recipientHeadListPtr;
}
