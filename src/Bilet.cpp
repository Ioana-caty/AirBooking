#include "../headers/Bilet.h"
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

	// validare pentru discount
	if (this->discountProcent < 0 || this->discountProcent > 80) {
		this->discountProcent = 0;
	}

	// validare si setarea locului
	if (esteLocValid(Loc)) {
		this->loc = Loc;
	} else {
		std::cerr	<< "\nEROARE: Locul: " << Loc << " este invalid!\n"
					<< "Format: cifre (1-2) + litera mare (ex: 12A, 5F)\n";
		this->loc = "N/A";
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
	// trebuie sa aiba 2-3 caractere
	if (Loc.length() < 2 || Loc.length() > 3) {
		return false;
	}
	// ultima litera trebuia sa fie majuscula
	char ultimaLitera = Loc.back();
	if (!std::isupper(ultimaLitera)) {
		return false;
	}
	// toate caracterele inainte de ultima litera trebuie sa fie cifre
	for (size_t i = 0; i < Loc.length() - 1; i++) {
		if (!std::isdigit(Loc[i])) {
			return false;
		}
	}
	return true;
}

void Bilet::setLoc(const std::string &nouLoc) {
	if (Bilet::esteLocValid(nouLoc)) {
		this->loc = nouLoc;
	}
}

bool Bilet::isWindowSeat() const {
	if (this->loc == "N/A") {
		return false ;
	} else {
		char litera = this->loc.back();
		return toupper(litera) == 'A' || toupper(litera) == 'F';
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
		COUT << std::fixed << std::setprecision(2) << b.getPretFinal() << " EUR]";
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

BiletFirstClass::~BiletFirstClass() {}