#pragma once
#include <iostream>
#include <string>
#include <vector>
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

    std::string getNumarZbor() const;
    int getLocuriOcupate() const;
    size_t getCapacitateMaxima() const;

	const std::string& getDestinatie() const { return destinatie; }
	const std::string& getPoarta() const { return poarta; }
	const std::vector<Pasager>& getPasageri() const { return listaPasageri; }

    void setPoarta(const std::string& nouaPoarta);
    bool adaugaPasager(const Pasager& p);
    double calculeazaIncasariTotale() const;
    Pasager* cautaPasagerDupaNume(const std::string &nume);
    bool isFull() const;
	bool upgradeBiletPasager(const std::string& nume);

	~Zbor();
    friend std::ostream& operator<<(std::ostream& COUT, const Zbor& z);
};