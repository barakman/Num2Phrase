#ifndef DICTIONARY_H
#define DICTIONARY_H


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CLASS NAME:  Dictionary                                              //
//                                                                      //
// DESCRIPTION: Store a predefined number of elements.                  //
//              Allow access operations (read / write).                 //
//              Time complexity - O(1). Space complexity - O(n).        //
//                                                                      //
// REMARKS:     This class operates as a direct hash-table, and         //
//              therefore works fast but consumes a lot of memory.      //
//              It is ideal for data base with a dense range of keys.   //
//                                                                      //
// AUTHOR:      Barakman (barakman@yahoo.com)                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


template<typename TYPE>
class Dictionary
{
public: //Constructor + Destructor
	Dictionary(int iSize);
	virtual ~Dictionary();
	//-------------------------------------------
public: //Interface Functions
	virtual bool Add(const TYPE& tItem,int iKey);
	virtual bool Get(TYPE& tItem,int iKey) const;
	//-------------------------------------------
private: //Object Attributes
	int    m_iSize;
	TYPE** m_aDataBase;
	//-------------------------------------------
};


//////////////////////////////////////
// Constructor + Destructor (below) //


template<typename TYPE>
Dictionary<TYPE>::Dictionary(int iSize)
{
	m_iSize=iSize;
	m_aDataBase=new TYPE*[m_iSize];
	for (int i=0; i<m_iSize; i++)
		m_aDataBase[i]=0;
}


template<typename TYPE>
Dictionary<TYPE>::~Dictionary()
{
	for (int i=0; i<m_iSize; i++)
		if (m_aDataBase[i]!=0)
			delete m_aDataBase[i];
	delete[] m_aDataBase;
}


// Constructor + Destructor (above) //
//////////////////////////////////////


/////////////////////////////////
// Interface Functions (below) //


template<typename TYPE>
bool Dictionary<TYPE>::Add(const TYPE& tItem,int iKey)
{
	if (0<=iKey && iKey<=m_iSize-1 && m_aDataBase[iKey]==0)
	{
		m_aDataBase[iKey]=new TYPE(tItem);
		return true;
	}
	return false;
}


template<typename TYPE>
bool Dictionary<TYPE>::Get(TYPE& tItem,int iKey) const
{
	if (0<=iKey && iKey<=m_iSize-1 && m_aDataBase[iKey]!=0)
	{
		tItem=*m_aDataBase[iKey];
		return true;
	}
	return false;
}


// Interface Functions (above) //
/////////////////////////////////


#endif
