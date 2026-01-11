#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Zbor.h"
#include "SortStrategy.h"
#include "Utils.h"

class CompanieAeriana {
private:
    std::string numeCompanie;
    std::vector<Zbor> flotaZboruri;
	std::shared_ptr<SortStrategy> sortStrategy;

	bool esteZborDuplicat(const std::string& numarZbor) const;
public:
    CompanieAeriana();
    explicit CompanieAeriana(const std::string& nume);

    bool adaugaZbor(const Zbor& z);
    Zbor *cautaZborDupaNumar(const std::string& numarZbor);

	void setSortStrategy(std::shared_ptr<SortStrategy> s);
	void sorteazaZboruri();
	// void sorteazaZboruriDupaDestinatie();
	// void sorteazaZboruriDupaOcupare();
	// void sorteazaZboruriDupaIncasari();
	std::vector<Zbor*> filtreazaZboruriPline();
	std::vector<Zbor*> filtreazaZboruriGoale();
	std::vector<Zbor*> cautaZboruriDupaDestinatie(const std::string& dest);

    friend std::ostream& operator<<(std::ostream& COUT, const CompanieAeriana& c);
	void afisareFaraPasageri(bool incasari) const;
	friend void saveData(const CompanieAeriana& companie, const std::string& numeFisier);
};