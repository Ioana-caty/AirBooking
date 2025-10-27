#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Pasager.h"

class Zbor {
private:
    std::string numarZbor;
    std::string destinatie;
    std::string poarta;
    std::vector<Pasager> listaPasageri;
    size_t capacitateMaxima;

    bool estePoartaValida(const std::string& poarta) const;

public:

    //Constructori
    Zbor();
    Zbor(const std::string& numarZbor, const std::string& destinatie, const std::string& poarta, int capacitateMaxima);

    //Destructor
    virtual ~Zbor();

    //Getters
    std::string getNumarZbor() const;
    std::string getPoarta() const;
    int getLocuriOcupate() const;
    size_t getCapacitateMaxima() const;


    //Setters
    void setPoarta(const std::string& nouaPoarta);

    //Functii
    bool adaugaPasager(const Pasager& p);
    double calculeazaIncasariTotale() const;
    Pasager* cautaPasagerDupaNume(const char* nume);
    bool isFull() const;

    friend std::ostream& operator<<(std::ostream& COUT, const Zbor& z);
};