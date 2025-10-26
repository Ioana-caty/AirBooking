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
    this->capacitateMaxima = 0;
}

Zbor::Zbor(const std::string& numarZbor, const std::string& destinatie, const std::string& poarta, int capacitateMaxima) {
    this->numarZbor = numarZbor;
    this->destinatie = destinatie;
    this->poarta = poarta;
    this->capacitateMaxima = capacitateMaxima;
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
std::string Zbor::getPoarta()const{return this->poarta;}
int Zbor::getLocuriOcupate()const{return this->listaPasageri.size();}
size_t Zbor::getCapacitateMaxima() const {return this->capacitateMaxima;}


void Zbor::setPoarta(const std:: string& nouaPoarta) {
    if (this-> estePoartaValida(nouaPoarta)) {
        this->poarta = nouaPoarta;
    } else {
        std::cerr << "Eroare. Poarta " << nouaPoarta <<" este invalida!" << std::endl;
        this->poarta = "N/A";
    }
}

bool Zbor::isFull() const {
    return this->listaPasageri.size() >= this->capacitateMaxima;
}

bool Zbor::adaugaPasager(const Pasager& p) {
    if (this->isFull()) {
        std::cerr   << "\n!!! EROARE: Zborul " << this->numarZbor << " este PLIN("
                    << this->getLocuriOcupate() << "/" << this->capacitateMaxima
                    <<").\nPasagerul " << p.getNume() << " NU a putut fi adaugat.\n";
        return false;
    }
    this->listaPasageri.push_back(p);
    return true;
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
    std::cerr << "EROARE: Pasagerul '" << nume << "' nu a fost gasit.\n";
    return nullptr;
}


std::ostream& operator<<(std::ostream& COUT, const Zbor& z) {
    COUT    << "ZBOR: " << z.numarZbor
            <<"| DESTINATIE: " << z.destinatie
            <<"| POARTA: " << z.poarta
            <<"| LOCURI: " << z.getLocuriOcupate() << "/" << z.capacitateMaxima << "\n";

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