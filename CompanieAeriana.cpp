#include "CompanieAeriana.h"
#include <iostream>
#include <iomanip>

CompanieAeriana::CompanieAeriana() {
    this->numeCompanie = "Companie Anonima";
}

CompanieAeriana::CompanieAeriana(const std::string &nume) {
    this->numeCompanie = nume;
}

bool CompanieAeriana::esteZborDuplicat(const std::string &numarZbor) const {
    size_t nrTotalZboruri = this->flotaZboruri.size();
    for (size_t i = 0; i < nrTotalZboruri; i++) {
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

// nu e void pt ca vreau sa am detaliile zborului ca sa-l pot adauga
const Zbor *CompanieAeriana::cautaZborDupaNumar(const std::string &numarZbor) {
    size_t nrTotalZboruri = this->flotaZboruri.size();
    for (size_t i = 0; i < nrTotalZboruri; ++i) {
        if (this->flotaZboruri[i].getNumarZbor() == numarZbor) {
            return &this->flotaZboruri[i];
        }
    }
    return nullptr;
}


std::ostream &operator<<(std::ostream &COUT, const CompanieAeriana &c) {
    COUT << "COMPANIE: " << c.numeCompanie << "\n";
    COUT << "FLOTA DE ZBORURI (" << c.flotaZboruri.size() << "):\n";

    if (c.flotaZboruri.empty() == true) {
        COUT << "(Niciun zbor inregistrat)\n";
    } else {
        size_t nrTotalZboruri = c.flotaZboruri.size();
        for (size_t i = 0; i < nrTotalZboruri; ++i) {
            COUT << c.flotaZboruri[i] << "\n\n";
        }
    }
    return COUT;
}
