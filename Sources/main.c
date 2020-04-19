#define WORD 1
#define LETTERS 2
#define FILE_NAME "liste_francais_no_ac.txt"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Headers/link.h"
#include "../Headers/filesManagement.h"

int main()
{
	srand(time(NULL));
	
	//Affichage des mots dans le .txt
	link *wordChainPtr = readFile(FILE_NAME);
	//displayChain(wordChainPtr, WORD);
	
	//Affichage des différentes lettres dans le .txt
	//link *lettersChainPtr = getLetters(wordChainPtr, NULL, &count);
	//displayChain(lettersChainPtr, LETTERS);
	
	
	matress mat = getProbasMatressFromWordsChain(wordChainPtr);
	char length[5] = "0", quit[5];
	do
	{
		//scanf("%s", length);
		strcpy(quit, length);
		int intlength = (int)atoi(length);
		
		sleep(1);
		
		/*char* word = safeMalloc(sizeof(char) * intlength);
		word = */generateWord(&mat, &intlength);
		/*int i = 0;
		for(i = 0; i < intlength; i++)
		{
			printf("%c", word[i]);
			free(word[i]);
		}*/
			
		printf("\n");
	}while(quit != "q");
	
	return 0;
}
