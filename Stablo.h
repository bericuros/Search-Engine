// Stablo.h: interface for the Stablo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STABLO_H__5F3D5977_5DFA_4D4C_B15E_3DD09CBA589F__INCLUDED_)
#define AFX_STABLO_H__5F3D5977_5DFA_4D4C_B15E_3DD09CBA589F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <IOSTREAM>
#include<vector>
using namespace std;

class Stablo {
public:
	virtual ~Stablo() { }

	virtual bool umetni(const char *kljuc) = 0;
	virtual bool obrisi(const char *kljuc) = 0;
	
	virtual void pronadji(const char *) = 0;

	virtual int dohvatiInfoFrekv(const char *kljuc) = 0;
	virtual char* dohvatiInfoNaziv(const char *kljuc) = 0;

	virtual int brojCvorova() { return m_brCvorova; }
	virtual int brojKljuceva() { return m_brKljuceva; }
	virtual int brojReci() { return m_brReci; }

	virtual void predvidi(const char *, char *[], vector<pair<const char *, int>> &) = 0;

	virtual void ispisiStatistiku(ostream &it) {
		it << "Ukupno cvorova: " << brojCvorova() << endl;
		it << "Ukupno kljuceva: " << brojKljuceva() << endl;
	}
protected:
	int m_brCvorova;
	int m_brKljuceva;
	int m_brReci;

	Stablo() {
		m_brKljuceva = 0;
		m_brCvorova = 0;
		m_brReci = 0;
	}
};

#endif // !defined(AFX_STABLO_H__5F3D5977_5DFA_4D4C_B15E_3DD09CBA589F__INCLUDED_)
