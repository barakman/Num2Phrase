#include "Phrase.h"
#include <string.h>


int Phrase::m_iTotalMemoryUsage=0;


///////////////////////////////////////
// Constructors + Destructor (below) //


Phrase::Phrase(const char* aPhrase)
{
	Create(aPhrase);
}


Phrase::Phrase(const Phrase& cPhrase)
{
	Create(cPhrase.m_aPhrase);
}


Phrase::~Phrase()
{
	Destroy();
}


// Constructors + Destructor (above) //
///////////////////////////////////////


/////////////////////////////////
// Interface Operators (below) //


Phrase::operator const char*() const
{
	return m_aPhrase;
}


const Phrase& Phrase::operator=(const Phrase& cPhrase)
{
	if (this!=&cPhrase)
	{
		Destroy();
		Create(cPhrase.m_aPhrase);
	}
	return *this;
}


const Phrase& Phrase::operator+=(const Phrase& cPhrase)
{
	if (cPhrase.IsNotEmpty())
	{
		char* aPhrase;
		if (this->IsNotEmpty())
		{
			aPhrase=new char[m_iLength+cPhrase.m_iLength];
			strcpy(aPhrase,m_aPhrase);
			strcat(aPhrase," ");
			strcat(aPhrase,cPhrase.m_aPhrase);
		}
		else
		{
			aPhrase=new char[cPhrase.m_iLength];
			strcpy(aPhrase,cPhrase.m_aPhrase);
		}
		Destroy();
		Create(aPhrase);
		delete[] aPhrase;
	}
	return *this;
}


Phrase operator+(const Phrase& cPhrase1,const Phrase& cPhrase2)
{
	Phrase cPhrase=cPhrase1;
	cPhrase+=cPhrase2;
	return cPhrase;
}


// Interface Operators (above) //
/////////////////////////////////


/////////////////////////////////
// Interface Functions (below) //


bool Phrase::IsNotEmpty() const
{
	return m_iLength>0? true:false;
}


int Phrase::GetTotalMemoryUsage()
{
	return m_iTotalMemoryUsage;
}


// Interface Functions (above) //
/////////////////////////////////


////////////////////////////////
// Internal Functions (below) //


void Phrase::Create(const char* aPhrase)
{
	if (aPhrase!=0)
	{
		m_iLength=strlen(aPhrase)+1;
		m_aPhrase=new char[m_iLength];
		strcpy(m_aPhrase,aPhrase);
		m_iTotalMemoryUsage+=m_iLength;
	}
	else
	{
		m_iLength=0;
		m_aPhrase=0;
	}
}


void Phrase::Destroy()
{
	if (m_aPhrase!=0)
	{
		m_iTotalMemoryUsage-=m_iLength;
		delete[] m_aPhrase;
		m_iLength=0;
		m_aPhrase=0;
	}
}


// Internal Functions (above) //
////////////////////////////////
