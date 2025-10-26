#include "Pasager.h"
#include <iostream>
#include <cstring>

int Pasager::counterID = 0;

//Constructor de Initializare
Pasager::Pasager(const char* nume, std::string email, const Bilet& bilet)
: email(email), bilet(bilet) {

    this->nume = new char[strlen(nume) + 1];    // alocam memorie noua pe heap
    strcpy(this->nume, nume);                   // copiem continutul

    this->pasagerID = counterID++;
}

//Constructor default
Pasager::Pasager() {
    this->nume = new char[strlen("not_specifying") + 1];
    strcpy(this->nume, "not_specifying");
    this->email = "none@gmail.com";
    this->pasagerID = counterID++;
}

// Destrcutor
Pasager::~Pasager() {
    //std::cout << "Destructor" << std::endl;
    delete[] this->nume;
    this->nume = nullptr;
}

// Construcor de copiere
Pasager::Pasager(const Pasager& another) {
    this->nume = new char[strlen(another.nume) + 1];
    strcpy(this->nume, another.nume);
    this->email = another.email;
    this->pasagerID = another.pasagerID;
    this->bilet = another.bilet;
}

// Operator Atribuire
Pasager& Pasager::operator=(const Pasager &another) {
    // verificam auto-atribuirea, daca nu delete[] this->nume are sterge datele inainte sa le copiem
    if (this == &another) {
        return *this;
    }

    // curatam resursele vechi ale obiectului curent
    delete[] this->nume;

    // alocam resurse noi si copiem
    this->nume = new char[strlen(another.nume) + 1];
    strcpy(this->nume, another.nume);
    this->email = another.email;
    this->bilet = another.bilet;

    //returnam obiectul curent
    return *this;
}

//Getter
const char* Pasager::getNume() const{
    return this->nume;
}

const Bilet Pasager::getBilet() const {
    return this->bilet;
}

//Setter
void Pasager::setBilet(const Bilet& Bilet) {
    this->bilet = Bilet;
}

std::ostream& operator<<(std::ostream& COUT, const Pasager& p) {
    COUT    << "Pasager [ID: " << p.pasagerID
            << ",Nume: " << p.nume
            << ",Email: " << p.email << "]"
            << std:: endl;
    COUT    << p.bilet;
    return COUT;
}
