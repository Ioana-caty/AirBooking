#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Zbor.h" // Clasa 'Zbor' este necesara pentru compunere

class CompanieAeriana {
private:
    std::string numeCompanie;
    std::vector<Zbor> flotaZboruri; // Compunere: O companie ARE o lista de zboruri

    // Functie helper privata
    bool esteZborDuplicat(const std::string& numarZbor) const;

public:
    CompanieAeriana();
    CompanieAeriana(const std::string& nume); // Cu parametri

    virtual ~CompanieAeriana();

    std::string getNumeCompanie() const;

    void adaugaZbor(const Zbor& z);

    Zbor* cautaZborDupaNumar(const std::string& numarZbor);

    friend std::ostream& operator<<(std::ostream& COUT, const CompanieAeriana& c);
};