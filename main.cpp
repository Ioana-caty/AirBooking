#include <iostream>
#include <string>       //std::string, std::getline
#include <limits>       //std::numaric_limits
#include <iomanip>      //std::setprecision

#include "CompanieAeriana.h"
#include "Zbor.h"
#include "Pasager.h"
#include "Bilet.h"

void curataBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int citesteInt(const std::string& prompt) {
    int val;
    std::cout << prompt;
    while (!(std::cin >> val)) {
        std::cout << "Input invalid. Introduceti un numar: ";
        std::cin.clear();
        curataBuffer();
    }
    curataBuffer();
    return val;
}
std::string citesteString(const std::string& prompt) {
    std::string val;
    std::cout << prompt;
    std::getline(std::cin, val);
    return val;
}

Bilet creeazaBilet() {
    std::cout << "--- CREARE BILET NOU --- \n";
    std::string loc = citesteString("Introduceti locul (ex: 11A): ");
    std::string tipClasa = citesteString("Introduceti clasa (Economic/Business): ");
    double pretBaza = citesteInt("Introduceti pretul de baza: ");

    Bilet b(loc, tipClasa, pretBaza);
    return b;
}

Pasager creeazaPasager() {
    std::cout << "--- CREARE PASAGER NOU --- \n";
    std::string nume = citesteString("Introduceti numele pasagerului: ");
    std::string email = citesteString("Introduceti email: ");

    // un pasager are un bilet, asa ca il cream
    Bilet b = creeazaBilet();

    // in constructor Pasager avem nume = const char*  => se foloseste .c_str:
    Pasager p(nume.c_str(), email, b);
    return p;
}

Zbor creeazaZbor() {
    std::cout << "--- CREARE ZBOR NOU --- \n";
    std::string numarZbor = citesteString("Introduceti nr. zbor (ex:RO255): ");
    std::string destinatie = citesteString("Introduceti destinatia: ");
    std::string poarta = citesteString("Introduceti poarta (ex:B12): ");
    int capacitateMaxima = citesteInt("Introduceti capacitatea maxima a zborului: ");

    Zbor z(numarZbor, destinatie, poarta, capacitateMaxima);
    return z;
}

Zbor* cautaZbor(CompanieAeriana& companie) {
    std::string nrZbor = citesteString("Introduceti numarul zborului: ");
    Zbor* zborGasit = companie.cautaZborDupaNumar(nrZbor);
    if (zborGasit == nullptr) {
        std::cout << "EROARE: Zborul '" << nrZbor << "' nu a fost gasit!.\n";
    }
    return zborGasit;
}


void afiseazaMeniu() {
    std::cout <<"TEST APLICATIE:" << std::endl;
    std::cout << "1.  Adauga zbor nou\n";
    std::cout << "2.  Cauta zbor dupa numar\n";
    std::cout << "3.  Adauga pasager la zbor\n";
    std::cout << "0.  Iesire\n";
    std::cout << "-------------------------\n";
    std::cout << "Alegeti optiunea: ";
}

int main() {
    std::string numeCompanie = citesteString("Introduceti numele companiei aeriene: ");
    CompanieAeriana companie(numeCompanie);

    int optiune;
    bool ruleaza = true;

    while (ruleaza) {
        afiseazaMeniu();
        std::cin >> optiune;
        curataBuffer();

        switch (optiune) {
            case 1: { // adauga zbor
                Zbor z = creeazaZbor();
                companie.adaugaZbor(z);
                std::cout <<"Zbor adaugat cu succes!\n";
                break;
            }
            case 2: { // cauta zbor dupa nume
                std::cout << "\nNume zbor de aflat: \n";
                Zbor* z = cautaZbor(companie);
                if (z != nullptr) {
                    std::cout << "Zbor gasit!\n";
                } else {
                    std::cout << "Zborul nu a fost gasit!\n";
                }
                break;
            }
            case 3: { //adauga pasager la zbor
                Zbor* z = cautaZbor(companie);
                if (z != nullptr) {
                    Pasager p = creeazaPasager();
                    if (z->adaugaPasager(p)) {
                        std::cout << "Pasager adaugat cu succes!\n";
                    }
                }
                break;
            }
            case 0: {
                std::cout << "\nLa revedere!\n";
                ruleaza = false;
                break;
            }
            default:
                std::cout << "Optiune invalida! Incercati din nou.\n";
                break;
        }

        if (ruleaza) {
            std::cout << "Apasati Enter pentru a continua..";
            std::cin.get();
        }
    }
}