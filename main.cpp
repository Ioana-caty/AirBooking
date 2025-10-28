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
        std::cout <<"4. Adauga pasager\n";
        std::cout <<"5. Cauta pasager\n";
        std::cout <<"6 Aplica discount\n";
        std::cout <<"7. Modifica poarta\n";
        std::cout <<"8 Modifica loc bilet\n";
        std::cout <<"9 Calculeaza incasari\n";
        std::cout <<"10 Verifica loc geam\n";
        std::cout <<"11 Verifica daca zborul este plin\n";
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

            const Zbor *z = companie.cautaZborDupaNumar(numar);
            if (z) {
                std::cout << "\n" << *z << "\n";
            } else {
                std::cerr << "\nZbor negasit!\n";
            }
        }
        if (optiune == 4) {
            std::string numar, email, loc, clasa;
            char nume[100];
            double pret;

            std::cout <<"Numar zbor: "; std::cin >> numar;
            Zbor *z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue; // opreste executia lui while si sare la meniu
            }
            std::cin.ignore(); // de la ENTER
            std::cout << "Nume: "; std::cin.getline(nume, 100);
            std::cout <<"Email: "; std::cin>>email;
            std::cout <<"Loc: "; std::cin>>loc;
            std::cout <<"Clasa: "; std::cin>>clasa;
            std::cout <<"Pret: "; std::cin>>pret;

            Bilet b(loc, clasa, pret);
            Pasager p(nume, email, b);
            z->adaugaPasager(p);

            std::cout << "Pasager adaugat cu succes!\n";
        }
        if (optiune == 5) {
            std::string numar;
            char nume[100];
            std::cout <<"Numar zbor: "; std::cin >> numar;

            Zbor* z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue;
            }
            std::cin.ignore(); //ENTER
            std::cout << "Nume: "; std::cin.getline(nume, 100);
            const Pasager* p = z->cautaPasagerDupaNume(nume);
            if (p) {
                std::cout << "\n" << *p << "\n";
            } else {
                std::cerr << "\nPasager negasit!\n";
            }
        }
        if (optiune == 6) {
            std::string numar;
            char nume[100];
            int discount;

            std::cout <<"Numar zbor: "; std::cin >> numar;
            Zbor* z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue;
            }

            std::cin.ignore(); //ENTER
            std::cout << "Nume: "; std::cin.getline(nume, 100);
            Pasager* p = z->cautaPasagerDupaNume(nume);
            if (!p) {
                std::cerr << "Pasager negasit!\n";
                continue;
            }

            std::cout <<"Discount (0-80): "; std::cin >> discount;
            Bilet b = p->getBilet();
            b.aplicaDiscount(discount);
            p->setBilet(b);
        }
        if (optiune == 7) {
            std::string numar, poarta;
            std::cout <<"Numar zbor: "; std::cin >> numar;

            Zbor* z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue;
            }

            std::cin.ignore(); //ENTER
            std::cout <<"Poarta noua: "; std::cin >> poarta;
            z->setPoarta(poarta);
            std::cout <<"Poarta modificata cu succes!";
        }
        if (optiune == 8) {
            std::string numar, loc;
            char nume[100];

            std::cout <<"Numar zbor: "; std::cin >> numar;
            Zbor* z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue;
            }

            std::cin.ignore(); //ENTER
            std::cout << "Nume: "; std::cin.getline(nume, 100);
            Pasager*p = z->cautaPasagerDupaNume(nume);
            if (!p) {
                std::cerr << "Pasager negasit!\n";
                continue;
            }

            std::cout <<"Loc nou: "; std::cin>>loc;
            Bilet b = p->getBilet();
            b.setLoc(loc);
            p->setBilet(b);

            std::cout <<"Locul modificat cu succes!\n";
        }
        if (optiune == 9) {
            std::string numar;
            std::cout <<"Numar zbor: "; std::cin >> numar;

            Zbor* z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue;
            }

            std::cout   << "Incasari: "
                        << std::fixed << std::setprecision(2)
                        << z->calculeazaIncasariTotale() << " EUR\n";
        }
        if (optiune == 10) {
            std::string numar;
            char nume[100];

            std::cout <<"Numar zbor: "; std::cin >> numar;
            Zbor* z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue;
            }

            std::cin.ignore(); //ENTER
            std::cout << "Nume: "; std::cin.getline(nume, 100);
            Pasager* p = z->cautaPasagerDupaNume(nume);
            if (!p) {
                std::cerr << "Pasager negasit!\n";
                continue;
            }

            if (p->getBilet().isWindowSeat()) {
                std::cout<<"DA, este loc la geam!\n";
            } else {
                std::cout<<"NU, nu este loc la geam!\n";
            }
        }
        if (optiune == 11) {
            std::string numar;
            std::cout <<"Numar zbor: "; std::cin >> numar;

            Zbor* z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue;
            }

            if (z->isFull()) {
                std::cout   <<"Zborul este PLIN ("
                            << z->getLocuriOcupate() << "/" << z->getCapacitateMaxima() << ")\n";
            } else {
                int disponibile = z->getCapacitateMaxima() - z->getLocuriOcupate();
                std::cout   <<"Zborul are locuri disponibile:" << disponibile << " locuri ramase ("
                            << z->getLocuriOcupate() << "/" << z->getCapacitateMaxima() << ")\n";
            }
        }
    }
    std::cout << "\nLA REVEDERE! SA AVETI O ZI BUNA!\n";


}