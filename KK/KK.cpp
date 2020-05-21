

#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

struct AI {
	AI() {};
	AI(int Score) : score(Score) {};
	int x;
	int y;
	int score;
};

class Gra {
	int wymiar;
	char **tablica = new char *[wymiar]; //alokacja pamieci
	char tura;
	int rzad, kolumna;
	char gracz = 'o';
	char komp = 'x';
public:
	Gra(int rozmiar);
	AI Najlepszy(char player, int glebokosc);
	void Wyswietl();
	void Przebieg(char opcja);
	char Sprawdz();
};

AI Gra::Najlepszy(char player, int glebokosc) {

	if(glebokosc == 0){
		return AI(0);
	}

		char rv = Sprawdz();
		if (rv == komp) {
			return AI(10);
		}
		else if (rv == gracz) {
			return AI(-10);
		}
		else if (rv == 'n') {
			return AI(0);
		}

		vector<AI> moves;

		for (int y = 0; y < wymiar; y++) {
			for (int x = 0; x < wymiar; x++) {
				if (tablica[x][y] == 'n') {
					AI ruch;
					ruch.x = x;
					ruch.y = y;
					tablica[x][y] = player;
					if (player == komp) {
						ruch.score = Najlepszy(gracz, glebokosc-1).score;
					}
					else {
						ruch.score = Najlepszy(komp, glebokosc-1).score;
					}
					moves.push_back(ruch);
					tablica[x][y] = 'n';
				}
			}
		}
		int bestMove = 0;
		if (player == komp) {
			int bestScore = -10000;
			for (int i = 0; i < moves.size(); i++) {
				if (moves[i].score > bestScore) {
					bestMove = i;
					bestScore = moves[i].score;
				}
			}
		}
		else {
			int bestScore = 10000;
			for (int i = 0; i < moves.size(); i++) {
				if (moves[i].score < bestScore) {
					bestMove = i;
					bestScore = moves[i].score;
				}
			}
		}
		return moves[bestMove];
	
}

Gra::Gra(int rozmiar) {
	wymiar = rozmiar;
	for (int i = 0; i < wymiar; ++i)
	{
		tablica[i] = new char[wymiar]; //alokacja pamieci
		for (int j = 0; j < wymiar; ++j) //wpisanie wartosci do tablicy
			tablica[i][j] = 'n';
	}
}

void Gra::Wyswietl() {
	for (int i = 0; i < wymiar; i++) {
		cout << endl;
		for (int j = 0; j < wymiar; j++) {
			cout << tablica[i][j];
		}
	}
	cout << endl;
}

char Gra::Sprawdz() {
	int licz = 0;
	
	//W poziomie
	for (int i = 0; i < wymiar; i++) {
		int liczx = 0, liczo = 0;
		for (int j = 0; j < wymiar -1 ; j++) {
			if (tablica[i][j] == tablica[i][j + 1] && tablica[i][j] == 'x') liczx++;
			else if (tablica[i][j] == tablica[i][j + 1] && tablica[i][j] == 'o') liczo++;

			if (liczx == wymiar - 1) return 'x';
			else if (liczo == wymiar - 1) return 'o';
		}
		//cout << "koniec";
}

	// W pionie
	for (int j = 0; j < wymiar; j++) {
		int liczx = 0, liczo = 0;
		for (int i = 0; i < wymiar - 1; i++) {
			if (tablica[i][j] == tablica[i+1][j] && tablica[i][j] == 'x') liczx++;
			else if (tablica[i][j] == tablica[i + 1][j] && tablica[i][j] == 'o') liczo++;

			if (liczx == wymiar - 1) return 'x';
			else if (liczo == wymiar - 1) return 'o';
		}
	}
	
	//Przekatna
	int liczx = 0, liczo = 0;
	for (int i = 0; i < wymiar-1; i++) {
		for (int j = 0; j < wymiar-1; j++) {
			if (tablica[i][j] == tablica[i + 1][j + 1] && tablica[i][j] == 'x') liczx++;
			else if (tablica[i][j] == tablica[i + 1][j + 1] && tablica[i][j] == 'o') liczo++;
		}
	}
	if (liczx == wymiar - 1) return 'x';
	else if (liczo == wymiar - 1) return 'o';
	liczx = 0, liczo = 0;
	//Przekatna 2
	
	for (int i = wymiar -1 ; i > 0; i--) {
		for (int j = 0; j < wymiar - 1; j++) {
			if (tablica[i][j] == tablica[i - 1][j + 1] && tablica[i][j] == 'x') liczx++;
			else if (tablica[i][j] == tablica[i - 1][j + 1] && tablica[i][j] == 'o') liczo++;
		}
	}
	if (liczx == wymiar - 1) return 'x';
	else if (liczo == wymiar - 1) return 'o';
	
	//Remis
	for (int i = 0; i < wymiar; i++) {
		for (int j = 0; j < wymiar; j++) {
			if (tablica[i][j] != 'n') licz++;

		}
	}
	if (licz == (wymiar*wymiar)) return 'n';

}


void Gra::Przebieg(char opcja) {
	tura = 'o';
	char wygrana = 'z';
	Wyswietl();
	while (wygrana == 'z') {
		
		cout << endl << "Kolej gracza z kolkiem, podaj rzad potem kolumne" << endl;
		do {
			cin >> rzad >> kolumna;
			if (tablica[rzad - 1][kolumna - 1] != 'n') {
				cout << "To pole jest juz zajete lub wykracza poza zakres planszy" << endl;
			}
			else
				tablica[rzad - 1][kolumna - 1] = 'o';
			wygrana = Sprawdz();
			Wyswietl();

		} while (tablica[rzad - 1][kolumna - 1] != 'o');
		
		
		// SZTUCZNA INTELIGENCJA
		if (opcja == 'k') {
			AI best = Najlepszy(komp, 6);
			tablica[best.x][best.y] = komp;
			wygrana = Sprawdz();
			cout << "Ruch komputera:" << endl;
			Wyswietl();
		}
		
		
		// DRUGI GRACZ

		else if (opcja == 'm') {
			cout << "Kolej gracza z krzyzykiem, podaj rzad potem kolumne" << endl;
			do {
				cin >> rzad >> kolumna;
				if (tablica[rzad - 1][kolumna - 1] != 'n') {
					cout << "To pole jest juz zajete lub wykracza poza zakres planszy" << endl;
				}
				else
					tablica[rzad - 1][kolumna - 1] = 'x';
				Wyswietl();
				wygrana = Sprawdz();
			} while (tablica[rzad - 1][kolumna - 1] != 'x');
		}

		// Sprawdzenie kto wygral

			if (wygrana == 'o') {
				cout << "Wygral gracz z kolkiem" << endl;
			}
			else if (wygrana == 'x' && opcja == 'k') {
				cout << "Wygral komputer" << endl;
			}
			else if (wygrana == 'x' && opcja == 'm') {
				cout << "Wygral gracz z krzyzykiem" << endl;
			}
			else wygrana = 'z';
	}
}
int main()
{
	char opcja;
	int wielkosc;
	cout << "Wybierz wielkosc planszy" << endl;
	cin >> wielkosc;
	Gra test(wielkosc);
	do {
		cout << "MULTIPLAYER - wybierz m" << endl << "Z komputerem - wybierz k" << endl;
		cin >> opcja;
		if (opcja != 'm' && opcja != 'k') cout << "Zla opcja!!! Sprobuj jeszcze raz" << endl;
	} while (opcja != 'm' && opcja != 'k');
	test.Przebieg(opcja);
}

