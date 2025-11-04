#include "../headers/Bilet.h"
#include <iomanip>
#include <iostream>

int Bilet::counterID = 1000;
const double Bilet::TAXA_AEROPORT = 15.75;

/*
    NU AVEM:  Constructor de copiere && atribuitre && Destrcutor
    pentru ca nu avem pointer sau resurse dinamice in clasa
    C++ poate genera automat
*/

// Constructor Default
Bilet::Bilet()
    : loc("N/A"),
      tipClasa("N/A"),
      pretBaza(0.0),
      discountProcent(0),
      biletID(counterID++) {
}

Bilet::Bilet(const std::string& Loc, const std::string& tipClasa, double pretBaza)
    : loc(Loc),
      tipClasa(tipClasa),
      pretBaza(pretBaza >= 0 ? pretBaza : 0.0),
      discountProcent(0),
      biletID(counterID++) {
}

// Functie privata
bool Bilet::esteLocValid(const std::string &Loc) {
    return Loc.length() >= 2 && Loc.length() <= 3;
}

//Setter
void Bilet::setLoc(const std:: string& nouLoc) {
    // esteLocValid este o functie statica => nu folosim this->
    if (Bilet::esteLocValid(nouLoc)) {
        this->loc = nouLoc;
    } else {
        std::cerr << "Eroare: Locul '" << nouLoc << "' este invalid!!" << std::endl;
        this->loc = "N/A";
    }
}

void Bilet::aplicaDiscount(int procent) {
    if (procent >= 0 && procent <= 80) {
        this->discountProcent = procent;
        std::cout << "Discount de " << procent << " aplicat biletului " << this->biletID << std::endl;
    } else {
        std::cerr << "Eroare: Discountul (" << procent << ") trebuie sa fie intr 1 si 80." << std::endl;
    }
}

double Bilet::getPretFinal() const {
    const double pretCuTaxe = this->pretBaza + Bilet::TAXA_AEROPORT;
    const double valoareDiscount = pretCuTaxe * (static_cast<double>(this->discountProcent) / 100.0);
    /*
    (double)             C
    static_cast<double>  C++
    */
    if (valoareDiscount > pretCuTaxe)
        std::cerr << "Eroare: Discountul nu poate sa fie mai mare decat pretul cu taxe!" << std::endl;
    return pretCuTaxe - valoareDiscount;
}

// Verifica daca codul este la geam
bool Bilet::isWindowSeat() const {
    if (this->loc == "N/A") {
        return false;
    } else {
        char literaLoc = this ->loc.back();
        // .back() => returneaza ultimul caracter
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