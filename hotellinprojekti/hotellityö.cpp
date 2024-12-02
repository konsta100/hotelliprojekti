//Konsta Hautanen 2-3p
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;

bool huonevarattu(const vector<bool>& huoneet, int huonenumero) {//tarkistaa huoneen varaus tilanteen
	return huoneet[huonenumero - 1];
}
int satunnainenvarausnumero() {
	return rand() % 90000 + 10000;//valitsee satunnaisen varausnumeron 10000-99999 v�lilt�
}
void varauksenteko(vector<bool>& huoneet, vector<string>& varausnimet, vector<int>&varausnumerot, int yhdenhuoneenhinta, int kahdenhuoneenhinta) {
	string varaaja;
	setlocale(LC_ALL, "fi-FI");
	int henkilomaara, yomaara, huonenumero;
	cout << "Varaajan nimi: ";
	cin.ignore();//poistaa edellisen sy�tteen jotta getline lukee nimen oikein
	getline(cin, varaaja);
	cout << "Yhden(1) vai kahden(2) hengen huone?: ";
	while (!(cin >> henkilomaara) || (henkilomaara != 1 && henkilomaara != 2)) {
		cout << "Anna joko 1 tai 2 ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	do {
		cout << "Valitse huonenumero 1-" << huoneet.size() << "): "; //kysyt�� haluttu huonenumero ja tarkistetaan onko vapaana
		while (!(cin >> huonenumero)) {
			cout << "Anna huonenumero v�lilt� 1-" << huoneet.size() << ": ";
			cin.clear();
			cin.ignore(numeric_limits < streamsize>::max(), '\n');
		}if (huonenumero<1 || huonenumero>huoneet.size()) {
			cout << "Huonetta ei ole. Valitse jokin muu huone.\n";
		}
		else if (huonevarattu(huoneet, huonenumero)) {
			cout << "Huone " << huonenumero << " on jo varattu.\n";
		}
	} while (huonenumero<1 || huonenumero>huoneet.size() || huonevarattu(huoneet, huonenumero));
	cout << "Kuinka monta y�t� olet viett�m�ss�? ";
	while (!(cin >> yomaara) || yomaara <= 0) {
		cout << "Anna positiivinen luku ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	int hinta = (henkilomaara == 1 ? yhdenhuoneenhinta : kahdenhuoneenhinta) * yomaara; //laskeataan hinta
	int varausnumero = satunnainenvarausnumero();//arvotaan varausnumero
	varausnumerot.push_back(varausnumero);//p�ivitet��n varauksen nimi ja varausnumero
	varausnimet.push_back(varaaja);
	huoneet[huonenumero - 1] = true; //Huone varattu
	cout << "Huone " << huonenumero << " varattu.\n";//varauksen onnistuminen
	cout << "Hinta on: " << hinta << " euroa.\n";
	cout << "Varausnumero " << varausnumero << "\n";
}
void varaushaku(const vector<string>& varausnimet, const vector<int>& varausnumerot) { //Hakee varauksen nimen tai varausnumeron perusteella
	if (varausnimet.empty()) {
		cout << "Ei varauksia.\n";
		return;
	}
	int haku;
	cout << "Haetko varausta nimell� valitse (1) vai varausnumerolla valitse (2) ";
	while (!(cin >> haku) || (haku != 1 && haku != 2)) {
		cout << "Virhe paina 1 tai 2 ";
		cin.clear();
		cin.ignore(numeric_limits < streamsize>::max(), '\n');
	}
	if (haku == 1) {
		string nimi;
		cout << "Varaajan nimi: ";
		cin.ignore();
		getline(cin, nimi);
		bool pari = false;
		for (size_t i = 0; i < varausnimet.size(); ++i) {
			if (varausnimet[i] == nimi) {
				cout << "Varaus l�ytyi numerolla " << varausnumerot[i] << "\n";
				pari = true;
			}
		}
		if (!pari) {
			cout << "Varausta nimell� " << nimi << " ei l�ytynyt.\n";
		}
	}
	else if (haku == 2) {
		int numero;
		cout << "Varausnumero: ";
		while (!(cin >> numero)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		bool pari = false;
		for (size_t i = 0; i < varausnumerot.size();++i) {
			if(varausnumerot[i]==numero){
				cout << "Varaus l�ytyi nimell� " << varausnimet[i] << "\n";
				pari = true;
			}
		}
		if (!pari) {
			cout << "Varausta numerolla " << numero << " ei l�ytynyt.\n";
		}
	}
}
int main() {
	setlocale(LC_ALL, "fi-FI");
	srand(static_cast<unsigned>(time(0)));
	int huoneidenmaara = rand() % 41 + 30; //arvotaan huoneiden m��r� 30-70
	int yhdenhuoneenhinta = rand() % 21 + 80;//arvotaan huoneiden hinnat 80-100
	int kahdenhuoneenhinta = rand() % 21 + 90; //90-110
	cout << "Yhden hengen huoneen hinta on " << yhdenhuoneenhinta << " euroa/ y�\n"; //hintojen m��r�t
	cout << "Kahden hengen huoneen hinta on " << kahdenhuoneenhinta << " euroa/y�\n";
	vector<bool>huoneet(huoneidenmaara, false);
	vector<string>varausnimet;
	vector<int>varausnumerot;
	int valitse;
	do {
		cout << "\nHotelli huoneen varaus\n";
		cout << "1. Tee uusi varaus\n";
		cout << "2. Hae varausta\n";
		cout << "3. Poistu\n";
		cout << "Valintasi: ";
		while (!(cin >> valitse) || valitse < 1 || valitse>3) {
			cout << "Virheellinen valinta ";
			cin.clear(); //poistaa virhetilan
			cin.ignore(numeric_limits <streamsize>::max(), '\n'); //poistaa rivin virheen j�lkeen
		}
		switch (valitse) {
		case 1:
			varauksenteko(huoneet, varausnimet, varausnumerot, yhdenhuoneenhinta, kahdenhuoneenhinta);
			break;
		case 2:
			varaushaku(varausnimet, varausnumerot);
			break;
		case 3: cout << "Kiitos k�ynnist� \n";
			break;
		}
	} while (valitse != 3); //ohjelma jatkuu kunnes k�ytt�j� valitsee poistumisen
	return 0;
}