#include "../headers/Zbor.h"
#include <iostream>
#include <iomanip>
#include <algorithm>    // std::sort
#include <cctype>

Zbor::Zbor()
    : numarZbor("N/A"), destinatie("N/A"), poarta("N/A"), capacitateMaxima(0) {
}
Zbor::Zbor(const std::string& nrz, const std::string& d, const std::string& p, int c)
	: numarZbor(nrz), destinatie(d), poarta(p), capacitateMaxima(c) {}

bool Zbor::estePoartaValida(const std::string& poartaNoua) const {
    if (poartaNoua.length() < 2) { //minim 2 caractere
        return false;
    }
    if (!isalpha(poartaNoua[0])) { // primul caracter sa fie litera
        return false;
    }
    for (size_t i = 1; i < poartaNoua.length(); i++) {
        if (!isdigit(poartaNoua[i])) { //toate celelalte caractere sunt cifre
            return false;
        }
    }
    return true;
}

std::string Zbor::getNumarZbor()const { return this->numarZbor; }
int Zbor::getLocuriOcupate()const { return this->listaPasageri.size(); }
size_t Zbor::getCapacitateMaxima() const { return this->capacitateMaxima; }

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
                    <<").\n";
        return false;
    }
    this->listaPasageri.push_back(p);
    return true;
}

double Zbor::calculeazaIncasariTotale()const {
    double total = 0.0;
    for (const auto& pasager : this->listaPasageri) {
    	if (pasager.getBilet() != nullptr) {
    		total += pasager.getBilet()->getPretFinal();
    	}
    }
    return total;
}

Pasager* Zbor::cautaPasagerDupaNume(const std::string& nume){
   for (const auto& pasager : this->listaPasageri) {
	   if (pasager.getNume() == nume) {
		   return &pasager;
	   }
   }
    return nullptr;
}

Zbor::~Zbor() {}
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