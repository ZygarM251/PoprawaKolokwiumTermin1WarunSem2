#include <iostream>
#include <cstring>
#include <cmath> 

using namespace std;

#define Zadanie4

#ifdef Zadanie1

class Wlasciciel {
private:
	char nazwisko[50];
public:
	Wlasciciel(const char* nazwisko) {
		if (nazwisko == nullptr || strlen(nazwisko) == 0) {
			throw invalid_argument("nazwisko musi miec wartosc");
		}
		strncpy_s(this->nazwisko, nazwisko, sizeof(this->nazwisko));
		this->nazwisko[sizeof(this->nazwisko) - 1] = '\0';
	}

	const char* getNazwisko() const {
		return nazwisko;
	}

	void setNazwisko(const char* value) {
		if (value == nullptr || strlen(value) == 0) {
			throw invalid_argument("nazwisko musi miec wartosc");
		}
		strncpy_s(nazwisko, value, sizeof(nazwisko));
		nazwisko[sizeof(nazwisko) - 1] = '\0';
	}
};;

class Samochod
{
protected:
	static int ostatniNumerYYYYY;
	char numerRejestracyjnyXXX[4];
	int numerRejestracyjnyYYYYY;
	char numerRejestracyjny[10];
	int stanLicznika;
	bool czyDopuszczony;
	Wlasciciel wlasciciel;
public:
	Samochod(const char* rejestracjaXXX, int stanLicznika, bool czyDopuszczony, const Wlasciciel& wlasciciel)
		: stanLicznika(stanLicznika), czyDopuszczony(czyDopuszczony), wlasciciel(wlasciciel)
	{
		setRejestracjaXXX(rejestracjaXXX);
		setStanLicznika(stanLicznika);

		numerRejestracyjnyYYYYY = ++ostatniNumerYYYYY;
	}

	virtual ~Samochod() {}

	virtual double obliczWartosc(double warPocz) const {
		double wspSpraw = (czyDopuszczony) ? 1.0 : 0.2;
		double wartosc = (warPocz - 0.1 * stanLicznika) * wspSpraw;
		if (wartosc < 400.0) {
			wartosc = 400.0;
		}

		return wartosc;
	}

	virtual int obliczZasieg() const {
		return 800;
	}

	void setStanLicznika(int wartoscLicznika) {
		if (wartoscLicznika < 0) {
			throw invalid_argument("Stan musi byc wiekszy od zera");
		}
		stanLicznika = wartoscLicznika;
	}

	void setRejestracjaXXX(const char* value)
	{

		strncpy_s(numerRejestracyjnyXXX, value, sizeof(numerRejestracyjnyXXX));
		numerRejestracyjnyXXX[sizeof(numerRejestracyjnyXXX) - 1] = '\0';
	}

	void setCzyDopuszczony(bool value) {
		czyDopuszczony = value;
	}

	void setWlasciciel(const Wlasciciel& value) {
		wlasciciel = value;
	}

	const char* getRejestracja()
	{
		snprintf(numerRejestracyjny, sizeof(numerRejestracyjny), "%s-%05d", numerRejestracyjnyXXX, numerRejestracyjnyYYYYY);
		return numerRejestracyjny;
	}

	int getStanLicznika() { return stanLicznika; }

	bool getCzyDopuszczony() { return czyDopuszczony; }



	Wlasciciel& getWlasciciel() { return wlasciciel; }

	const char* getRejestracjaXXX() { return numerRejestracyjnyXXX; }

	bool operator==(const Samochod& other) const {
		if (strcmp(numerRejestracyjnyXXX, other.numerRejestracyjnyXXX) != 0) {
			return false;
		}
		if (abs(stanLicznika - other.stanLicznika) > 10) {
			return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream& os, Samochod& samochod) {
		os << "Samochod: " << samochod.getRejestracja()
			<< ", Licznik: " << samochod.getStanLicznika()
			<< ", Dopuszczenie: " << (samochod.getCzyDopuszczony() ? "dopuszczony" : "niedopuszczony")
			<< ", Właściciel: " << samochod.getWlasciciel().getNazwisko();
		return os;
	}

};
int Samochod::ostatniNumerYYYYY = 0;

class SamochodElektryczny : public Samochod
{
private:
	int stanBaterii;

public:
	SamochodElektryczny(const char* rejestracjaXXX, int stanLicznika, bool czyDopuszczony, const Wlasciciel& wlasciciel, int stanBaterii)
		: Samochod(rejestracjaXXX, stanLicznika, czyDopuszczony, wlasciciel), stanBaterii(stanBaterii)
	{
		if (stanBaterii < 0 || stanBaterii > 100) {
			throw invalid_argument("Zakres bateri musi wynosic od 0 do 100%");
		}
	}

	int obliczZasieg() const override {
		return 2.5 * stanBaterii;
	}

	int getStanBaterii() {
		return stanBaterii;
	}

	void setStanBaterii(int wartosc) {
		if (wartosc < 0 || wartosc > 100) {
			throw invalid_argument("Stan baterii powinien być w zakresie od 0 do 100%.");
		}
		stanBaterii = wartosc;
	}
};

int main()
{
	Wlasciciel wlasciciel1("Kowalski");
	Wlasciciel wlasciciel2("Nowak");

	Samochod samochod1("ABC", 1000, true, wlasciciel1);
	samochod1.setRejestracjaXXX("XYZ");
	samochod1.setStanLicznika(1050);
	samochod1.setCzyDopuszczony(false);

	SamochodElektryczny samochodElektryczny1("ELE", 800, true, wlasciciel2, 50);
	samochodElektryczny1.setStanBaterii(75);

	if (samochod1 == samochodElektryczny1) {
		cout << "Samochody sa identyczne." << endl;
	}
	else {
		cout << "Samochody nie sa identyczne." << endl;
	}

	cout << "Informacje o samochodzie 1: " << endl;
	cout << samochod1 << endl;

	cout << "Informacje o samochodzie elektrycznym 1: " << endl;
	cout << samochodElektryczny1 << endl;

	cout << "Zasięg samochodu 1: " << samochod1.obliczZasieg() << " km" << endl;
	cout << "Zasięg samochodu elektrycznego 1: " << samochodElektryczny1.obliczZasieg() << " km" << endl;
}

#endif 



#ifdef Zadanie2

class Miejscowosc {
private:
	char nazwa[50];

public:
	Miejscowosc(const char* nazwa) {
		strncpy_s(this->nazwa, nazwa, sizeof(this->nazwa));
		this->nazwa[sizeof(this->nazwa) - 1] = '\0';
	}

	const char* getNazwe() const {
		return nazwa;
	}
};

enum class TypBudynku {
	mieszkalny,
	publiczny,
	komercyjny
};

class Budynek {
protected:
	char ulica[50];
	int numer;
	char kodPocztowy[10];
	int metraz;
	TypBudynku typ;
	Miejscowosc miejscowosc;

	static int licznikBudynkowInnychNizPubliczne;

public:
	Budynek(const char* ulica, int numer, const char* kodPocztowy, int metraz, TypBudynku typ, const Miejscowosc& miejscowosc)
		: numer(numer), metraz(metraz), typ(typ), miejscowosc(miejscowosc)
	{
		setAdres(ulica, numer, kodPocztowy);
		if (typ != TypBudynku::publiczny) {
			licznikBudynkowInnychNizPubliczne++;
		}
	}

	virtual ~Budynek() {
		if (typ != TypBudynku::publiczny) {
			licznikBudynkowInnychNizPubliczne--;
		}
	}

	void setAdres(const char* ulica, int numer, const char* kodPocztowy)
	{
		strncpy_s(this->ulica, ulica, sizeof(this->ulica));
		this->ulica[sizeof(this->ulica) - 1] = '\0';

		this->numer = numer;

		strncpy_s(this->kodPocztowy, kodPocztowy, sizeof(this->kodPocztowy));
		this->kodPocztowy[sizeof(this->kodPocztowy) - 1] = '\0';
	}

	double przekatnaKwadratu() const {
		return sqrt(2.0) * sqrt(static_cast<double>(metraz));
	}

	virtual double operator()() const {
		return przekatnaKwadratu();
	}

	virtual void wyswietlInformacje() const {
		cout << "Adres: " << ulica << " " << numer << ", " << kodPocztowy << endl;
		cout << "Metraż: " << metraz << " m^2" << endl;
		cout << "Typ: ";
		switch (typ) {
		case TypBudynku::mieszkalny:
			cout << "mieszkalny";
			break;
		case TypBudynku::publiczny:
			cout << "publiczny";
			break;
		case TypBudynku::komercyjny:
			cout << "komercyjny";
			break;
		}
		cout << endl;
		cout << "Miejscowość: " << miejscowosc.getNazwe() << endl;
	}

	static int getLicznikBudynkowInnychNizPubliczne() {
		return licznikBudynkowInnychNizPubliczne;
	}
};


int Budynek::licznikBudynkowInnychNizPubliczne = 0;


class Posiadlosc : public Budynek {
private:
	int dzialka;

public:
	Posiadlosc(const char* ulica, int numer, const char* kodPocztowy, int metraz, const Miejscowosc& miejscowosc, TypBudynku typ, int dzialka)
		: Budynek(ulica, numer, kodPocztowy, metraz, typ, miejscowosc), dzialka(dzialka)
	{
		if (typ == TypBudynku::publiczny) {
			throw logic_error("Typ budynku nie może być publiczny dla posiadłości.");
		}
	}

	int getDzialka() const {
		return dzialka;
	}

	bool operator==(const Posiadlosc& other) const {
		if (miejscowosc.getNazwe() != other.miejscowosc.getNazwe() || metraz != other.metraz || dzialka != other.dzialka) {
			return false;
		}
		else if (typ != other.typ) {
			throw logic_error("Nie można porównać posiadłości o różnych typach.");
		}
		return true;
	}
};

int main() {
	Miejscowosc gdansk("Gdańsk");
	Miejscowosc sopot("Sopot");

	Budynek budynek1("ul. Spacerowa", 10, "80-001", 150, TypBudynku::mieszkalny, gdansk);
	Budynek budynek2("ul. Słoneczna", 5, "81-000", 200, TypBudynku::komercyjny, sopot);

	try {
		Posiadlosc posiadlosc1("ul. Kwiatowa", 20, "80-002", 300, gdansk, TypBudynku::mieszkalny, 500);
		Posiadlosc posiadlosc2("ul. Ogrodowa", 15, "81-001", 400, sopot, TypBudynku::mieszkalny, 600);
		Posiadlosc posiadlosc3("ul. Kwiatowa", 20, "80-002", 300, gdansk, TypBudynku::mieszkalny, 500);
		if (posiadlosc1 == posiadlosc2) {
			cout << "posiadlosc 1 i posiadlosc 2 sa identyczne." << endl;
		}
		else {
			cout << "posiadlosc 1 i posiadlosc 2 nie sa identyczne." << endl;
		}

		try {
			if (posiadlosc1 == posiadlosc3) {
				cout << "posiadlosc 1 i posiadlosc 3 sa identyczne." << endl;
			}
			else {
				cout << "posiadlosc 1 i posiadlosc 3 nie sa identyczne." << endl;
			}
		}
		catch (const logic_error& e) {
			cerr << "Wyjątek: " << e.what() << endl;
		}

	}
	catch (const exception& e) {
		cerr << "Wyjątek: " << e.what() << endl;
	}

	return 0;
}

#endif 

#ifdef Zadanie3

class Operator {
private:
	char nazwaOperatora[50];

public:
	Operator(const char* nazwa) {
		if (strlen(nazwa) > 49) {
			throw invalid_argument("Za dluga nazwa operatora");
		}
		strcpy(nazwaOperatora, nazwa);
	}

	const char* getNazwa() const {
		return nazwaOperatora;
	}
};

enum Stan {
	Wlaczony,
	Wylaczony,
	Zablokowany
};

class Telefon {
protected:
	char numer[12];
	int stanBaterii;
	Stan stan;
	Operator operatorTelefonii;
	static int liczbaZablokowanychTelefonow;
	const int pin;

public:
	Telefon(const char* numer, int stanBaterii, Stan stan, const Operator& op, int pin)
		: stanBaterii(stanBaterii), stan(stan), operatorTelefonii(op), pin(pin)
	{
		if (strlen(numer) != 11 || numer[3] != '-' || numer[7] != '-') {
			throw invalid_argument("Zly format danych");
		}
		strcpy(this->numer, numer);
		if (stan == Zablokowany) {
			throw invalid_argument("Telefon jest zablokowany");
		}
		if (pin < 0 || pin > 9999) {
			throw invalid_argument("Za duza ilosc cyfr PINu");
		}
		if (stan == Zablokowany) {
			liczbaZablokowanychTelefonow++;
		}
	}

	~Telefon() {
		if (stan == Zablokowany) {
			liczbaZablokowanychTelefonow--;
		}
	}

	Telefon& operator+=(int procenty) {
		stanBaterii += procenty;

		if (stanBaterii > 100)
			stanBaterii = 100;
		else if (stanBaterii < 0)
			stanBaterii = 0;

		if (stanBaterii == 0)
			stan = Wylaczony;

		return *this;
	}

	static int getLiczbaZablokowanych() {
		return liczbaZablokowanychTelefonow;
	}

	void setStanBaterii(int nowyStanBaterii) {
		if (nowyStanBaterii < 0 || nowyStanBaterii > 100) {
			throw invalid_argument("Nieprawidlowy poziom baterii.");
		}
		stanBaterii = nowyStanBaterii;
	}

	void setStan(Stan nowyStan, int pin = -1) {
		if (nowyStan == Zablokowany) {
			throw invalid_argument("Uzyj metody zablokuj() do zablokowania telefonu.");
		}

		if (stan == Zablokowany) {
			if (pin != this->pin) {
				throw invalid_argument("Nieprawidlowy PIN.");
			}
			liczbaZablokowanychTelefonow--;
		}

		stan = nowyStan;
	}

	const char* getNumer() const {
		return numer;
	}

	int getPin() const {
		return pin;
	}

	int getStanBaterii() const {
		return stanBaterii;
	}

	Stan getStan() const {
		return stan;
	}

	Operator getOperator() const {
		return operatorTelefonii;
	}

	void zablokuj(int pin) {
		if (pin != this->pin) {
			throw invalid_argument("Podano niepoprawny PIN.");
		}
		if (stan != Zablokowany) {
			stan = Zablokowany;
			liczbaZablokowanychTelefonow++;
		}
	}

	void odblokuj(int pin) {
		if (pin != this->pin) {
			throw invalid_argument("Podano niepoprawny PIN.");
		}
		if (stan == Zablokowany) {
			stan = Wylaczony;
			liczbaZablokowanychTelefonow--;
		}
	}

	virtual double obliczCzasDzialania() const {
		return 20.0 * stanBaterii;
	}
};

int Telefon::liczbaZablokowanychTelefonow = 0;

class SystemOperacyjny {
private:
	char nazwa[50];
	double kosztObliczeniowy;

public:
	SystemOperacyjny(const char* nazwa, double koszt)
		: kosztObliczeniowy(koszt)
	{
		if (strlen(nazwa) > 49) {
			throw invalid_argument("Za dluga nazwa systemu operacyjnego.");
		}
		if (koszt < 0.0 || koszt > 1.0) {
			throw invalid_argument("Koszt obliczeniowy musi byc w zakresie od 0.0 do 1.0.");
		}
		strcpy(this->nazwa, nazwa);
	}

	const char* getNazwa() const {
		return nazwa;
	}

	double getKosztObliczeniowy() const {
		return kosztObliczeniowy;
	}
};

class Smartfon : public Telefon {
private:
	SystemOperacyjny systemOperacyjny;

public:
	Smartfon(const char* numer, int stanBaterii, Stan stan, const Operator& op, int pin, const SystemOperacyjny& sys)
		: Telefon(numer, stanBaterii, stan, op, pin), systemOperacyjny(sys)
	{
	}

	Smartfon(Telefon& telefon, SystemOperacyjny& sys)
		: Telefon(telefon.getNumer(), telefon.getStanBaterii(), telefon.getStan(), telefon.getOperator(), telefon.getPin()), systemOperacyjny(sys)
	{
	}

	double obliczCzasDzialania() const override {
		return 20.0 - 10.0 * systemOperacyjny.getKosztObliczeniowy() * getStanBaterii();
	}

	const char* getNazwaSystemu() const {
		return systemOperacyjny.getNazwa();
	}
};

int main()
{
	try {
		Operator operatorPlus("Plus");
		Telefon telefon("123-456-789", 50, Telefon::Wlaczony, operatorPlus, 1234);

		cout << "Stan poczatkowy:" << endl;
		telefon.wyswietl();

		// Doładowanie o 30%
		telefon += 30;
		cout << "Po doładowaniu o 30%:" << endl;
		telefon.wyswietl();

		// Rozładowanie o 80%
		telefon += -80;
		cout << "Po rozładowaniu o 80%:" << endl;
		telefon.wyswietl();

		// Dodatkowe rozładowanie o 10%
		telefon += -10;
		cout << "Po dodatkowym rozładowaniu o 10%:" << endl;
		telefon.wyswietl();

		// Sprawdzenie zmiany stanu na Wylaczony przy rozładowaniu do zera
		telefon += -10;
		cout << "Po dodatkowym rozładowaniu o 10%:" << endl;
		telefon.wyswietl();

	}
	catch (const invalid_argument& e) {
		cerr << "Blad: " << e.what() << endl;
	}
}

#endif 

#ifdef Zadanie4

class Autor {
private:
	char nazwisko[100];  
public:
	Autor(const char* nazwisko) {
		strncpy_s(this->nazwisko, nazwisko, sizeof(this->nazwisko));
		this->nazwisko[sizeof(this->nazwisko) - 1] = '\0';  
	}

	const char* getNazwisko() const {
		return nazwisko;
	}
};


class Książka {
private:
	char Tytul[100];   
	int liczbaStron;   
	bool dostępność;       
	Autor* autor;          

	static Książka* instancjaWzorcowa;

	Książka(const Książka& k)
		: liczbaStron(k.liczbaStron), dostępność(k.dostępność), autor(k.autor) {
		strncpy_s(this->Tytul, k.Tytul, sizeof(this->Tytul));
		this->Tytul[sizeof(this->Tytul) - 1] = '\0';  
	}

public:
	Książka() {
		if (instancjaWzorcowa == nullptr) {
			cerr << "Błąd: Instancja wzorcowa nie została setiona\n";
			exit(1);
		}
		*this = *instancjaWzorcowa;
	}

	Książka(const char* Tytul, int liczbaStron, bool dostępność, Autor* autor)
		: liczbaStron(liczbaStron), dostępność(dostępność), autor(autor) {
		strncpy_s(this->Tytul, Tytul, sizeof(this->Tytul));
		this->Tytul[sizeof(this->Tytul) - 1] = '\0';  
	}

	static void setInstancjęWzorcową(Książka* instancja) {
		instancjaWzorcowa = instancja;
	}

	const char* getTytul() const {
		return Tytul;
	}

	void setTytul(const char* nowyTytul) {
		strncpy_s(this->Tytul, nowyTytul, sizeof(this->Tytul));
		this->Tytul[sizeof(this->Tytul) - 1] = '\0';  
	}

	int getLiczbaStron() const {
		return liczbaStron;
	}

	void setLiczbaStron(int nowaLiczbaStron) {
		liczbaStron = nowaLiczbaStron;
	}

	bool czyDostępna() const {
		return dostępność;
	}

	void setDostępność(bool nowaDostępność) {
		dostępność = nowaDostępność;
	}

	Autor* getAutora() const {
		return autor;
	}

	void setAutora(Autor* nowyAutor) {
		autor = nowyAutor;
	}

	virtual float obliczCenę() const {
		return 1.0 * liczbaStron; 
	}

	operator const char* () const {
		int bufferSize = 200;  
		char* opis = new char[bufferSize];

		snprintf(opis, bufferSize, "Tytul: %s\nLiczba stron: %d\nDostępnosc: %s\nAutor: %s",
			Tytul, liczbaStron, dostępność ? "Dostępna" : "Niedostępna", autor->getNazwisko());

		return const_cast<const char*>(opis);
	}

	bool operator==(const Książka& other) const 
	{
		return (liczbaStron == other.liczbaStron &&
			   dostępność == other.dostępność &&
			   strcmp(autor->getNazwisko(), other.autor->getNazwisko()) == 0);
	}
};

Książka* Książka::instancjaWzorcowa = nullptr;

class EBook : public Książka {
private:
	float rozmiarMB;

public:
	EBook(const char* Tytul, int liczbaStron, bool dostępność, Autor* autor, float rozmiarMB)
		: Książka(Tytul, liczbaStron, dostępność, autor), rozmiarMB(rozmiarMB) {}

	float obliczCenę() const override {
		return 0.75 * Książka::obliczCenę();
	}

	float getRozmiarMB() const {
		return rozmiarMB;
	}

	void setRozmiarMB(float nowyRozmiarMB) {
		rozmiarMB = nowyRozmiarMB;
	}
};


int main()
{
	Autor* autor1 = new Autor("Kowalski");
	Autor* autor2 = new Autor("Nowak");

	Książka ksiazka1("Programowanie w C++", 300, true, autor1);
	Książka ksiazka2("Algorytmy i struktury danych", 400, true, autor2);
	Książka ksiazka3("Programowanie w C++", 300, true, autor1);

	if (ksiazka1 == ksiazka2) {
		cout << "Ksiazki 1 i 2 sa identyczne.\n";
	}
	else {
		cout << "Ksiazki 1 i 2 nie sa identyczne.\n";
	}

	if (ksiazka1 == ksiazka3) {
		cout << "Ksiazki 1 i 3 sa identyczne.\n";
	}
	else {
		cout << "Ksiazki 1 i 3 nie sa identyczne.\n";
	}

	const char* opisKsiazki1 = ksiazka1;
	cout << "\nOpis Ksiazki 1:\n" << opisKsiazki1 << endl;

	EBook ebook1("Algorytmy w praktyce", 250, true, autor2, 5.2);

	cout << "\nCena Ebooka: " << ebook1.obliczCenę() << " PLN" << endl;

	delete autor1;
	delete autor2;
}

#endif 
