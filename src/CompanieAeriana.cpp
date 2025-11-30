#include "../headers/CompanieAeriana.h"
#include <iostream>
#include <iomanip>

CompanieAeriana::CompanieAeriana() : numeCompanie("Companie Anonima") {
}
CompanieAeriana::CompanieAeriana(const std::string& nume) : numeCompanie(nume) {
}

bool CompanieAeriana::esteZborDuplicat(const std::string& numarZbor) const {
    for (const auto& zbor : flotaZboruri) {
	    if (zbor.getNumarZbor() == numarZbor) {
		    return true;
	    }
    }
	return false;
}

void CompanieAeriana::adaugaZbor(const Zbor& z) {
    if (!this->esteZborDuplicat(z.getNumarZbor())) {
        this->flotaZboruri.push_back(z);
    } else {
        std::cerr << "Eroare: Zborul " << z.getNumarZbor() << " exista deja!\n";
    }
}
// nu e void pt ca vreau sa am detaliile zborului ca sa-l pot adauga
Zbor *CompanieAeriana::cautaZborDupaNumar(const std::string& numarZbor) {
    for (const auto& zbor : flotaZboruri) {
        if (zbor.getNumarZbor() == numarZbor) {
            return &zbor;
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& COUT, const CompanieAeriana& c) {
    COUT << "COMPANIE: " << c.numeCompanie << "\n";
    COUT << "FLOTA DE ZBORURI (" << c.flotaZboruri.size() << "):\n";

    if (c.flotaZboruri.empty() == true) {
        COUT << "Niciun zbor inregistrat\n";
    } else {
        for (auto& zbor : c.flotaZboruri) {
            COUT << zbor << "\n";
        }
    }
    return COUT;
}