#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Zbor.h"
#include "Utils.h"

class SortStrategy {
public:
	virtual void sorteaza(std::vector<Zbor>& zboruri) const = 0;
	virtual std::string getNume() const = 0;
	virtual ~SortStrategy() = default;
};

class SortByDestinatie : public SortStrategy {
public:
	void sorteaza(std::vector<Zbor>& zboruri) const override {
		std::sort(zboruri.begin(), zboruri.end(), [](const Zbor& a, const Zbor& b) {
			return toUpperCase(a.getDestinatie()) < toUpperCase(b.getDestinatie());
		});
	}
	std::string getNume() const override {
		return "Sortare dupa destinatie (alfabetic)";
	}
};

class SortByOcupare : public SortStrategy {
public:
	void sorteaza(std::vector<Zbor>& zboruri) const override {
		std::sort(zboruri.begin(), zboruri.end(), [](const Zbor& a, const Zbor& b) {
			double rataA = static_cast<double>(a.getLocuriOcupate()) / a.getCapacitateMaxima();
			double rataB = static_cast<double>(b.getLocuriOcupate()) / b.getCapacitateMaxima();
			return rataA > rataB;
		});
	}
	std::string getNume() const override {
		return "Sortare dupa ocupare (descrescator)";
	}

};

class SortByIncasari : public SortStrategy{
public:
	void sorteaza(std::vector<Zbor>& zboruri) const override {
		std::sort(zboruri.begin(), zboruri.end(), [](const Zbor& a, const Zbor& b) {
			return a.calculeazaIncasariTotale() > b.calculeazaIncasariTotale();
		});
	}
	std::string getNume() const override {
		return "Sortare dupa incasari (descrescator)";
	}
};


