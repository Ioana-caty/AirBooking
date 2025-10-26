#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

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

    Bilet b = creeazaBilet();

    Pasager p(nume.c_str(), email, b);
    return p;
}

Zbor creeazaZbor() {
    std::cout << "--- CREARE ZBOR NOU --- \n";
    std::string numarZbor = citesteString("Introduceti nr. zbor (ex:RO255): ");
    std::string destinatie = citesteString("Introduceti destinatia: ");
    std::string poarta = citesteString("Introduceti poarta (ex:B12): ");
    size_t capacitateMaxima = citesteInt("Introduceti capacitatea maxima a zborului: ");

    Zbor z(numarZbor, destinatie, poarta, capacitateMaxima);
    return z;
}

Zbor* cautaZbor(CompanieAeriana& companie) {
    std::string nrZbor = citesteString("Introduceti numarul zborului: ");
    Zbor* zborGasit = companie.cautaZborDupaNumar(nrZbor);
    if (zborGasit == nullptr) {
        std::cout << "EROARE: Zborul '" << nrZbor << "' nu a fost gasit!\n";
    }
    return zborGasit;
}

void meniuInformatii(CompanieAeriana& companie) {
    bool ruleaza = true;
    while (ruleaza) {
        std::cout <<"---MENIU INFORMATII (CONSULTARI)---\n";
        std::cout <<"1. Afiseaza toate informatiile companiei\n";
        std::cout <<"2. Cauta si afiseaza zbor\n";
        std::cout <<"3. Cauta pasager pentru un zbor\n";
        std::cout <<"4. Calculeaza incasarile totale\n";
        std::cout <<"5. Verifica disponibilitatea pentru un zbor\n";
        std::cout <<"0. Inapoi la meniul principal\n";

        int optiune = citesteInt("Alege: ");
        switch (optiune) {
            case 1: {
                std::cout << companie << std::endl;
                break;
            }
            case 2: {
                std::string nrZbor = citesteString("Introduceti numarul zborului: ");
                Zbor* zborGasit = companie.cautaZborDupaNumar(nrZbor);

                if (zborGasit != nullptr) {
                    std::cout << "\n" << *zborGasit << std::endl;
                } else {
                    std::cout <<"X Zborul '" << nrZbor << "' nu exista." << std::endl;
                }
                break;
            }
            case 3: {
                Zbor* zborExistent = cautaZbor(companie);
                if (zborExistent != nullptr) {
                    std::string numePasager = citesteString("Introduceti numele pasagerului: ");
                    Pasager*  pasagerGasit = zborExistent->cautaPasagerDupaNume(numePasager.c_str());

                    if (pasagerGasit != nullptr) {
                        std::cout <<"Pasager gasit!"<< std::endl;
                        std::cout << *pasagerGasit << std::endl;
                    } // teoretic am eroare la cautaPasagerDupaNume !!!!!!
                }
                // teoretric am eroare si la cautaZbor !!!!
                break;
            }
            case 0: {
                ruleaza = false;
                std::cout << "Revenire la meniul princial...\n";
                break;
            }
            default: {
                std::cout << "X Optiune invalida!\n";
                break;
            }
        }
    }
}

// void meniuRezervari(CompanieAeriana& companie) {
//     bool ruleaza = true;
//     while (ruleaza) {
//         std::cout <<"---MENIU REZERVARI---\n";
//         std::cout <<"1. .....";
//         std::cout <<"2. ......";
//     }
// }

void meniuPrincipal(CompanieAeriana& companie) {
    bool ruleaza = true;
    while (ruleaza) {
        std::cout <<"---MENIU PRINCIPAL(" << companie.getNumeCompanie() <<")---\n";
        std::cout <<"1. Meniu Informatii\n";
        std::cout <<"2. Meniu Rezervari\n";
        std::cout <<"0. Iesire\n";

        int optiune = citesteInt("Alege: ");
        switch (optiune) {
            case 1:
                meniuInformatii(companie);
                break;
            // case 2:
            //     meniuRezervari(companie);
            //     break;
            case 0:
                ruleaza = false;
                std::cout <<"La revedere! Va dorim o zi buna!" << std::endl;
                break;
            default:
                std::cout << "Optiune invalida. Incercati din nou!" << std::endl;
        }
    }
}

int main() {
    std::cout << "=== SISTEM DE GESTIUNE COMPANIE AERIANA ===\n";

    std::string numeCompanie = citesteString("Introduceti numele companiei aeriene: ");
    CompanieAeriana companie(numeCompanie);

    //date temporare

    Zbor z1("RO123", "Bucuresti", "A5", 150);
    Zbor z2("L456", "Frankfurt", "B12", 200);


    Bilet b1("10A", "Economic", 120.50);
    Pasager p1("Tudor Deaconu", "t.deaconu@gmail.com", b1);
    Bilet b2("25A", "Business", 98.5);
    Pasager p2("Iustina Caramida", "i.caramida@yahoo.com", b2);
    Bilet b3("8A", "Economic", 60.50);
    Pasager p3("Costin Sin", "c.sin@gmail.com", b3);

    z1.adaugaPasager(p1);
    z1.adaugaPasager(p2);
    z2.adaugaPasager(p3);

    companie.adaugaZbor((z1));
    companie.adaugaZbor((z2));

    meniuPrincipal(companie);

    return 0;
}


/*                      (Bilet, std::string) trebuie să fie construit înainte ca instrucțiunile din {...} să ruleze.

Avem o clasă "Pasager" care are ca membru un obiect Bilet bilet;.
    Când creez un obiect Pasager p1, ordinea e așa:
        înainte să intre în corpul constructorului Pasager(...), C++ trebuie să inițializeze toți membrii clasei.
        deci, C++ apelează automat constructorul default al lui Bilet, adică Bilet::Bilet().
        acesta creează un bilet temporar → de aici apare „Biletul fantomă”.

Constructorul default al lui Bilet incrementează counterID.
→ De aceea ID-ul sare din 1000 în 1001 înainte ca tu să-l fi dorit.

Apoi, în interiorul constructorului Pasager, facem o copiere a biletului real
→ Dar biletul fantomă există deja, deci counterID a fost deja mărit o dată în plus.

std::string este o clasă, la fel ca Bilet
-> are și ea un constructor default (care creează un string gol "")
-> daca pun intre {..} ia stringul gol "" si copiaza peste el valoarea mea (i.caramida@yahoo.com)
        am facut 2 operatii
-> astfel sarim peste crearea inutile a stringului gol

*/
