#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Zbor.h"

class CompanieAeriana {
private:
    std::string numeCompanie;
    std::vector<Zbor> flotaZboruri;                                 // stocam toate obiectele zbor care apartin companiei

    bool esteZborDuplicat(const std::string &numarZbor) const;

public:
    CompanieAeriana();

    CompanieAeriana(const std::string &nume); // Cu parametri


    std::string getNumeCompanie() const;

    void adaugaZbor(const Zbor &z);

    Zbor *cautaZborDupaNumar(const std::string &numarZbor);

    friend std::ostream &operator<<(std::ostream &COUT, const CompanieAeriana &c);
}
;