#include "../headers/Zbor.h"
#include "../headers/CompanieAeriana.h"
#include "../headers/Exceptii.h"
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
	// trebuie sa aiba 2-3 caractere
    if (poartaNoua.length() < 2 || poartaNoua.length() > 3) {
        return false;
    }
	// primul caracter trebuie sa fie litera mare
    if (!std::isupper(poartaNoua[0])) {
	    return false;
    }
	// toate celelalte caractere sunt cifre
    for (size_t i = 1; i < poartaNoua.length(); i++) {
        if (!isdigit(poartaNoua[i])) {
            return false;
        }
    }
    return true;
}

bool Zbor::exitaPasager(const std::string& nume) const {
	for (const auto& pasager : this->listaPasageri) {
		if (toUpperCase(pasager.getNume()) == toUpperCase(nume)) {
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
	if (this->exitaPasager(p.getNume())) {
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
    	if (pasager.getBilet() != nullptr) {
    		total += pasager.getBilet()->getPretFinal();
    	}
    }
    return total;
}
Pasager* Zbor::cautaPasagerDupaNume(const std::string& nume){
   for (auto& pasager : this->listaPasageri) {
	   if (toUpperCase(pasager.getNume()) == toUpperCase(nume)) {
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
	const BiletFirstClass* firstclass = dynamic_cast<const BiletFirstClass*>(biletVechi);

	Bilet* biletNou = nullptr;

	if (economic != nullptr) {
		std::cout << "\n=== UPGRADE: Economic -> Business ===\n";
		std::cout << "Pret actual: " << economic->getPretFinal() << " EUR\n";

		bool accesLounge;
		std::cout << "Acces lounge (1-DA/0-NU):";
		std::cin >> accesLounge;

		biletNou = new BiletBusiness (
			biletVechi->getLoc(),
			biletVechi->getPretBaza() + 50.0, // + taxa upgrade
			biletVechi->getDiscountProcent(),
			accesLounge
			);

		std::cout << "Pret nou: " << biletNou->getPretFinal() << " EUR\n";
		std::cout << "Diferenta: +" << (biletNou->getPretFinal() - economic->getPretFinal()) << " EUR\n";
	} else if (business != nullptr) {
		std::cout << "\n=== UPGRADE: Business -> First Class ===\n";
		std::cout << "Pret actual: " << business->getPretFinal() << " EUR\n";

		bool servireMasa, prioritate;
		std::cout << "Servire masa (1-DA/0-NU):";
		std::cin >> servireMasa;
		std::cout << "Prioritate (1-DA/0-NU):";
		std::cin >> prioritate;

		biletNou = new BiletFirstClass (
			biletVechi->getLoc(),
			biletVechi->getPretBaza() + 100.0, // + taxa upgrade
			biletVechi->getDiscountProcent(),
			servireMasa,
			prioritate
			);

		std::cout << "Pret nou: " << biletNou->getPretFinal() << " EUR\n";
		std::cout << "Diferenta: +" << (biletNou->getPretFinal() - business->getPretFinal()) << " EUR\n";
	} else if (firstclass != nullptr) {
		std::cout << "\n[INFO] Biletul este deja First Class - nivel maxim!\n";
		std::cout << "Nu este posibil un upgrade ulterior.\n";
		return false;
	}

	if (biletNou != nullptr) {
		pasager->setBilet(biletNou);
		delete biletNou;
		std::cout << "Upgrade realizat cu succes!\n";
		return true;
	}
	return true;
}

void Zbor::afiseazaLocuriOcupate() const {
	std::cout << "----Locuri Ocupate---- ";
	for (const auto& pasager: this->listaPasageri) {
		const Bilet* bilet = pasager.getBilet();
		if (bilet != nullptr) {
			std::cout << bilet->getLoc() << " ";
		}
	}
	std::cout << "\n";
}
bool Zbor::esteLocOcupat(const std::string& loc, const std::string& numeDeExclus) const {
	for (const auto& pasager : this->listaPasageri) {
		if (pasager.getNume() == numeDeExclus) {
			continue;
		}
		const Bilet* bilet = pasager.getBilet();
		if (bilet != nullptr && bilet->getLoc() == loc) {
			return true;
		}
	}
	return false;
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
