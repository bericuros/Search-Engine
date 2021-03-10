#include "Recnik.h"

Recnik::Recnik() : tree(new TrieStablo) {}

Recnik::~Recnik() {
	if (tree) {
		delete tree;
		tree = nullptr;
	}
}

int Recnik::brojKljuceva() const {
	return tree->brojKljuceva();
}

int Recnik::brojReci() const {
	return tree->brojReci();
}

bool Recnik::umetni(const char *kljuc) {
	return tree->umetni(kljuc);
}

bool Recnik::obrisi(const char *kljuc) {
	return tree->obrisi(kljuc);
}

void Recnik::predvidi(const char *kljuc, char *susedi[], vector<pair<const char *, int>> &words) {
	tree->predvidi(kljuc, susedi, words);
}

void Recnik::pronadji(const char *kljuc) {
	tree->pronadji(kljuc);
}
