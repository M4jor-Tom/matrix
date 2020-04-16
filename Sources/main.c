#define WORD 1
#define LETTERS 2
#define FILE_NAME "fichier.txt"

#include <stdio.h>
#include <stdlib.h>

#include "../Headers/link.h"
#include "../Headers/filesManagement.h"

int main()
{
	int count = 0;
	
	//Affichage des mots dans le .txt
	link *wordChainPtr = readFile(FILE_NAME);
	displayChain(wordChainPtr, WORD);
	
	//Affichage des différentes lettres dans le .txt
	link *lettersChainPtr = getLetters(wordChainPtr, NULL, &count);
	displayChain(lettersChainPtr, LETTERS);
	
	
	getProbasMatressFromWordsChain(wordChainPtr);
	
	//Fin du programme
	printf("\n\n");
	system("pause");
	return 0;
}
