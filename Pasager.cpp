#include "Pasager.h"
#include <iostream>
#include <cstring>

int Pasager::counterID = 0;

//Constructor de Initializare
Pasager::Pasager(const char* nume, std::string email) {
    this->nume = new char[strlen(nume) + 1];    // alocam memorie noua pe heap
    strcpy(this->nume, nume);                   // copiem continutul
    this->email = email;
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
    std::cout << "Destructor" << std::endl;
    delete[] this->nume;
    this->nume = nullptr;
}

// Construcor de copiere
Pasager::Pasager(const Pasager& another) {
    this->nume = new char[strlen(another.nume) + 1];
    strcpy(this->nume, another.nume);
    this->email = another.email;
    this->pasagerID = counterID++;
}

// Operator Atribuire
Pasager& Pasager::operator=(const Pasager &another) {

    // verificam auto-atribuirea, daca nu delete[] this->nume are sterge datele inainte sa le copiem
    if (this == &another) {
        return *this;
    }

    // curatam resursel vechi ale obiectului curent
    delete[] this->nume;

    // alocam resurse noi si copiem
    this->nume = new char[strlen(another.nume) + 1];
    strcpy(this->nume, another.nume);
    this->email = another.email;

    return *this;
}

std::string Pasager::getEmail() const {
    return this->email;
}

const char* Pasager::getNume() const{
    return this->nume;
}

std::ostream& operator<<(std::ostream& COUT, const Pasager& p) {
    COUT    << "Pasager [ID: " << p.pasagerID
            << ",Nume: " << p.nume
            << ",Email: " << p.email << "]";
    return COUT;
}
