#ifndef TRANSLATOR_H
#define TRANSLATOR_H


#include "Dictionary.h"


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CLASS NAME:  Translator                                              //
//                                                                      //
// DESCRIPTION: Translate something to something else.                  //
//                                                                      //
// REMARKS:     The translation algorithm is abstract and so it should  //
//              be implemented by any concrete sub-class of this class. //
//              During run-time, the algorithm may use a dictionary,    //
//              which depends on the type of translator implemented.    //
//              Hence, writing and erasing the dictionary should take   //
//              place at the construction and destruction of any        //
//              concrete sub-class of this class.                       //
//              Reading the dictionary is implemented in this class.    //
//              It is advisable to implement concrete sub-classes of    //
//              this class as Singletons, in order to maintain a single //
//              instance of the dictionary for each type of translator. //
//                                                                      //
// AUTHOR:      Barakman (barakman@yahoo.com)                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


template<typename INPUT,typename OUTPUT>
class Translator
{
public: //Constructor + Destructor
	Translator();
	virtual ~Translator();
	//------------------------------------
protected: //Dictionary Access
	virtual void WriteDictionary()=0;
	virtual void EraseDictionary()=0;
	OUTPUT ReadDictionary(int iKey) const;
	//------------------------------------
public: //Translation Algorithm
	virtual OUTPUT Translate(INPUT)=0;
	//------------------------------------
protected: //Object Attributes
	Dictionary<OUTPUT>* m_pDictionary;
	//------------------------------------
};


//////////////////////////////////////
// Constructor + Destructor (below) //


template<typename INPUT,typename OUTPUT>
Translator<INPUT,OUTPUT>::Translator()
{
}


template<typename INPUT,typename OUTPUT>
Translator<INPUT,OUTPUT>::~Translator()
{
}


// Constructor + Destructor (above) //
//////////////////////////////////////


///////////////////////////////
// Dictionary Access (below) //


template<typename INPUT,typename OUTPUT>
OUTPUT Translator<INPUT,OUTPUT>::ReadDictionary(int iKey) const
{
	OUTPUT tItem;
	m_pDictionary->Get(tItem,iKey);
	return tItem;
}


// Dictionary Access (above) //
///////////////////////////////


#endif
