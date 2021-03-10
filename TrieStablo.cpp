// TrieStablo.cpp: implementation of the TrieStablo class.
//
//////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include "TrieStablo.h"
#include<stack>
#include<vector>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TrieStablo::TrieCvor::TrieCvor(TrieStablo::TrieCvor *roditelj) : m_roditelj(roditelj), m_info_frekv(0), m_brojPodstabala(0) {
	for (int i = 0; i < 255; i++) {
		m_niz_pokazivaca[i] = 0;
	}
}

TrieStablo::TrieCvor::~TrieCvor() {

	m_info_frekv = 0;
	if (m_info_naziv) {
		delete m_info_naziv;
	}
	for (int i = 0; i < 255; i++) {
		if (m_niz_pokazivaca[i]) {
			delete m_niz_pokazivaca[i];
			m_niz_pokazivaca[i] = nullptr;
		}
	}
}

TrieStablo::TrieCvor *TrieStablo::TrieCvor::pronadjiPodstablo(char deoKljuca) {
	return m_niz_pokazivaca[deoKljuca];
}

void TrieStablo::TrieCvor::dodajPodstablo(char deoKljuca, TrieStablo::TrieCvor *cvor) {
	if (!m_niz_pokazivaca[deoKljuca]) {
		m_niz_pokazivaca[deoKljuca] = cvor;
		m_brojPodstabala++;
	}
}

void TrieStablo::TrieCvor::ukloniPodstablo(char deoKljuca) {
	if (m_niz_pokazivaca[deoKljuca]) {
		m_niz_pokazivaca[deoKljuca] = 0;
		m_brojPodstabala--;
	}
}

void TrieStablo::TrieCvor::uvecajInfoFrekv() {
	m_info_frekv++;
}

char * TrieStablo::TrieCvor::dohvatiInfoNaziv() {
	return m_info_naziv;
}

void TrieStablo::TrieCvor::postaviInfoNaziv(const char *podaci) {
	if (!m_info_naziv) {
		m_info_naziv = new char[strlen(podaci) + 1];
		strcpy(m_info_naziv, podaci);
	}
}

int TrieStablo::TrieCvor::dohvatiInfoFrekv() {
	return m_info_frekv;
}

void TrieStablo::TrieCvor::postaviInfoFrekv(int frekv) {
	m_info_frekv = frekv;
}

//---------------------------------------------------------------


TrieStablo::TrieCvor *TrieStablo::pronadjiCvor(const char *kljuc) {
	if (!m_koren) {
		return 0;
	}

	TrieCvor *tek = m_koren;

	for (int i = 0; i < strlen(kljuc) && tek; i++) {
		char c = kljuc[i];
		if (kljuc[i] >= 65 && kljuc[i] <= 90) {
			c = kljuc[i] + 32;
		}
		tek = tek->pronadjiPodstablo(c);
	}

	return tek;
}

TrieStablo::TrieStablo() : m_koren(0) {}

TrieStablo::~TrieStablo() {
	if (m_koren) {
		delete m_koren;
		m_koren = nullptr;
	}
}

bool TrieStablo::umetni(const char *kljuc) {
	if (!m_koren) {
		m_koren = new TrieCvor(0);
		m_brCvorova++;
	}

	TrieCvor *tek = m_koren;
	TrieCvor *sledeci = 0;
	string podaci = "";

	if (strlen(kljuc) == 0) return false;

	for (int i = 0; i < strlen(kljuc); i++) {

		char c = kljuc[i];
		if (kljuc[i] >= 65 && kljuc[i] <= 90) {
			c = kljuc[i] + 32;
		}
		podaci += c;

		sledeci = tek->pronadjiPodstablo(c);

		if (!sledeci) {
			sledeci = new TrieCvor(tek);
			tek->dodajPodstablo(c, sledeci);
			m_brCvorova++;
		}

		tek = sledeci;
	}

	//bool rezultat = true;  // ako je kljuc prvi put umetnut, onda true
	m_brKljuceva++;
	//sledeci->postaviInfo(podaci);      
	if (sledeci->dohvatiInfoFrekv() == 0) {
		m_brReci++;
	}
	sledeci->uvecajInfoFrekv();
	sledeci->postaviInfoNaziv(podaci.c_str());
	return true;
}

bool TrieStablo::obrisi(const char *kljuc) {
	if (!m_koren) {
		return false;
	}

	TrieCvor *tek = pronadjiCvor(kljuc);
	if (!tek) {
		return false;
	}

	m_brKljuceva -= tek->dohvatiInfoFrekv();
	tek->postaviInfoFrekv(0);
	int i = strlen(kljuc) - 1;

	while (i >= 0 && tek && tek->brojPodstabala() == 0 && !tek->dohvatiInfoNaziv()) {
		TrieCvor *roditelj = tek->roditelj();

		delete tek;
		m_brCvorova--;

		if (roditelj) {
			char c = kljuc[i];
			if (kljuc[i] >= 65 && kljuc[i] <= 90) {
				c = kljuc[i] + 32;
			}
			roditelj->ukloniPodstablo(c);
			i--;
		}
		else {
			m_koren = 0;
		}
		tek = roditelj;
	}

	m_brReci--;
	return true;
}

void TrieStablo::pronadji(const char *kljuc) {
	TrieCvor *node = pronadjiCvor(kljuc);

	if (node && node->dohvatiInfoNaziv()) {
		cout << "Rec \"" << kljuc << "\" postoji u recniku.\n";
		cout << "Njena frekvencija je " << node->dohvatiInfoFrekv() * 100.0 / m_brKljuceva << " %.\n";
	}
	else {
		cout << "Rec \"" << kljuc << "\" ne postoji u recniku.\n";
	}
}

int TrieStablo::dohvatiInfoFrekv(const char *kljuc) {
	TrieCvor *cvor = pronadjiCvor(kljuc);

	if (cvor) {
		return cvor->dohvatiInfoFrekv();
	}
	return 0;
}

char * TrieStablo::dohvatiInfoNaziv(const char *kljuc) {
	TrieCvor *cvor = pronadjiCvor(kljuc);

	if (cvor) {
		return cvor->dohvatiInfoNaziv();
	}
	return 0;
}

void TrieStablo::predvidi(const char *kljuc, char *susedi[], vector<pair<const char*, int>> &words) {

	if (!m_koren) return;

	stack<TrieCvor *> sttc;
	stack<int> strb, stnum;

	sttc.push(m_koren);
	strb.push(0);
	stnum.push(0);

	TrieCvor *tc;
	int rb, num, size = strlen(kljuc);
	char c;
	
	while (!sttc.empty()) {
		tc = sttc.top(), sttc.pop();
		rb = strb.top(), strb.pop();
		num = stnum.top(), stnum.pop();
		
		TrieCvor *temp = nullptr;
		if (rb < size) {  // ako moze jos slova da se dodaje
			c = kljuc[rb];
			if (num < 3) { // ako moze jos neko slovo biti pogresno napisano
				for (int i = 0; i < strlen(susedi[c]); i++) {
					temp = tc->pronadjiPodstablo(susedi[c][i]);
					if (temp) {
						sttc.push(temp);
						strb.push(rb + 1);
						stnum.push(num + 1);
					}
				}
			}
			temp = tc->pronadjiPodstablo(c);
			if (temp) {
				sttc.push(temp);
				strb.push(rb + 1);
				stnum.push(num);
			}
		}
		else { // ove reci dolaze u obzir
			for (int i = 97; i < 122; i++) {
				temp = tc->pronadjiPodstablo(i);
				if (temp) {
					sttc.push(temp);
					strb.push(size);
					stnum.push(0);
				}
			}

			if (tc->dohvatiInfoNaziv()) {
				words.push_back({ tc->dohvatiInfoNaziv(), tc->dohvatiInfoFrekv() });
			}
		}

		

	}

}
