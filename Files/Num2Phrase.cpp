#include "Num2Phrase.h"


Num2Phrase* Num2Phrase::m_pNum2Phrase=0;


/////////////////////////////////
// Singleton Interface (below) //


Num2Phrase* Num2Phrase::CreateTranslator()
{
	if (m_pNum2Phrase==0)
	{
		m_pNum2Phrase=new Num2Phrase;
		m_pNum2Phrase->WriteDictionary();
	}
	return m_pNum2Phrase;
}


void Num2Phrase::DestroyTranslator()
{
	if (m_pNum2Phrase!=0)
	{
		m_pNum2Phrase->EraseDictionary();
		delete m_pNum2Phrase;
	}
	m_pNum2Phrase=0;
}


// Singleton Interface (above) //
/////////////////////////////////


//////////////////////////////////////
// Constructor + Destructor (below) //


Num2Phrase::Num2Phrase()
{
}


Num2Phrase::~Num2Phrase()
{
}


// Constructor + Destructor (above) //
//////////////////////////////////////


///////////////////////////////
// Dictionary Access (below) //


enum TOKEN
{
	ZERO      =  0,
	ONE       =  1,
	TWO       =  2,
	THREE     =  3,
	FOUR      =  4,
	FIVE      =  5,
	SIX       =  6,
	SEVEN     =  7,
	EIGHT     =  8,
	NINE      =  9,
	TEN       = 10,
	ELEVEN    = 11,
	TWELVE    = 12,
	THIRTEEN  = 13,
	FOURTEEN  = 14,
	FIFTEEN   = 15,
	SIXTEEN   = 16,
	SEVENTEEN = 17,
	EIGHTEEN  = 18,
	NINETEEN  = 19,
	TWENTY    = 20,
	THIRTY    = 30,
	FORTY     = 40,
	FIFTY     = 50,
	SIXTY     = 60,
	SEVENTY   = 70,
	EIGHTY    = 80,
	NINETY    = 90,
	HUNDRED       ,
	THOUSAND      ,
	MILLION       ,
	BILLION       ,
	AND           ,
	COMMA         ,
	MAX_TOKEN
};


void Num2Phrase::WriteDictionary()
{
	m_pDictionary=new Dictionary<Phrase>(MAX_TOKEN);

	m_pDictionary->Add("zero"     ,ZERO     );
	m_pDictionary->Add("one"      ,ONE      );
	m_pDictionary->Add("two"      ,TWO      );
	m_pDictionary->Add("three"    ,THREE    );
	m_pDictionary->Add("four"     ,FOUR     );
	m_pDictionary->Add("five"     ,FIVE     );
	m_pDictionary->Add("six"      ,SIX      );
	m_pDictionary->Add("seven"    ,SEVEN    );
	m_pDictionary->Add("eight"    ,EIGHT    );
	m_pDictionary->Add("nine"     ,NINE     );
	m_pDictionary->Add("ten"      ,TEN      );
	m_pDictionary->Add("eleven"   ,ELEVEN   );
	m_pDictionary->Add("twelve"   ,TWELVE   );
	m_pDictionary->Add("thirteen" ,THIRTEEN );
	m_pDictionary->Add("fourteen" ,FOURTEEN );
	m_pDictionary->Add("fifteen"  ,FIFTEEN  );
	m_pDictionary->Add("sixteen"  ,SIXTEEN  );
	m_pDictionary->Add("seventeen",SEVENTEEN);
	m_pDictionary->Add("eighteen" ,EIGHTEEN );
	m_pDictionary->Add("nineteen" ,NINETEEN );
	m_pDictionary->Add("twenty"   ,TWENTY   );
	m_pDictionary->Add("thirty"   ,THIRTY   );
	m_pDictionary->Add("forty"    ,FORTY    );
	m_pDictionary->Add("fifty"    ,FIFTY    );
	m_pDictionary->Add("sixty"    ,SIXTY    );
	m_pDictionary->Add("seventy"  ,SEVENTY  );
	m_pDictionary->Add("eighty"   ,EIGHTY   );
	m_pDictionary->Add("ninety"   ,NINETY   );
	m_pDictionary->Add("hundred"  ,HUNDRED  );
	m_pDictionary->Add("thousand" ,THOUSAND );
	m_pDictionary->Add("million"  ,MILLION  );
	m_pDictionary->Add("billion"  ,BILLION  );
	m_pDictionary->Add("and"      ,AND      );
	m_pDictionary->Add(","        ,COMMA    );
}


void Num2Phrase::EraseDictionary()
{
	delete m_pDictionary;
}


// Dictionary Access (above) //
///////////////////////////////


///////////////////////////////////
// Translation Algorithm (below) //


Phrase Num2Phrase::Translate(Num cNum)
{
	if (cNum==0)
		return ReadDictionary(ZERO);

	Phrase cPhrase;

	int iComponent;    //Each component is a decimal number in the range 0-999.
	int iCompScope=1;  //Each component except for the last one is followed by a scope.
	int iDelimiter=-1; //Each component except for the first one is followed by a delimiter.

	int iCompCount=0;
	for (Num cTmp=cNum; cTmp>0; cTmp/=1000)
	{
		iComponent=cTmp%1000;
		if (iComponent>0)
		{
			//The following takes effect in the current iteration:
			//-The component, the scope and the delimiter are translated.
			//-The results are concatenated at the beginning of the phrase.
			Phrase cComponent=TranslateComponent(iComponent);
			Phrase cCompScope=TranslateCompScope(iCompScope);
			Phrase cDelimiter=TranslateDelimiter(iDelimiter);
			cPhrase=cComponent+cCompScope+cDelimiter+cPhrase;

			//The following will only take effect in the next iteration:
			//-The second component will be followed by an 'and' or a comma.
			//-Each of the remaining components will be followed by a comma.
			if (++iCompCount==1 && (iComponent<100 || iComponent%100==0))
				iDelimiter=AND;
			else
				iDelimiter=COMMA;
		}
		iCompScope*=1000;
	}

	return cPhrase;
}


Phrase Num2Phrase::TranslateComponent(int iComponent) const
{
	Phrase cPhrase;

	//Numbers 1-19 are comprised of exactly 1 token.
	if (1<=iComponent && iComponent<=19)
		cPhrase=ReadDictionary(iComponent);

	//Numbers 20-99 are comprised of 1 or 2 tokens.
	else if (20<=iComponent && iComponent<=99)
	{
		cPhrase=ReadDictionary(iComponent/10*10);
		cPhrase+=TranslateComponent(iComponent%10);
	}

	//Numbers 100-999 are comprised of 2, 4 or 5 tokens.
	else if (100<=iComponent && iComponent<=999)
	{
		cPhrase=ReadDictionary(iComponent/100);
		cPhrase+=ReadDictionary(HUNDRED);
		if (iComponent%100>0)
			cPhrase+=ReadDictionary(AND);
		cPhrase+=TranslateComponent(iComponent%100);
	}

	return cPhrase;
}


Phrase Num2Phrase::TranslateCompScope(int iCompScope) const
{
	Phrase cPhrase;

	//Each scope is comprised of 1 token at most.
	switch (iCompScope)
	{
	case 1:
		break;
	case 1000:
		cPhrase=ReadDictionary(THOUSAND);
		break;
	case 1000000:
		cPhrase=ReadDictionary(MILLION);
		break;
	case 1000000000:
		cPhrase=ReadDictionary(BILLION);
		break;
	}

	return cPhrase;
}


Phrase Num2Phrase::TranslateDelimiter(int iDelimiter) const
{
	Phrase cPhrase;

	//Each delimiter is comprised of exactly 1 token.
	switch (iDelimiter)
	{
	case AND:
		cPhrase=ReadDictionary(AND);
		break;
	case COMMA:
		cPhrase=ReadDictionary(COMMA);
		break;
	}

	return cPhrase;
}


// Translation Algorithm (above) //
///////////////////////////////////
