#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "../headers/Pasager.h"

class CompanieAeriana;

class Zbor {
private:
    std::string numarZbor;
    std::string destinatie;
    std::string poarta;
    std::vector<Pasager> listaPasageri;
    size_t capacitateMaxima;

    bool estePoartaValida(const std::string& poartaNoua) const;
	bool existaPasager(const std::string& nume) const;

public:

    Zbor();
    Zbor(const std::string& numarZbor, const std::string& destinatie, const std::string& poarta, int capacitateMaxima);

    const std::string& getNumarZbor() const { return numarZbor; }
    int getLocuriOcupate() const {return listaPasageri.size(); }

	const std::string& getPoarta() const { return poarta; }
	const std::vector<Pasager>& getPasageri() const { return listaPasageri; }

    bool setPoarta(const std::string& nouaPoarta);
    bool adaugaPasager(const Pasager& p);
	bool isFull() const;
	bool upgradeBiletPasager(const std::string& nume);
	bool esteLocOcupat (const std::string& loc, const std::string& numeDeExclus) const;
	bool corespundeNumarului(const std::string& numar) const;

	double calculeazaIncasariTotale() const;
	void afiseazaLocuriOcupate() const;
	void afiseazaDetaliiCapacitate() const;

	Pasager* cautaPasagerDupaNume(const std::string &nume);

	~Zbor();


    friend std::ostream& operator<<(std::ostream& COUT, const Zbor& z);
	friend void saveData(const CompanieAeriana& companie, const std::string& nameFile);
};