#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include "Bilet.h"

class Pasager {
private:
    char* nume;             // la pointer noi suntem responsabili pentru memorie
    std::string email;      // string normal
    int pasagerID;          // D unic
    static int counterID;   // contor global pentru a da ID-urile unice && este pt toate obiectele Pasager

    Bilet bilet;            // Obiect memebru

public:
    Pasager(const char* nume, std::string email, const Bilet& bilet);   // constructor de cu parametri
    Pasager();                                                          // constructor default

    virtual ~Pasager();                                                 // destructor
    Pasager(const Pasager& another);                                    // constructor de copiere, Construieste un obiect nou si nu doar o copie a altuia
    Pasager& operator=(const Pasager& another);                         // constructor de atribuire, Copiaza datele dintr-un obiect existent in alt obiect deja existent

    const char* getNume() const;                                        // getter
    const Bilet getBilet()const;                                              // getter pentru Bilet

    void setBilet(const Bilet& bilet);                                  //setter pentru bilet

    friend std::ostream& operator<<(std::ostream&os, const Pasager& p);
};