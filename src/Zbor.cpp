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

	const BiletEconomic* economic = dynamic_cast<const BiletEconomic*>(biletVechi);
	const BiletBusiness* business = dynamic_cast<const BiletBusiness*>(biletVechi);
	const BiletPremium* premium = dynamic_cast<const BiletPremium*>(biletVechi);
	const BiletFirstClass* firstclass = dynamic_cast<const BiletFirstClass*>(biletVechi);

	Bilet* biletNou = nullptr;

	if (economic != nullptr) {
		std::cout << "\n=== UPGRADE: Economic -> Premium ===\n";
		std::cout << "Pret actual: " << Formatare::formatareMoneda(economic->getPretFinal())<< "\n";

		bool bautura, prioritate;
		std::cout << "Bautura gratuita (1-DA/0-NU): ";
		std::cin >> bautura;
		std::cout << "Prioritate imbarcare (1-DA/0-NU): ";
		std::cin >> prioritate;

		biletNou = new BiletPremium(
			biletVechi->getLoc(),
			biletVechi->getPretBaza() + 40.0,
			biletVechi->getDiscountProcent(),
			bautura,
			prioritate
		);

		std::cout << "Pret nou: " << Formatare::formatareMoneda(biletNou->getPretFinal()) << "\n";
		std::cout << "Diferenta: +" << Formatare::formatareMoneda((biletNou->getPretFinal() - economic->getPretFinal())) << "\n";

	} else if (premium != nullptr) {
		std::cout << "\n=== UPGRADE: Premium -> Business ===\n";
		std::cout << "Pret actual: " << Formatare::formatareMoneda(premium->getPretFinal()) << "\n";

		bool accesLounge;
		std::cout << "Acces lounge (1-DA/0-NU): ";
		std::cin >> accesLounge;

		biletNou = new BiletBusiness(
			biletVechi->getLoc(),
			biletVechi->getPretBaza() + 30.0,
			biletVechi->getDiscountProcent(),
			accesLounge
		);

		std::cout << "Pret nou: " << Formatare::formatareMoneda(biletNou->getPretFinal()) << "\n";
		std::cout << "Diferenta: +" << Formatare::formatareMoneda(biletNou->getPretFinal() - premium->getPretFinal()) << "\n";

	} else if (business != nullptr) {
		std::cout << "\n=== UPGRADE: Business -> First Class ===\n";
		std::cout << "Pret actual: " << Formatare::formatareMoneda(business->getPretFinal()) << "\n";

		bool servireMasa, prioritate;
		std::cout << "Servire masa (1-DA/0-NU):";
		std::cin >> servireMasa;
		std::cout << "Prioritate (1-DA/0-NU):";
		std::cin >> prioritate;

		biletNou = new BiletFirstClass(
			biletVechi->getLoc(),
			biletVechi->getPretBaza() + 100.0,
			biletVechi->getDiscountProcent(),
			servireMasa,
			prioritate
		);

		std::cout << "Pret nou: " << Formatare::formatareMoneda(biletNou->getPretFinal()) << "\n";
		std::cout << "Diferenta: +" << Formatare::formatareMoneda(biletNou->getPretFinal() - business->getPretFinal()) << "\n";

	} else if (firstclass != nullptr) {
		std::cout << "\n[INFO] Biletul este deja First Class - nivel maxim!\n";
		std::cout << "Nu este posibil un upgrade ulterior.\n";
		return false;
	}

	if (biletNou != nullptr) {
		pasager->actualizeazaBilet(biletNou);
		delete biletNou;
		UI::mesajSucces("Upgrade realizat cu succes!");
		return true;
	}
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


bool Zbor::operator<(const Zbor& other) const {
	// rdupa rata de ocupare
	double rataMea = (double)getLocuriOcupate() / capacitateMaxima;
	double rataLui = (double)other.getLocuriOcupate() / other.capacitateMaxima;
	return rataMea < rataLui;
}

bool Zbor::operator>(const Zbor& other) const {
	// dupa incasari
	return calculeazaIncasariTotale() > other.calculeazaIncasariTotale();
}