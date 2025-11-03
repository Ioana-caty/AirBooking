#include "../headers/Pasager.h"
#include <iostream>

int Pasager::counterID = 0;

//Constructor de Initializare
Pasager::Pasager(const std::string& nume, const std::string& Email, const Bilet& biletNou)
: nume(nume), email(Email), bilet(biletNou) {
    this->pasagerID = counterID++;
}

Pasager::Pasager() {
    this->nume = "not_specified";
    this->email = "none@gmail.com";
    this->pasagerID = counterID++;
}

Pasager::~Pasager() {
    // Nu mai e nevoie să ștergem nimic, std::string se ocupă automat
}

// Constructor de copiere
Pasager::Pasager(const Pasager& another) {
    this->nume = another.nume;
    this->email = another.email;
    this->pasagerID = another.pasagerID;
    this->bilet = another.bilet;
}

// Operator Atribuire
Pasager& Pasager::operator=(const Pasager& another) {
    // verificam auto-atribuirea
    if (this == &another) {
        return *this;
    }

    // copiem direct, std::string se ocupă de gestionarea memoriei
    this->nume = another.nume;
    this->email = another.email;
    this->pasagerID = another.pasagerID;
    this->bilet = another.bilet;

    return *this;
}

const std::string& Pasager::getNume() const {
    return this->nume;
}

const Bilet Pasager::getBilet() const {
    return this->bilet;
}

//Setter
void Pasager::setBilet(const Bilet& biletNou) {
    this->bilet = biletNou;
}

std::ostream& operator<<(std::ostream& COUT, const Pasager& p) {
    COUT    << "Pasager [ID: " << p.pasagerID
            << ",Nume: " << p.nume
            << ",Email: " << p.email << "]"
            << std:: endl;
    COUT    << p.bilet;
    return COUT;
}