#ifndef _RECNIK_
#define _RECNIK_

#include"TrieStablo.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Recnik {
public:
	Recnik();
	virtual ~Recnik();

	int brojKljuceva() const;
	int brojReci() const;
	bool umetni(const char *);
	bool obrisi(const char *);
	void predvidi(const char *, char *[], vector<pair<const char *, int>> &);

	void pronadji(const char *);
protected:
private:
	Stablo *tree;
};

#endif // _RECNIK_