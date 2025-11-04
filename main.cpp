#include <iostream>
#include <iomanip>
#include <fstream>
#include "headers/Bilet.h"
#include "headers/Pasager.h"
#include "headers/Zbor.h"
#include "headers/CompanieAeriana.h"

void populareDate(CompanieAeriana& companie) {
    std::cout << "---POPULARE DATE---\n";

    const std::string FISIER_DATE = "tastatura.txt";
    std::ifstream fin(FISIER_DATE);

    if (!fin.is_open()) {
        std::cerr << "EROARE: Nu s-a putut deschide fisierul tastatura.txt\n";
        return;
    }

    int numarzboruri;
    fin >> numarzboruri;
    fin.ignore();

    for (int i = 0; i < numarzboruri; i++) {
        std::string codZbor, destinatie, poarta;
        int capacitateMaxima;

        fin >> codZbor >> destinatie >> poarta >> capacitateMaxima;
        fin.ignore();

        Zbor zbor(codZbor, destinatie, poarta, capacitateMaxima);

        int numarPasageri;
        fin >> numarPasageri;
        fin.ignore();

        for (int j = 0; j < numarPasageri; j++) {
            std::string nume, email, loc, tipClasa;
            double pretBaza, discount;

            std::getline(fin, nume);
            std::getline(fin, email);
            fin >> loc >> tipClasa >> pretBaza >> discount;
            fin.ignore();

            Bilet bilet(loc, tipClasa, pretBaza);

            if (discount > 0) {
                bilet.aplicaDiscount(discount);
            }

            Pasager pasager(nume, email, bilet);
            zbor.adaugaPasager(pasager);
        }

        companie.adaugaZbor(zbor);
    }

    fin.close();
    std::cout << "S-au implementat datele din fisier!\n";
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
            std::string numar, email, loc, clasa, nume;
            double pret;

            std::cout <<"Numar zbor: "; std::cin >> numar;
            Zbor *z = companie.cautaZborDupaNumar(numar);
            if (!z) {
                std::cerr << "Zbor negasit!\n";
                continue; // opreste executia lui while si sare la meniu
            }
            std::cin.ignore(); // de la ENTER
            std::cout << "Nume: "; std::cin>>nume;
            std::cout <<"Email: "; std::cin>>email;
            std::cout <<"Loc: "; std::cin>>loc;
            std::cout <<"Clasa: "; std::cin>>clasa;
            std::cout <<"Pret: "; std::cin>>pret;

            Bilet b(loc, clasa, pret);
            Pasager p(nume, email, b);
            if (z->adaugaPasager(p)) {
                std::cout << "Pasager adaugat cu succes!\n";
            } else {
                std::cerr << "Pasagerul " << p.getNume() << " NU a putut fi adaugat.\n";
            }
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

            const Zbor* z = companie.cautaZborDupaNumar(numar);
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
            const Pasager* p = z->cautaPasagerDupaNume(nume);
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

            const Zbor* z = companie.cautaZborDupaNumar(numar);
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