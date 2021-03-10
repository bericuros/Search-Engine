// TrieStablo.h: interface for the TrieStablo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_)
#define AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stablo.h"
#include<iostream>
#include<stack>

class TrieStablo : public Stablo {
public:
	TrieStablo();
	virtual ~TrieStablo();

	virtual bool umetni(const char *kljuc);
	virtual bool obrisi(const char *kljuc);

	virtual void pronadji(const char *);

	virtual int dohvatiInfoFrekv(const char *);
	virtual char *dohvatiInfoNaziv(const char *);


	virtual void predvidi(const char *, char *[], vector<pair<const char*, int>> &);
protected:
	class TrieCvor {
	public:
		TrieCvor(TrieCvor *roditelj);

		virtual ~TrieCvor();

		TrieCvor *roditelj() {
			return m_roditelj;
		}

		TrieCvor *pronadjiPodstablo(char deoKljuca);
		void dodajPodstablo(char deoKljuca, TrieCvor *cvor);
		void ukloniPodstablo(char deoKljuca);

		int brojPodstabala() const { return m_brojPodstabala; }

		int dohvatiInfoFrekv();
		void postaviInfoFrekv(int frekv);
		void uvecajInfoFrekv();

		char *dohvatiInfoNaziv();
		void postaviInfoNaziv(const char *);
	protected:
		TrieCvor *m_niz_pokazivaca[255];
		TrieCvor *m_roditelj;
		int m_info_frekv;
		char *m_info_naziv;
		int m_brojPodstabala;

		TrieCvor(const TrieCvor &) { }
		TrieCvor &operator=(const TrieCvor &) { }

	};

	TrieCvor *m_koren;

	TrieStablo(const TrieStablo &) { }
	TrieStablo &operator=(const TrieStablo &) { }

	TrieCvor *pronadjiCvor(const char *kljuc);   // pronalazi cvor koji sadrzi dati kljuc

};

#endif // !defined(AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_)
