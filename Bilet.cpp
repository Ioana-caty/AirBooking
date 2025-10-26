#include "Bilet.h"
#include <iomanip>
#include <iostream>

int Bilet::counterID = 1000;
const double Bilet::TAXA_AEROPORT = 15.75;
/*
    NU AVEM  Constructor de copiere && atribuitre && Destrcutor
    pentru ca nu avem pointer sau resurse dinamice in clasa
    C++ poate genera automat
*/

// Constructor Default
Bilet::Bilet() {
    this->loc = "N/A";
    this->tipClasa = "N/A";
    this->pretBaza = 0.0;
    this->discountProcent = 0;
    this->biletID = counterID++; //generam ID unic
}

// Constructor cu parametri
Bilet::Bilet(const std::string& nouLoc, const std::string& tipClasa, double pretBaza) {
    this->loc = nouLoc;
    this->tipClasa = tipClasa;
    this->pretBaza = pretBaza;
    this->discountProcent = 0;

    if (pretBaza < 0) {
        this->pretBaza = 0;
    }

    this->biletID = counterID++;
}

// Functie privata
bool Bilet::esteLocValid(const std::string &loc) const {
    return loc.length() >= 2 && loc.length() <= 3;
}

// Getters

std::string Bilet::getLoc() const {
    return this->loc;
}



int Bilet::getDiscountProcent() const {
    return this->discountProcent;
}

//Setters
void Bilet::setLoc(const std:: string& nouLoc) {
    if (this->esteLocValid(nouLoc)) {
        this->loc = nouLoc;
    } else {
        std::cerr << "Eroare: Locul '" << nouLoc << "' este invalid!!" << std::endl;
        this->loc = "N/A";
    }
}



//Implementare functii netriviale

// Aplicare discount
void Bilet::aplicaDiscount(int procent) {
    if (procent >= 0 && procent <= 80) {
        this->discountProcent = procent;
        std::cout << "\nDiscount de " << procent << " aplicat biletului " << this->biletID << std::endl;
    } else {
        std::cerr << "Eroare: Discountul (" << procent << ") trebuie sa fie intr 1 si 80." << std::endl;
    }
}

// Calculare pret final
double Bilet::getPretFinal() const {
    const double pretCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT;
    const double valoareDiscount = pretCuTaxe * ((double)(this->discountProcent) / 100.0);
    if (valoareDiscount > pretCuTaxe)
        std::cerr << "Eroare: Discountul nu poate sa fie mai mare decat pretul cu taxe!" << std::endl;
    return pretCuTaxe - valoareDiscount;
}


// Verifica daca codul este la geam
bool Bilet::isWindowSeat() const {
    if (this->loc == "N/A") {
        return false;
    } else {
        char literaLoc = this ->loc.back(); // returneaza ultimul caracter
        return toupper(literaLoc) == 'A' || toupper(literaLoc) == 'F';
    }
}

std::ostream& operator<<(std::ostream& COUT, const Bilet& b) {
    COUT <<"Bilet [ID: " << b.biletID
    << ", Loc: " << b.loc
    << ", Clasa: " << b.tipClasa
    << ", Pret Final: ";

    if (b.pretBaza <= 0) {
        COUT << "N/A";
    } else {
        COUT << std::fixed << std::setprecision(2) << b.getPretFinal() << "EUR]";
    }
    return COUT;
}



