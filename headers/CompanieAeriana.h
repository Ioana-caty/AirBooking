#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Zbor.h"
#include "Utils.h"

class CompanieAeriana {
private:
    std::string numeCompanie;
    std::vector<Zbor> flotaZboruri; // stocam toate obiectele zbor care apartin companiei

    bool esteZborDuplicat(const std::string& numarZbor) const;

public:
    CompanieAeriana();
    explicit CompanieAeriana(const std::string& nume);

    bool adaugaZbor(const Zbor& z);
    Zbor *cautaZborDupaNumar(const std::string& numarZbor);

    friend std::ostream& operator<<(std::ostream& COUT, const CompanieAeriana& c);
	friend void saveData(const CompanieAeriana& companie, const std::string& numeFisier);
};