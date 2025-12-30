#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Zbor.h"
#include "Utils.h"

class CompanieAeriana {
private:
    std::string numeCompanie;
    std::vector<Zbor> flotaZboruri;

    bool esteZborDuplicat(const std::string& numarZbor) const;

public:
    CompanieAeriana();
    explicit CompanieAeriana(const std::string& nume);

    bool adaugaZbor(const Zbor& z);
    Zbor *cautaZborDupaNumar(const std::string& numarZbor);

	void sorteazaZboruriDupaDestinatie();
	void sorteazaZboruriDupaOcupare();
	void sorteazaZboruriDupaIncasari();
	std::vector<Zbor*> filtreazaZboruriPline();
	std::vector<Zbor*> filtreazaZboruriGoale();
	std::vector<Zbor*> cautaZboruriDupaDestinatie(const std::string& dest);

    friend std::ostream& operator<<(std::ostream& COUT, const CompanieAeriana& c);
	void afisareFaraPasageri(bool incasari) const;
	friend void saveData(const CompanieAeriana& companie, const std::string& numeFisier);
};