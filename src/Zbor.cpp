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

bool Zbor::exitaPasager(const std::string& nume) const {
	for (const auto& pasager : this->listaPasageri) {
		if (pasager.getNume() == nume) {
			return true;
		}
	}
	return false;
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
	if (this->exitaPasager(p.getNume())) {
		std::cerr	<< "\n!!! EROARE: Pasagerul '" << p.getNume()
					<< "' a fost deja inregistrat.\n";
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
   for (auto& pasager : this->listaPasageri) {
	   if (pasager.getNume() == nume) {
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
