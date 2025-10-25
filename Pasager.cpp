#include "Pasager.h"
#include <iostream>
#include <cstring>

int Pasager::counterID = 1000;

//Constructor de Initializare
Pasager::Pasager(const char* nume, std::string email) {
    this->nume = new char[strlen(nume) + 1];    // alocam memorie noua pe heap
    strcpy(this->nume, nume);                   // copiem continutul
    this->email = email;
    this->pasagerID = counterID++;
    std::cout << "DEBUG: Constructor cu parametrii pelat pentru: " << this->nume << "\n";
}

//Constructor de copiere
Pasager::Pasager() {
    this->nume = new char[strlen("not_specifying") + 1];
    strcpy(this->nume, "not_specifying");
    this->email = "none@gmail.com";
    this->pasagerID = counterID++;
    std::cout <<"DEBUG: Constructor Default Pasager() apelat \n";
}

// Destrcutor
Pasager::~Pasager() {
    std::cout << "DEBUG: Destructor apelat pentru: " << this->nume << "\n";
    delete[] this->nume;
}

// Construcor de copiere
Pasager::Pasager(const Pasager& another) {
    this->nume = new char[strlen(another.nume) + 1];
    strcpy(this->nume, another.nume);
    this->email = another.email;
    this->pasagerID = counterID++;
    std::cout << "DEBUG: Copy Constructor apelat (a creat: " << this->nume << "\n";
}

Pasager &Pasager::operator=(const Pasager &another) {
    std::cout << "Debug Operator= apelat (" << this->nume << "devine" << another.nume << ")\n";

    if (this == &another) {
        return *this;
    }
    delete[] this->nume;
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
    COUT << "Pasager (ID " << p.pasagerID << "): " << p.nume << " [" << p.email << "]";
    return COUT;
}
