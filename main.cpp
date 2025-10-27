#include <iostream>
#include <iomanip>
#include "Bilet.h"
#include "Pasager.h"
#include "Zbor.h"
#include "CompanieAeriana.h"

void populareDate(CompanieAeriana& companie) {
    std::cout << "---POPULARE DATE---";

    Zbor z1("RO123", "Paris", "A12", 5);
    Zbor z2("RO456", "Londra", "B5", 4);
    Zbor z3("RO789", "Berlin", "C20", 3);

    Bilet b1("14A", "Economic", 150.0);
    Bilet b2("1F", "Business", 350.5);
    b2.aplicaDiscount(10);
    Bilet b3("22C", "Economic", 120.6);

    Pasager p1("Iustina Caramida", "i.caramida@gmail.com", b1);
    Pasager p2("Costin Sin", "c.sin@gmail.com", b2);
    Pasager p3("Tudor Deaconu", "tudor.d@gmail.com", b3);

    z1.adaugaPasager((p1));
    z1.adaugaPasager((p2));
    z2.adaugaPasager((p3));

    companie.adaugaZbor(z1);
    companie.adaugaZbor(z2);
    companie.adaugaZbor(z3);

    std::cout <<"S-au implementat datele!\n";
}

int main() {
    CompanieAeriana companie("Wizz");
    populareDate(companie);

    int optiune;
    while (true) {
        std::cout << "\n---MENIU---\n";
        std::cout << "1. Afiseaza date companie\n";
        std::cout << "2. Adauga zbor\n";
        std::cout <<"3. Cauta zbor\n";
        std::cout << "0. Iesire\n";
        std::cout <<"Optiune: ";
        std::cin >> optiune;

        if (optiune == 0) {
            break;
        }
        if (optiune == 1) {
            std::cout << "\n" << companie << "\n";
        }
        if (optiune == 2) {
            std::string numar, destinatie, poarta;
            int cap;
            std::cout <<"Numar zbor: "; std::cin >> numar;
            std::cout <<"Destinatie: "; std::cin >> destinatie;
            std::cout <<"Poarta: "; std::cin >> poarta;
            std::cout <<"Capacitate: "; std::cin >> cap;

            Zbor z(numar, destinatie, poarta, cap);
            companie.adaugaZbor(z);
            std::cout << "Zbor adaugat cu succes!\n";
        }
        if (optiune == 3) {
            std::string numar;
            std::cout <<"Numar zbor: "; std::cin >> numar;

            Zbor *z = companie.cautaZborDupaNumar(numar);
            if (z != NULL) {
                std::cout << "\n" << *z << "\n";
            } else {
                std::cerr << "\nZbor negasit!\n";
            }
        }
    }


}