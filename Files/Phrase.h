#ifndef PHRASE_H
#define PHRASE_H


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CLASS NAME:  Phrase                                                  //
//                                                                      //
// DESCRIPTION: Store a null terminated string of characters.           //
//              Allow basic operations (assign, concatenate, etc.).     //
//                                                                      //
// REMARKS:     The '+' operation concatenates two strings,             //
//              separated by a space character, into one string.        //
//              The function 'GetTotalMemoryUsage' returns the total    //
//              amount of memory that is allocated by existing objects. //
//                                                                      //
// AUTHOR:      Barakman (barakman@yahoo.com)                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


class Phrase
{
public: //Constructors + Destructor
	Phrase(const char* aPhrase=0);
	Phrase(const Phrase& cPhrase);
	virtual ~Phrase();
	//---------------------------------------------------------------------
public: //Interface Operators
	virtual operator const char*() const;
	const Phrase& operator=(const Phrase& cPhrase);
	const Phrase& operator+=(const Phrase& cPhrase);
	friend Phrase operator+(const Phrase& cPhrase1,const Phrase& cPhrase2);
	//---------------------------------------------------------------------
public: //Interface Functions
	virtual bool IsNotEmpty() const;
	static int GetTotalMemoryUsage();
	//---------------------------------------------------------------------
private: //Internal Functions
	void Create(const char* aPhrase);
	void Destroy();
	//---------------------------------------------------------------------
private: //Object Attributes
	int   m_iLength;
	char* m_aPhrase;
	//---------------------------------------------------------------------
private: //Class Attributes
	static int m_iTotalMemoryUsage;
	//---------------------------------------------------------------------
};


#endif
