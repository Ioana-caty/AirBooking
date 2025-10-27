#include <iostream>
#include <iomanip>
#include "Bilet.h"
#include "Pasager.h"
#include "Zbor.h"
#include "CompanieAeriana.h"

int main() {
    std:: cout <<"SISTEM MANAGEMENT ZBORURI";

    // BILET
    std:: cout << "\n\nTEST1: Functionalitate Bilete";
    Bilet b1;
    Bilet b2("12A", "Economic", 120.50);
    Bilet b3("15F", "Business", 350.5);
    std::cout <<"\nBilete create:\n" << b1 << "\n" << b2 << "\n" << b3 << "\n";

    std::cout << "\nLoc b2: " << b2.getLoc() << "\n";
    b2.setLoc("14B");
    std::cout << "Loc nou: " << b2.getLoc() << "\n";

    b3.aplicaDiscount(20);
    b3.aplicaDiscount(90);

    std::cout   << "\nPret final b3: " << std::fixed << std::setprecision(2)
                << b3.getPretFinal() << " EUR\n";

    Bilet geam("12A", "Economic", 100.3);
    Bilet culoar("8C", "Economic", 100.1);

    std::cout << "Verificare Locuri la geam: ";
    std::cout << (geam.isWindowSeat() ? "DA" : "NU");
    std::cout << (culoar.isWindowSeat() ? " DA" : " NU") << "\n";


    // PASAGER
    std:: cout << "\nTEST2: Functionalitate Pasageri";

    Bilet bilet1("12A", "Economic", 150.7);
    Bilet bilet2("8F", "Business", 400.5);

    Pasager p1;
    Pasager p2("Iustina Caramida", "i.caramida@yahoo.com", bilet1);
    Pasager p3("Ioana Caramida", "c.caramida@gmail.com", bilet2);

    std::cout << "\nPasageri creati:\n" << p1 << "\n" << p2 << "\n" << p3 << "\n";
    std::cout << "Nume p2: " << p2.getNume() << "\n";
    std::cout << "Bilet p3: " << p2.getBilet() << "\n";

    Bilet biletNou("5C", "Economic", 200.3);
    biletNou.aplicaDiscount(15);
    p2.setBilet(biletNou);
    std::cout <<"\nDupa discount:\n" << p2 << "\n";

    //ZBOR
    std:: cout << "\nTEST3: Functionalitate Zbor";

    Zbor z1;
    Zbor z2("RO123", "Paris", "A12", 3);
    std::cout << "Zborurile: " << z1 << z2 << "\n";

    std::cout <<"Numar zbor: " << z2.getNumarZbor() << "\n";
    std::cout <<"Poarta: " << z2.getPoarta() << "\n";
    std::cout <<"Locuri ocupate: " << z2.getLocuriOcupate() << "\n";
    std::cout <<"Capacitate: " << z2.getCapacitateMaxima() << "\n";

    z2.setPoarta("B15");
    std::cout << "\nNoua poarta: " << z2.getPoarta() << "\n";
    z2.setPoarta("123"); // eroare

    std::cout << "\nZbor plin? " << (z2.isFull()? "DA" : "NU") << "\n";

    //Noi pasageri
    Bilet bz1("12A", "Economic", 120.7);
    Bilet bz2("8F", "Business", 400.5);
    bz2.aplicaDiscount(10);
    Bilet bz3("8C", "Economic", 110.0);
    Bilet bz4("22D", "Economic", 115.0);

    Pasager pz1("Ana Popescu", "a.popescu@gmail.com", bz1);
    Pasager pz2("Ion Aranutu", "arnautu@gmail.com", bz2);
    Pasager pz3("Elena Dumitru", "dumitru@gmail.com", bz3);
    Pasager pz4("Mihai Olteanu", "olteanu@gmail.com", bz4);

    std::cout <<"\nAdaug pasageri...";
    z2.adaugaPasager(pz1);
    z2.adaugaPasager(pz2);
    z2.adaugaPasager(pz3);

    std::cout <<"\n" << z2 << "\n";

    //incercam sa adaugam cand e plin
    std::cout<<"Adaug cand e plin:\n";
    z2.adaugaPasager(pz4);

    //calculam incasari
    std::cout   << "\nIncasari totale: " << std::fixed << std::setprecision(2)
                << z2.calculeazaIncasariTotale() << " EUR\n";

    //cautam pasager
    Pasager* gasit = z2.cautaPasagerDupaNume("Ion Aranutu");
    if (gasit) {
        std::cout << "\nPasager gasit!\n" << *gasit << "\n";
    }

    Pasager* negasit = z2.cautaPasagerDupaNume("Vasile Ion");
    if (!negasit) {
        std::cout << "\nPasagerul nu exita!\n" << *negasit << "\n";
    }

    //Companie aeriana
    std:: cout << "\n!!!!!!!!!!!!!!!!TEST4: Functionalitate Companie";
    CompanieAeriana Wizz("Wizz");
    std::cout <<"\nCompanie: " << Wizz.getNumeCompanie() << "\n";

    //cream zboruri
    Zbor zb1("RO101", "Paris", "A12", 2);
    Zbor zb2("RO202", "Londra", "B8", 3);
    Zbor zb3("RO303", "Roma", "C15", 2);

    std::cout<<"\nAdauga zboruri:...\n";
    Wizz.adaugaZbor(zb1);
    Wizz.adaugaZbor(zb2);
    Wizz.adaugaZbor(zb3);

    std::cout << "\n" << Wizz << "\n";

}