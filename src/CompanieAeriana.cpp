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

Zbor *CompanieAeriana::cautaZborDupaNumar(const std::string& numarZbor) {
    for (auto& zbor : flotaZboruri) {
        if (zbor.corespundeNumarului(numarZbor)) {
            return &zbor;
        }
    }
    return nullptr;
}

void CompanieAeriana::sorteazaZboruriDupaDestinatie() {
	std::sort(flotaZboruri.begin(), flotaZboruri.end(), [](const Zbor& a, const Zbor& b) {
		return toUpperCase(a.getDestinatie()) < toUpperCase(b.getDestinatie());
	});
	mesajSucces("Zboruri sortate alfabetic dupa destinatie");
}

void CompanieAeriana::sorteazaZboruriDupaOcupare() {
	std::sort(flotaZboruri.begin(), flotaZboruri.end(),
			  [](const Zbor& a, const Zbor& b) {
				  return b < a;
			  });
	mesajSucces("Zboruri sortate dupa rata de ocupare (descrescator)");
}

void CompanieAeriana::sorteazaZboruriDupaIncasari() {
	std::sort(flotaZboruri.begin(), flotaZboruri.end(),
			  [](const Zbor& a, const Zbor& b) {
				  return a > b;
			  });
	mesajSucces("Zboruri sortate dupa incasari (descrescator)");
}

std::vector<Zbor*> CompanieAeriana::filtreazaZboruriPline() {
	std::vector<Zbor*> rezultat;

	for (auto& zbor : flotaZboruri) {
		if (zbor.isFull()) {
			rezultat.push_back(&zbor);
		}
	}

	return rezultat;
}

std::vector<Zbor*> CompanieAeriana::filtreazaZboruriGoale() {
	std::vector<Zbor*> rezultat;

	for (auto& zbor : flotaZboruri) {
		if (zbor.getLocuriOcupate() == 0) {
			rezultat.push_back(&zbor);
		}
	}

	return rezultat;
}

std::vector<Zbor*> CompanieAeriana::cautaZboruriDupaDestinatie(const std::string& dest) {
	std::vector<Zbor*> rezultat;

	std::string destUpper = toUpperCase(dest);

	for (auto& zbor : flotaZboruri) {
		if (toUpperCase(zbor.getDestinatie()) == destUpper) {
			rezultat.push_back(&zbor);
		}
	}
	return rezultat;
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

void CompanieAeriana::afisareFaraPasageri(bool incasari) const {
	std::cout << "\n==============================================================================================\n";
	for (const auto& zbor : flotaZboruri) {
		zbor.afisareFaraPasageri(incasari);
	}
	std::cout << "==============================================================================================\n";
}