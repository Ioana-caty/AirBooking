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

Bilet::Bilet(const std::string &Loc, double pretBaza)
				: biletID(counterID++), loc(Loc), pretBaza(pretBaza >= 0 ? pretBaza : 0.0), discountProcent (0.0) {}

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
	return Loc.length() >= 2 && Loc.length() <= 3;
}

void Bilet::setLoc(const std::string &nouLoc) {
	if (Bilet::esteLocValid(nouLoc)) {
		this->loc = nouLoc;
	} else {
		std::cerr << "EROARE: Locul " << nouLoc << " este invalid!\n";
	}
}

void Bilet::aplicaDiscount(int procent) {
	if (procent >= 0 && procent <= 80) {
		this->discountProcent = procent;
		std::cout	<< " Discount de " << procent << "% aplicat biletului "
					<< this->biletID << std::endl;
	} else {
		std::cerr << "EROARE: Discountul " << procent << " trebuie sa fie intre 0 si 80!\n";
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
BiletEconomic::BiletEconomic(const std::string &Loc, double pretBaza) :
	Bilet(Loc, pretBaza) {}

double BiletEconomic::getPretFinal() const {
	const double pretCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT + BiletEconomic::TAXA_EXTRA;
	const double discount = pretCuTaxe * (static_cast<double> (this->discountProcent) / 100.0);
	return pretCuTaxe - discount;
}

std::string BiletEconomic::getTipClasa() const { return "Economic"; }
Bilet* BiletEconomic::clone() const { return new BiletEconomic(*this); }
BiletEconomic::~BiletEconomic() {}


// BUSINESS:
BiletBusiness::BiletBusiness() :
	Bilet(), accesLounge(true) {}

BiletBusiness::BiletBusiness(const std::string &Loc, double pretBaza, bool accesLounge) :
	Bilet(Loc, pretBaza), accesLounge(accesLounge) {}

double BiletBusiness::getPretFinal() const {
	double pretuCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT + BiletBusiness::TAXA_CONFORT;
	if (this->accesLounge) {
		pretuCuTaxe += 20.0;
	}
	const double discount = pretuCuTaxe + (static_cast<double> (this->discountProcent) / 100.0);
	return pretuCuTaxe - discount;
}

std::string BiletBusiness::getTipClasa() const { return "Business"; }
Bilet * BiletBusiness::clone() const { return new BiletBusiness(*this); }
BiletBusiness::~BiletBusiness() {}

// FIRSTA CLASS:

BiletFirstClass::BiletFirstClass() :
	Bilet(), servireMasa(true), prioritateImbracare(true) {}
BiletFirstClass::BiletFirstClass(const std::string &Loc, double pretBaza, bool servireMasa, bool prioritateImbarcare) :
	Bilet(Loc, pretBaza), servireMasa(servireMasa), prioritateImbracare(prioritateImbarcare) {}

double BiletFirstClass::getPretFinal() const {
	double pretCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT + BiletFirstClass::TAXA_LUXURY;
	if (this->servireMasa) {
		pretCuTaxe += 45.0;
	}
	if (this->prioritateImbracare) {
		pretCuTaxe += 25.0;
	}
	const double discount = pretCuTaxe + (static_cast<double>(this->discountProcent) / 100);
	return pretCuTaxe - discount;
}

std::string BiletFirstClass::getTipClasa() const { return "First Class"; }
Bilet * BiletFirstClass::clone() const { return new BiletFirstClass(*this); }

BiletFirstClass::~BiletFirstClass() {}