#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Zbor.h"

inline std::string toUpperCase(const std::string& s) {
	std::string result = s;
	std::transform(result.begin(), result.end(), result.begin(),
				   [](unsigned char c){ return std::toupper(c); });
	return result;
}


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