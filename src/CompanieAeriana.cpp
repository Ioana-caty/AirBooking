#include "../headers/CompanieAeriana.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>

CompanieAeriana::CompanieAeriana() : numeCompanie("Companie Anonima") {
}
CompanieAeriana::CompanieAeriana(const std::string& nume) : numeCompanie(nume) {
}

bool CompanieAeriana::esteZborDuplicat(const std::string& numarZbor) const {
    for (const auto& zbor : flotaZboruri) {
	    if (toUpperCase(zbor.getNumarZbor()) == toUpperCase(numarZbor)) {
		    return true;
	    }
    }
	return false;
}

bool CompanieAeriana::adaugaZbor(const Zbor& z) {
    if (!this->esteZborDuplicat(z.getNumarZbor())) {
        this->flotaZboruri.push_back(z);
    	return true;
    } else {
        std::cerr << "\n !!!EROARE: Zborul " << z.getNumarZbor() << " exista deja!\n";
    	return false;
    }
}
// nu e void pt ca vreau sa am detaliile zborului ca sa-l pot adauga
Zbor *CompanieAeriana::cautaZborDupaNumar(const std::string& numarZbor) {
    for (auto& zbor : flotaZboruri) {
        if (toUpperCase(zbor.getNumarZbor()) == toUpperCase(numarZbor)) {
            return &zbor;
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& COUT, const CompanieAeriana& c) {

	COUT << "==============================================================================================\n";
    COUT << "COMPANIE: " << c.numeCompanie << "\n";
    COUT << "FLOTA DE ZBORURI (" << c.flotaZboruri.size() << "):\n";
	COUT << "==============================================================================================\n";

    if (c.flotaZboruri.empty() == true) {
        COUT << "Niciun zbor inregistrat\n";
    } else {
        for (const auto& zbor : c.flotaZboruri) {
            COUT << zbor << "\n\n";
        }
    }
    return COUT;
}