#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<filesystem>
#include<ctime>
using namespace std;

#include"TrieStablo.h"
#include"Recnik.h"

bool cmp(pair<const char *, int> a, pair<const char *, int> b) {
	return a.second > b.second ||
		a.second == b.second && strlen(a.first) < strlen(b.first) ||
		a.second == b.second && strlen(a.first) == strlen(b.first) && strcmp(a.first, b.first) < 0;
}

void clear() {
	system("cls");
}

void postaviSusede(char *susedi[]) {
	for (int i = 0; i < 255; i++) {
		susedi[i] = nullptr;
	}
	const char *keyboard[3] = { "qwertyuiop", "asdfghjkl", "zxcvbnm" };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < strlen(keyboard[i]); j++) {
			if (keyboard[i][j] == 'q') {
				susedi[keyboard[i][j]] = new char[3];
				susedi[keyboard[i][j]][0] = 'a';
				susedi[keyboard[i][j]][1] = 'w';
				susedi[keyboard[i][j]][2] = '\0';
			}
			else if (keyboard[i][j] == 'p') {
				susedi[keyboard[i][j]] = new char[3];
				susedi[keyboard[i][j]][0] = 'o';
				susedi[keyboard[i][j]][1] = 'l';
				susedi[keyboard[i][j]][2] = '\0';
			}
			else if (i == 0) {
				susedi[keyboard[i][j]] = new char[5];
				susedi[keyboard[i][j]][0] = keyboard[i][j - 1];
				susedi[keyboard[i][j]][1] = keyboard[i + 1][j - 1];
				susedi[keyboard[i][j]][2] = keyboard[i + 1][j];
				susedi[keyboard[i][j]][3] = keyboard[i][j + 1];
				susedi[keyboard[i][j]][4] = '\0';
			}
			else if (keyboard[i][j] == 'a') {
				susedi[keyboard[i][j]] = new char[4];
				susedi[keyboard[i][j]][0] = 'q';
				susedi[keyboard[i][j]][1] = 's';
				susedi[keyboard[i][j]][2] = 'w';
				susedi[keyboard[i][j]][3] = '\0';
			}
			else if (keyboard[i][j] == 'l') {
				susedi[keyboard[i][j]] = new char[4];
				susedi[keyboard[i][j]][0] = 'o';
				susedi[keyboard[i][j]][1] = 'k';
				susedi[keyboard[i][j]][2] = 'p';
				susedi[keyboard[i][j]][3] = '\0';
			}
			else if (i == 1) {
				susedi[keyboard[i][j]] = new char[6];
				susedi[keyboard[i][j]][0] = keyboard[i - 1][j];
				susedi[keyboard[i][j]][1] = keyboard[i][j - 1];
				susedi[keyboard[i][j]][2] = keyboard[i + 1][j - 1];
				susedi[keyboard[i][j]][3] = keyboard[i][j + 1];
				susedi[keyboard[i][j]][4] = keyboard[i - 1][j + 1];
				susedi[keyboard[i][j]][5] = '\0';
			}
			else if (keyboard[i][j] == 'z') {
				susedi[keyboard[i][j]] = new char[3];
				susedi[keyboard[i][j]][0] = 's';
				susedi[keyboard[i][j]][1] = 'x';
				susedi[keyboard[i][j]][2] = '\0';
			}
			else if (keyboard[i][j] == 'm') {
				susedi[keyboard[i][j]] = new char[3];
				susedi[keyboard[i][j]][0] = 'k';
				susedi[keyboard[i][j]][1] = 'n';
				susedi[keyboard[i][j]][2] = '\0';
			}
			else {
				susedi[keyboard[i][j]] = new char[4];
				susedi[keyboard[i][j]][0] = keyboard[i - 1][j + 1];
				susedi[keyboard[i][j]][1] = keyboard[i][j - 1];
				susedi[keyboard[i][j]][2] = keyboard[i][j + 1];
				susedi[keyboard[i][j]][3] = '\0';
			}
		}
	}
}

int MainMenu(Recnik *&dict) {
	
	cout << "\nUnesite redni broj stavke koju zelite da izvrsite:\n";
	cout << "1. Stvaranje recnika pomocu prilozenog skupa datoteka.\n";
	cout << "2. Stvaranje recnika\n";
	cout << "3. Umetanje reci\n";
	cout << "4. Broj reci.\n";
	cout << "5. Pronalazenje reci\n";
	cout << "6. Predvidjanje reci\n";
	cout << "7. Brisanje recnika\n";
	cout << "8. Izlaz\n\n";

	int item;
	cin >> item;

	if (item < 1 || item > 8) {
		item = 11;
	}
	else if (!dict && item != 1 && item != 2 && item != 3 && item != 8) {
		item = 9;
	}
	else if (dict && (item == 1 || item == 2)) {
		item = 10;
	}

	return item;
}

void CreateDict(Recnik *&dict) {

	clear();

	dict = new Recnik;

	int n;
	cout << "Unesite broj tekstualnih datoteka sa recima: ";
	cin >> n;
	
	while (n--) {
		string name;
		cout << "Unesite puno ime datoteke: ";
		cin >> name;

		ifstream file;
		file.open(name.c_str());
		if (!file) {
			clear();
			cout << "Datoteka sa datim imenom ne postoji.\n";
			break;
		}

		while (file.peek() != EOF) {
			string word;
			file >> word;
			bool valid = true;
			for (int i = 0; i < word.size(); i++) {
				if (word[i] < 65 || word[i] > 90 && word[i] < 97 || word[i] > 122) {
					valid = false;
					break;
				}
			}
			if (valid) {
				dict->umetni(word.c_str());
			}
		}

		file.close();
	}

}

void TextFileCreateDict(Recnik *&dict) {
	//const clock_t beginTime = clock();
	
	clear();

	dict = new Recnik;

	int num = 0, cnt = 0;
	string filePath = "C:\\Users\\pc\\Desktop\\asp2lab3texts";
	for (const auto &it : filesystem::directory_iterator(filePath)) {
		num++;
	}
	for (const auto &it : filesystem::directory_iterator(filePath)) {
		ifstream file;
		file.open(it.path());
		if (!file) break;
		
		cnt++;
		if (cnt % (num / 20) == 0 || cnt == num || cnt % (num / 30) == 0 && cnt < num / 20) {
			clear();
			cout << "Ucitano: " << cnt * 100 / num << "%\n";
		}

		while (file.peek() != EOF) {
			string word;
			file >> word;
			bool valid = true;
			for (int i = 0; i < word.size(); i++) {
				if (word[i] < 65 || word[i] > 90 && word[i] < 97 || word[i] > 122) {
					valid = false;
					break;
				}
			}
			if (valid) {
				dict->umetni(word.c_str());
			}
		}
		
		file.close();
	}

	//cout << "time:" << (double)(clock() - beginTime) / CLOCKS_PER_SEC << endl;
	cout << "Recnik je uspesno kreiran.\n";
}

void NumberKeys(Recnik *&dict) {
	clear();
	cout << "Broj reci u recniku je: " << dict->brojReci() << "\n";
	cout << "Ukupan broj reci (s ponavljanjem) je: " << dict->brojKljuceva() << "\n";
}

void FindWord(Recnik *&dict) {

	clear();
	cout << "Unesite rec koju zelite da pretrazite: ";
	string word;
	cin >> word;

	dict->pronadji(word.c_str());

}

void InsertWord(Recnik *&dict) {
	
	clear();

	if (!dict) dict = new Recnik;

	cout << "Unesite rec: ";
	string word;
	cin >> word;

	dict->umetni(word.c_str());
	cout << "Rec je uspesno uneta, odnosno njena ucestalost je povecana.\n";

}

void Predict(Recnik *&dict, char *susedi[]) {

	clear();
	cout << "Pretrazujete rec: ";
	string word;
	cin >> word;

	vector<pair<const char *, int>> words;
	dict->predvidi(word.c_str(), susedi, words);
	sort(words.begin(), words.end(), cmp);

	bool exists = false;
	int frekv = 0;
	for (int i = 0; i < words.size(); i++) {
		if (words[i].first == word) {
			exists = true;
			cout << "Uneta rec postoji u recniku: " << words[i].first << "   ( frekv = " << words[i].second * 100.0 / dict->brojKljuceva() << " % )\n";
			cout << "[ Sledi prikaz (do) tri najucestalije reci slicne unetoj:\n";
		}
	}

	if (words.size() and !exists) {
		cout << "Da niste mozda mislili:\n";
	}
	else if (!words.size()) {
		cout << "Ne postoji nijedna slicna rec u recniku.\n";
	}

	for (int i = 0; i < 3 && i < words.size(); i++) {
		if (exists) {
			cout << "  ";
		}
		cout << words[i].first << "   ( frekv = " << words[i].second * 100.0 / dict->brojKljuceva() << " % )\n";
	}
	if (exists) {
		cout << "  (Uneta rec moze ujedno biti i medju tri najucestalije) ]\n";
	}

}

void DeleteDict(Recnik *&dict) {
	clear();

	if (dict) {
		delete dict;
		dict = nullptr;
		cout << "Recnik je uspesno obrisan.\n";
	}
}

int main() {

	char *susedi[255];
	postaviSusede(susedi);
	Recnik *dict = nullptr;

	cout << "Dobrodosli!\n";
	while (true) {
		int item = MainMenu(dict);
		if (item == 1) TextFileCreateDict(dict);
		else if (item == 2) CreateDict(dict);
		else if (item == 3) InsertWord(dict);
		else if (item == 4) NumberKeys(dict);
		else if (item == 5) FindWord(dict);
		else if (item == 6) Predict(dict, susedi);
		else if (item == 7) DeleteDict(dict);
		else if (item == 8) {
			DeleteDict(dict);
			break;
		}
		else if (item == 9) {
			clear();
			cout << "Recnik ne postoji. Pokusajte odabirom jedne od prve tri stavke.\n";
		}
		else if (item == 10) {
			clear();
			cout << "Recnik treba prvo da se izbrise odabirom stavke 7 kako bi se napravio novi.\n";
		}
		else {
			clear();
			cout << "Uneli ste nevazecu vrednost.\n";
		}
	}
	cout << "\nDovidjenja!\n";

	return 0;

}