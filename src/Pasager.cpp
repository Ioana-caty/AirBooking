#include "../headers/Pasager.h"
#include <iostream>

int Pasager::counterID = 0;

Pasager::Pasager(const std::string& nume, const std::string& Email, const Bilet& biletNou)
    : nume(nume),
      email(Email),
      pasagerID(counterID++),
      bilet(biletNou) {
}

Pasager::Pasager()
    : nume("not_specified"),
      email("none@gmail.com"),
      pasagerID(counterID++),
      bilet() {
}


Pasager::~Pasager() {
}

Pasager::Pasager(const Pasager& another)
    : nume(another.nume),
      email(another.email),
      pasagerID(another.pasagerID),
      bilet(another.bilet) {
}

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

const Bilet& Pasager::getBilet() const {
    return this->bilet;
}

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