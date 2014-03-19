#include <stdio.h>
#include <stdlib.h>
#include "Num2Phrase.h"


int main(int argc,char* argv[])
{
	Num2Phrase* pNum2Phrase;
	pNum2Phrase=Num2Phrase::CreateTranslator();

	if (argc==1)
	{
		for (int i=0; i<sizeof(Num)*8; i++)
		{
			Num cNum=1<<i;
			Phrase cPhrase=pNum2Phrase->Translate(cNum);
			printf("%u = %s\n",(unsigned int)cNum,(const char*)cPhrase);
		}
	}
	else
	{
		for (int i=1; i<argc; i++)
		{
			Num cNum=strtoul(argv[i],NULL,10);
			Phrase cPhrase=pNum2Phrase->Translate(cNum);
			printf("%u = %s\n",(unsigned int)cNum,(const char*)cPhrase);
		}
	}

	Num2Phrase::DestroyTranslator();
	return 0;
}
