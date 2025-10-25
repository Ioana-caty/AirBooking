#pragma once
#include <iostream>
#include <string>

class Pasager {
private:
    char* nume;             // la pointer noi suntem responsabili pentru memorie
    std::string email;      // string normal
    int pasagerID;          // D unic
    static int counterID;    // contor global pentru a da ID-urile unice && este pt toate obiectele Pasager
public:
    Pasager(const char* nume, std::string email);   // constructor de initalizare
    Pasager();                                      // constructor default
    virtual ~Pasager();                             // destructor
    Pasager(const Pasager& another);                // constructor de copiere, Construieste un obiect nou si nu doar o copie a altuia
    Pasager& operator=(const Pasager& another);     // constructor de atribuire, Copiaza datele dintr-un obiect existent in alt obiect deja existent

    std::string getEmail() const;
    const char* getNume() const;

    friend std::ostream& operator<<(std::ostream&os, const Pasager& p);
};