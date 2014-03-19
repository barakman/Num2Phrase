#ifndef NUM_2_PHRASE_H
#define NUM_2_PHRASE_H


#include "Num.h"
#include "Phrase.h"
#include "Translator.h"


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CLASS NAME:  Num2Phrase                                              //
//                                                                      //
// DESCRIPTION: Translate a numeric value to words.                     //
//                                                                      //
// REMARKS:     This class derives from Class Translator<Num,Phrase>.   //
//              It implements a Number-To-Words translation algorithm.  //
//              The algorithm is limited to unsigned 32-bit integers,   //
//              but includes infrastructure for extended ranges.        //
//              It provides an interface for translating numbers in the //
//              specified range (0 to 2^32-1).                          //
//              The provided interface can be easily extended for a     //
//              wider range of numbers.                                 //
//                                                                      //
// AUTHOR:      Barakman (barakman@yahoo.com)                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


class Num2Phrase : public Translator<Num,Phrase>
{
public: //Singleton Interface
	static Num2Phrase* CreateTranslator();
	static void DestroyTranslator();
	//----------------------------------------------
protected: //Constructor + Destructor
	Num2Phrase();
	virtual ~Num2Phrase();
	//----------------------------------------------
protected: //Dictionary Access
	virtual void WriteDictionary();
	virtual void EraseDictionary();
	//----------------------------------------------
public: //Translation Algorithm
	virtual Phrase Translate(Num cNum);
	//----------------------------------------------
protected: //Translation Algorithm
	Phrase TranslateComponent(int iComponent) const;
	Phrase TranslateCompScope(int iCompScope) const;
	Phrase TranslateDelimiter(int iDelimiter) const;
	//----------------------------------------------
private: //Class Attributes
	static Num2Phrase* m_pNum2Phrase;
	//----------------------------------------------
};


#endif
