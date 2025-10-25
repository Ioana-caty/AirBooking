#include "Zbor.h"
#include <iostream>
#include <iomanip>
#include <algorithm>    // std::sort
#include <cstring>      // strcmp
#include <cctype>


Zbor::Zbor() {
    this->numarZbor = "N/A";
    this->destinatie = "N/A";
    this->poarta = "N/A";
}

Zbor::Zbor(const std::string& numarZbor, const std::string& destinatie, const std::string& poarta) {
    this->numarZbor = numarZbor;
    this->destinatie = destinatie;
    this->poarta = poarta;
}

Zbor::~Zbor() { }

bool Zbor::estePoartaValida(const std::string& poarta) const {
    //minim 2 caractere
    if (poarta.length() < 2) {
        return false;
    }

    // primul caracter sa fie litera
    if (!isalpha(poarta[0])) {
        return false;
    }

    //verificam ca toate celelalte caractere sunt cifre
    for (size_t i = 1; i < poarta.length(); i++) {
        if (!isdigit(poarta[i])) {
            return false;
        }
    }
    return true;
}

std::string Zbor::getNumarZbor()const{return this->numarZbor;}
std::string Zbor::getDestinatie()const{return this->destinatie;}
std::string Zbor::getPoarta()const{return this->poarta;}

void Zbor::setPoarta(const std:: string& poarta) {
    if (this-> estePoartaValida(poarta)) {
        this->poarta = poarta;
    } else {
        std::cerr << "Eroare. Poarta " << poarta <<" este invalida!" << std::endl;
        this->poarta = "N/A";
    }
}

void Zbor::adaugaPasager(const Pasager& p) {
    this->listaPasageri.push_back(p);
}

double Zbor::calculeazaIncasariTotale()const {
    double total = 0.0;
    for (size_t i = 0; i < this->listaPasageri.size(); i++) {
        total += this->listaPasageri[i].getBilet().getPretFinal();
    }
    return total;
}

Pasager* Zbor::cautaPasagerDupaNume(const char* nume) {
   for (size_t i = 0; i < this->listaPasageri.size(); i++) {
        if (std::strcmp(this->listaPasageri[i].getNume(), nume) == 0) {
            return &this->listaPasageri[i];
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& COUT, const Zbor& z) {
    COUT    << "ZBOR: " << z.numarZbor
            <<"| DESTINATIE: " << z.destinatie
            <<"| POARTA: " << z.poarta << "\n";
    COUT    <<"Lista pasageri (" << z.listaPasageri.size() << ")\n";

    if (z.listaPasageri.empty()) {
        COUT << "Niciun pasager inregistrat\n";
    } else {
        for (size_t i = 0; i < z.listaPasageri.size(); i++) {
            COUT << z.listaPasageri[i] << "\n";
        }
    }
    return COUT;
}