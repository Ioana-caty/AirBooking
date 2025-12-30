#include "../headers/Bilet.h"
#include "../headers/CompanieAeriana.h"
#include "../headers/Exceptii.h"
#include "../headers/Utils.h"
#include <iomanip>
#include <iostream>

int Bilet::counterID = 1000; // se incepe de la 1000
const double Bilet::TAXA_AEROPORT = 15.75;
const double BiletEconomic::TAXA_EXTRA = 3.0;
const double BiletBusiness::TAXA_CONFORT = 35.5;
const double BiletFirstClass::TAXA_LUXURY = 74.75;

// BILET:
Bilet::Bilet() : biletID(counterID++), loc("N/A"), pretBaza(0.0), discountProcent (0.0) {}

Bilet::Bilet(const std::string &Loc, double pretBaza, int discountProcent)
				: biletID(counterID++), loc(Loc), pretBaza(pretBaza >= 0 ? pretBaza : 0.0), discountProcent (discountProcent) {

	if (this->discountProcent < 0 || this->discountProcent > 80) {
		throw ExceptieValidare("Discount invalid: " + std::to_string(discountProcent) + "% (permis: 0-80%)");
	}

	if (!esteLocValid(Loc)) {
		throw ExceptieValidare("Loc invalid: " + Loc + " (format: 1-2 cifre + litera, ex: 12A)");
	}
	this->loc = Loc;

	if (pretBaza < 0) {
		throw ExceptieValidare("Pret invalid: " + std::to_string(pretBaza) + " EUR (trebuie >= 0)");
	}
}

Bilet::Bilet(const Bilet &other) : biletID(other.biletID), loc(other.loc), pretBaza(other.pretBaza), discountProcent(other.discountProcent) {}

Bilet & Bilet::operator=(const Bilet &other) {
	if (this == &other) {
		return *this;
	}

	this->biletID = other.biletID;
	this->loc = other.loc;
	this->pretBaza = other.pretBaza;
	this->discountProcent = other.discountProcent;
	this->counterID = other.counterID;

	return *this;
}

bool Bilet::esteLocValid(const std::string &Loc) {
	return esteFormatValid(Loc, true);
}

bool Bilet::setLoc(const std::string &nouLoc) {
	if (this->esteLocValid(toUpperCase(nouLoc))) {
		this->loc = toUpperCase(nouLoc);
		return true;
	} else {
		return false;
	}
}

std::ostream & operator<<(std::ostream &COUT, const Bilet &b) {
	COUT	<< "Bilet [ID: " << b.biletID
			<< ", Loc: " << b.loc
			<< ", Clasa: " << b.getTipClasa()
			<< ", Pret Final: ";
	if (b.pretBaza <= 0) {
		std::cout << "N/A";
	} else {
		COUT << Formatare::formatareMoneda(b.getPretFinal());
	}

	return COUT;
}
Bilet::~Bilet() {}

// ECONOMIC:
BiletEconomic::BiletEconomic() :
	Bilet() {}
BiletEconomic::BiletEconomic(const std::string &Loc, double pretBaza, int discountProcent) :
	Bilet(Loc, pretBaza, discountProcent) {}

double BiletEconomic::getPretFinal() const {
	const double pretCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT + BiletEconomic::TAXA_EXTRA;
	double discount = 0.0;
	if (this->discountProcent > 0) {
		discount = pretCuTaxe * (static_cast<double>(this->discountProcent) / 100.0);
	}
	return pretCuTaxe - discount;
}

std::string BiletEconomic::getTipClasa() const { return "Economic"; }
Bilet* BiletEconomic::clone() const { return new BiletEconomic(*this); }

Bilet* BiletEconomic::creeazaUpgrade() const {
	bool bautura, prioritate;
	std::cout << "\nConfigurare Upgrade la PREMIUM:\n";
	std::cout << "Bautura gratuita (1-DA/0-NU): "; std::cin >> bautura;
	std::cout << "Prioritate imbarcare (1-DA/0-NU): "; std::cin >> prioritate;

	// Crestem pretul de baza cu 40.0 pentru acest salt
	return new BiletPremium(this->loc, this->pretBaza + 40.0, this->discountProcent, bautura, prioritate);
}
BiletEconomic::~BiletEconomic() {}
// BUSINESS:
BiletBusiness::BiletBusiness() :
	Bilet(), accesLounge(true) {}

BiletBusiness::BiletBusiness(const std::string &Loc, double pretBaza, int discountProcent, bool accesLounge) :
	Bilet(Loc, pretBaza, discountProcent), accesLounge(accesLounge) {}

double BiletBusiness::getPretFinal() const {
	double pretCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT + BiletBusiness::TAXA_CONFORT;
	if (this->accesLounge) {
		pretCuTaxe += 20.0;
	}
	double discount = 0.0;
	if (this->discountProcent > 0) {
		discount = pretCuTaxe * (static_cast<double>(this->discountProcent) / 100.0);
	}
	return pretCuTaxe - discount;
}

std::string BiletBusiness::getTipClasa() const { return "Business"; }
Bilet * BiletBusiness::clone() const { return new BiletBusiness(*this); }
Bilet* BiletBusiness::creeazaUpgrade() const {
	bool servireMasa, prioritateFC;
	std::cout << "\nConfigurare Upgrade la FIRST CLASS:\n";
	std::cout << "Servire masa (1-DA/0-NU): "; std::cin >> servireMasa;
	std::cout << "Prioritate (1-DA/0-NU): "; std::cin >> prioritateFC;

	return new BiletFirstClass(this->loc, this->pretBaza + 100.0, this->discountProcent, servireMasa, prioritateFC);
}
BiletBusiness::~BiletBusiness() {}

// FIRST CLASS:
BiletFirstClass::BiletFirstClass() :
	Bilet(), servireMasa(true), prioritateImbracare(true) {}
BiletFirstClass::BiletFirstClass(const std::string &Loc, double pretBaza, int discountProcent, bool servireMasa, bool prioritateImbarcare) :
	Bilet(Loc, pretBaza, discountProcent), servireMasa(servireMasa), prioritateImbracare(prioritateImbarcare) {}

double BiletFirstClass::getPretFinal() const {
	double pretCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT + BiletFirstClass::TAXA_LUXURY;
	if (this->servireMasa) {
		pretCuTaxe += 45.0;
	}
	if (this->prioritateImbracare) {
		pretCuTaxe += 25.0;
	}
	double discount = 0.0;
	if (this->discountProcent > 0) {
		discount = pretCuTaxe * (static_cast<double>(this->discountProcent) / 100.0);
	}
	return pretCuTaxe - discount;
}

std::string BiletFirstClass::getTipClasa() const { return "FirstClass"; }
Bilet * BiletFirstClass::clone() const { return new BiletFirstClass(*this); }
Bilet* BiletFirstClass::creeazaUpgrade() const {
	return nullptr;
}
BiletFirstClass::~BiletFirstClass() {}

// BILET PREMIUM:
const double BiletPremium::TAXA_PREMIUM = 45.0;

BiletPremium::BiletPremium() : Bilet(), bautura(true), prioritate(true) {}

BiletPremium::BiletPremium(const std::string& Loc, double pretBaza, int discountProcent, bool bautura, bool prioritate):
	Bilet(Loc, pretBaza, discountProcent), bautura(bautura), prioritate(prioritate) {}

double BiletPremium::getPretFinal() const {
	double pretCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT + BiletPremium::TAXA_PREMIUM;
	if (this->bautura) {
		pretCuTaxe += 10.0;
	}
	if (this->prioritate) {
		pretCuTaxe += 14.0;
	}
	double discount = 0.0;
	if (this->discountProcent > 0) {
		discount = pretCuTaxe * (static_cast<double>(this->discountProcent) / 100.0);
	}
	return pretCuTaxe - discount;
}

std::string BiletPremium::getTipClasa() const { return "Premium"; }
Bilet* BiletPremium::clone() const { return new BiletPremium(*this); }
Bilet* BiletPremium::creeazaUpgrade() const {
	bool accesLounge;
	std::cout << "\nConfigurare Upgrade la BUSINESS:\n";
	std::cout << "Acces lounge (1-DA/0-NU): "; std::cin >> accesLounge;

	return new BiletBusiness(this->loc, this->pretBaza + 30.0, this->discountProcent, accesLounge);
}
BiletPremium::~BiletPremium() {}