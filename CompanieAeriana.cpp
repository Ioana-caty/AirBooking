#include "CompanieAeriana.h"
#include <iostream>
#include <iomanip>

CompanieAeriana::CompanieAeriana() {
    this->numeCompanie = "Companie Anonima";
}

CompanieAeriana::CompanieAeriana(const std::string &nume) {
    this->numeCompanie = nume;
}

CompanieAeriana::~CompanieAeriana() {
}

std::string CompanieAeriana::getNumeCompanie() const {
    return this->numeCompanie;
}

bool CompanieAeriana::esteZborDuplicat(const std::string &numarZbor) const {
    for (size_t i = 0; i < this->flotaZboruri.size(); ++i) {
        if (this->flotaZboruri[i].getNumarZbor() == numarZbor) {
            return true;
        }
    }
    return false;
}

void CompanieAeriana::adaugaZbor(const Zbor &z) {
    if (!this->esteZborDuplicat(z.getNumarZbor())) {
        this->flotaZboruri.push_back(z);
    } else {
        std::cerr << "Eroare: Zborul " << z.getNumarZbor() << " exista deja!" << std::endl;
    }
}

Zbor *CompanieAeriana::cautaZborDupaNumar(const std::string &numarZbor) {
    for (size_t i = 0; i < this->flotaZboruri.size(); ++i) {
        if (this->flotaZboruri[i].getNumarZbor() == numarZbor) {
            return &this->flotaZboruri[i];
        }
    }
    return nullptr; // Nu s-a gasit
}


std::ostream &operator<<(std::ostream &COUT, const CompanieAeriana &c) {
    COUT << "COMPANIE: " << c.numeCompanie << "\n";
    COUT << "FLOTA DE ZBORURI (" << c.flotaZboruri.size() << "):\n";

    if (c.flotaZboruri.empty()) {
        COUT << "(Niciun zbor inregistrat)\n";
    } else {
        for (size_t i = 0; i < c.flotaZboruri.size(); ++i) {
            COUT << c.flotaZboruri[i] << "\n\n";
        }
    }
    return COUT;
}
