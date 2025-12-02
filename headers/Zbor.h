#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "../headers/Pasager.h"


class Zbor {
private:
    std::string numarZbor;
    std::string destinatie;
    std::string poarta;
    std::vector<Pasager> listaPasageri;
    size_t capacitateMaxima;

    bool estePoartaValida(const std::string& poartaNoua) const;
	bool exitaPasager(const std::string& nume) const;

public:

    Zbor();
    Zbor(const std::string& numarZbor, const std::string& destinatie, const std::string& poarta, int capacitateMaxima);

    std::string getNumarZbor() const { return numarZbor; }
    int getLocuriOcupate() const {return listaPasageri.size(); }
    size_t getCapacitateMaxima() const {return capacitateMaxima; }

	const std::string& getDestinatie() const { return destinatie; }
	const std::string& getPoarta() const { return poarta; }
	const std::vector<Pasager>& getPasageri() const { return listaPasageri; }

    bool setPoarta(const std::string& nouaPoarta);
    bool adaugaPasager(const Pasager& p);
    double calculeazaIncasariTotale() const;
    Pasager* cautaPasagerDupaNume(const std::string &nume);
    bool isFull() const;
	bool upgradeBiletPasager(const std::string& nume);
	void afiseazaLocuriOcupate() const;
	bool esteLocOcupat (const std::string& loc, const std::string& numeDeExclus) const;

	~Zbor();
    friend std::ostream& operator<<(std::ostream& COUT, const Zbor& z);
};