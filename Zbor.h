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

    bool estePoartaValida(const std::string& poarta) const;

public:
    //Constructori
    Zbor();
    Zbor(const std::string& numarZbor, const std::string& destinatie, const std::string& poarta);

    //Destructor
    virtual ~Zbor();

    //Getters
    std::string getNumarZbor() const;
    std::string getDestinatie() const;
    std::string getPoarta() const;


    //Setters
    void setPoarta(const std::string& poarta);
    void adaugaPasager(const Pasager& p);
    double calculeazaIncasariTotale() const;
    Pasager* cautaPasagerDupaNume(const char* nume);

    friend std::ostream& operator<<(std::ostream& COUT, const Zbor& z);
};