#include "../headers/Zbor.h"
#include "../headers/CompanieAeriana.h"
#include "../headers/Exceptii.h"
#include "../headers/Utils.h"
#include <iostream>
#include <iomanip>

Zbor::Zbor()
    : numarZbor("N/A"), destinatie("N/A"), poarta("N/A"), capacitateMaxima(0) {
}
Zbor::Zbor(const std::string& nrz, const std::string& d, const std::string& p, int c)
	: destinatie(d), capacitateMaxima(c) {

	if (c <= 0) {
		throw ExceptieValidare("Capacitate invalida: " + std::to_string(c) + " (trebuie > 0)");
	}

	// validare si conversie pentru nrz
	std::string nrzUpper = toUpperCase(nrz);
	this->numarZbor = nrzUpper;

	// validare poarta
	std::string poartaUpper = toUpperCase(p);
	if (!estePoartaValida(poartaUpper)) {
		throw ExceptieValidare("Poarta invalida: " + poartaUpper + " (format: litera + cifre, ex: A12)");
	}
	this->poarta = poartaUpper;
}

bool Zbor::estePoartaValida(const std::string& poartaNoua) const {
	return esteFormatValid(poartaNoua, false);
}

bool Zbor::existaPasager(const std::string& nume) const {
	for (const auto& pasager : this->listaPasageri) {
		if (pasager.corespundeNumelui(nume)) {
			return true;
		}
	}
	return false;
}

bool Zbor::setPoarta(const std:: string& nouaPoarta) {

    if (this-> estePoartaValida(toUpperCase(nouaPoarta))) {
        this->poarta = toUpperCase(nouaPoarta);
    	return true;
    } else {
    	return false;
    }
}

bool Zbor::isFull() const {
    return this->listaPasageri.size() >= this->capacitateMaxima;
}

bool Zbor::adaugaPasager(const Pasager& p) {
	// verificare zbor este full
	if (this->isFull()) {
		throw ExceptieCapacitate("Zborul " + this->numarZbor + " este plin");
	}
	// verificam daca pasagerul exista deja
	if (this->existaPasager(p.getNume())) {
		throw ExceptieOperatie("Pasagerul " + p.getNume() + " este deja pe zborul " + this->numarZbor);
	}
	// verificam daca locul este disponibil
	if (p.getBilet() != nullptr) {
		std::string loc = p.getBilet()->getLoc();
		if (esteLocOcupat(loc, "")) {
			throw ExceptieOperatie("Locul " + loc + " este ocupat pe zborul " + this->numarZbor);
		}
	}

	this->listaPasageri.push_back(p);
	return true;
}

double Zbor::calculeazaIncasariTotale()const {
    double total = 0.0;
    for (const auto& pasager : this->listaPasageri) {
    	pasager.incasari(total);
    }
    return total;
}

Pasager* Zbor::cautaPasagerDupaNume(const std::string& nume){
	for (auto& pasager : this->listaPasageri) {
	   if (pasager.corespundeNumelui(nume)) {
		   return &pasager;
	   }
   }
    return nullptr;
}

bool Zbor::upgradeBiletPasager(const std::string& nume) {
	Pasager* pasager = cautaPasagerDupaNume(nume);
	if (pasager == nullptr) {
		std::cerr << "Pasager negasit!\n";
		return false;
	}

	const Bilet* biletVechi = pasager->getBilet();
	if (biletVechi == nullptr) {
		std::cerr << "Pasagerul nu are bilet!\n";
		return false;
	}

	UI::subtitlu("UPGRADE BILET");
	mesajInfo("Clasa curenta: " + biletVechi->getTipClasa());
	mesajInfo("Pret actual: " + Formatare::formatareMoneda(biletVechi->getPretFinal()));

	Bilet* biletNou = biletVechi->creeazaUpgrade();

	if (biletNou == nullptr) {
		mesajInfo("Biletul este deja la nivel maxim! Nu se mai poate face upgrade!");
		return false;
	}

	mesajInfo("Clasa noua: " + biletNou->getTipClasa());
	mesajInfo("Pret nou: " + Formatare::formatareMoneda(biletNou->getPretFinal()));

	pasager->actualizeazaBilet(biletNou);
	delete biletNou;
	mesajSucces("Upgrade realizat cu succes!");
	return true;
}

void Zbor::afiseazaLocuriOcupate() const {
	std::cout << "----Locuri Ocupate---- ";
	for (const auto& pasager: this->listaPasageri) {
		if (pasager.getBilet() != nullptr) {
			std::cout << pasager.getBilet()->getLoc() << " ";
		}
	}
	std::cout << "\n";
}

bool Zbor::esteLocOcupat(const std::string& loc, const std::string& numeDeExclus) const {
	for (const auto& pasager : this->listaPasageri) {
		if (pasager.getNume() == toUpperCase(numeDeExclus)) {
			continue;
		}
		if (pasager.getBilet() != nullptr && pasager.getBilet()->getLoc() == loc) {
			return true;
		}
	}
	return false;
}

void Zbor::afiseazaDetaliiCapacitate() const {
	if (isFull()) {
		std::cout << "Zborul este PLIN (" << listaPasageri.size()
				  << "/" << capacitateMaxima << ")\n";
	} else {
		int disponibile = capacitateMaxima - listaPasageri.size();
		std::cout << "Zborul are " << disponibile << " locuri ramase ("
				 << listaPasageri.size() << "/" << capacitateMaxima << ")\n";
	}
}

bool Zbor::corespundeNumarului(const std::string& numar) const {
	return toUpperCase(numarZbor) == toUpperCase(numar);
}

Zbor::~Zbor() {}

std::ostream& operator<<(std::ostream& COUT, const Zbor& z) {
    COUT    << "ZBOR: " << z.numarZbor
            <<"| DESTINATIE: " << z.destinatie
            <<"| POARTA: " << z.poarta
            <<"| LOCURI: " << z.getLocuriOcupate() << "/" << z.capacitateMaxima << "\n";
	COUT << "----------------------------------------------------------------------------------------------\n";
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

void Zbor::afisareFaraPasageri(bool afiseazaIncasari = false) const {
	std::cout << "ZBOR: " << numarZbor
			  << " | DESTINATIE: " << destinatie
			  << " | POARTA: " << poarta
			  << " | LOCURI: " << getLocuriOcupate() << "/" << capacitateMaxima;

	if (afiseazaIncasari) {
		std::cout << " | INCASARI: " << Formatare::formatareMoneda(calculeazaIncasariTotale());
	}

	std::cout << "\n";
}
