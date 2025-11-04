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

public:

    Zbor();
    Zbor(const std::string& numarZbor, const std::string& destinatie, const std::string& poarta, int capacitateMaxima);

    virtual ~Zbor();

    std::string getNumarZbor() const;
    int getLocuriOcupate() const;
    size_t getCapacitateMaxima() const;

    void setPoarta(const std::string& nouaPoarta);

    bool adaugaPasager(const Pasager& p);
    double calculeazaIncasariTotale() const;
    Pasager* cautaPasagerDupaNume(const std::string &nume);
    bool isFull() const;

    friend std::ostream& operator<<(std::ostream& COUT, const Zbor& z);
};