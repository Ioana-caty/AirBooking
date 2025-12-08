#include "../headers/Pasager.h"
#include "../headers/CompanieAeriana.h"
#include "../headers/Exceptii.h"
#include "../headers/Utils.h"
#include <iostream>

int Pasager::counterID = 0;

Pasager::Pasager(const std::string &nume, const std::string &Email, Bilet *biletNou)
	: nume(toUpperCase(nume)), email(Email), pasagerID(counterID++), bilet(biletNou) {
}
Pasager::Pasager() : nume("not_specified"), email("none@gmail.com"), pasagerID(counterID++), bilet(nullptr) {
}

Pasager::Pasager(const Pasager &other) : nume(other.nume), email(other.email), pasagerID(other.pasagerID) {
	if (other.bilet != nullptr) {
		bilet = other.bilet->clone();
	} else {
		bilet = nullptr;
	}
}

Pasager &Pasager::operator=(const Pasager &other) {
	if (this == &other) {
		return *this;
	}

	this->nume = other.nume;
	this->email = other.email;
	this->pasagerID = other.pasagerID;

	delete this->bilet; // stergem biletul vechi
	this->bilet = nullptr; // pentru siguranta

	if (other.bilet != nullptr) {
		this->bilet = other.bilet->clone();
	} else {
		this->bilet = nullptr;
	}

	return *this;
}

bool Pasager::corespundeNumelui(const std::string& numeVerificat) const {
	return toUpperCase(nume) == toUpperCase(numeVerificat);
}

void Pasager::modificaLoc(const std::string& locNou) {
	if (bilet == nullptr) {
		throw ExceptieOperatie("Pasagerul nu are bilet!");
	}

	Bilet* biletNou = bilet->clone();
	if (!biletNou->setLoc(locNou)) {
		delete biletNou;
		throw ExceptieValidare("Format loc invalid: "+ locNou);
	}
	delete this->bilet;
	this->bilet = biletNou;

}

void Pasager::actualizeazaBilet(const Bilet *biletNou) {
	if (biletNou != nullptr) {
		delete this->bilet;
		this->bilet = biletNou->clone();
	} else {
		delete this->bilet;
		this->bilet = nullptr;
	}
}

void Pasager::incasari(double& total) const {
	if (bilet != nullptr) {
		total += bilet->getPretFinal();
	}
}

Pasager::~Pasager() {
	delete bilet; // fara el, atunci cand se sterge PAsagerul, biletul ramane
	bilet = nullptr;
}

std::ostream &operator<<(std::ostream &COUT, const Pasager &p) {
	COUT << "Pasager [ID: " << p.pasagerID
			<< ", Nume: " << p.nume
			<< ", Email: " << p.email << "]"
			<< std::endl;
	if (p.bilet != nullptr) {
		COUT << *(p.bilet);
	} else {
		COUT << "Bilet: N/A\n";
	}
	return COUT;
}