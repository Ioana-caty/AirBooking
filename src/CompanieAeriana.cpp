#include "../headers/CompanieAeriana.h"
#include "../headers/Exceptii.h"
#include <iostream>
#include <iomanip>

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
	if (this->esteZborDuplicat(z.getNumarZbor())) {
		throw ExceptieOperatie("Zborul " + z.getNumarZbor() + " exista deja");
	}
	this->flotaZboruri.push_back(z);
	return true;
}

// nu e void pt ca vreau sa am detaliile zborului ca sa-l pot adauga
Zbor *CompanieAeriana::cautaZborDupaNumar(const std::string& numarZbor) {
    for (auto& zbor : flotaZboruri) {
        if (zbor.corespundeNumarului(numarZbor)) {
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