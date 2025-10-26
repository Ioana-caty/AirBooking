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
        std::cout <<"\n---MENIU INFORMATII (CONSULTARI)---\n";
        std::cout <<"1. Afiseaza toate informatiile companiei\n";
        std::cout <<"2. Cauta si afiseaza zbor\n";
        std::cout <<"3. Cauta pasager pentru un zbor\n";
        std::cout <<"4. Calculeaza incasarile totale\n";
        std::cout <<"5. Verifica disponibilitatea pentru un zbor\n";
        std::cout <<"6. Verifica daca locul este la geam\n";
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
                    std::cerr <<"X Zborul '" << nrZbor << "' nu exista." << std::endl;
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
            case 4: {
                Zbor* zbor = cautaZbor(companie);
                if (zbor != nullptr) {
                    double incasari = zbor->calculeazaIncasariTotale();
                    int nrPasageri = zbor->getLocuriOcupate();

                    std::cout << "Incasari pentru zborul '" << zbor->getNumarZbor() <<"'" << std::endl;
                    std::cout << "Numar Pasageri: " << nrPasageri << std::endl;
                    std::cout << "Total incasari: " << std::fixed << std::setprecision(2) << incasari
                              << " EUR" << std::endl;
                }
                break;
            }
            case 5: {
                Zbor* zbor = cautaZbor(companie);
                if (zbor != nullptr) {
                    std::cout << "Status: " << (zbor->isFull() ? "COMPLET" : "DISPONIBIL") << std::endl;
                }
                break;
            }
            case 6: {
                Zbor* zbor = cautaZbor(companie);;
                if (zbor != nullptr) {
                    std::string numePasager = citesteString("Introduceti numele pasagerului: ");
                    Pasager* pasagerGasit = zbor->cautaPasagerDupaNume(numePasager.c_str());

                    if (pasagerGasit != nullptr) {
                        Bilet biletPasager = pasagerGasit->getBilet();
                        std::cout << "Loc la geam: " << (biletPasager.isWindowSeat() ? "DA" : "NU");
                    } else {
                        std::cerr << "EROARE: Pasagerul nu a fost gasit!\n";
                    }
                }
                break;
            }
            case 0: {
                ruleaza = false;
                std::cout << "Revenire la meniul princial...\n";
                break;
            }
            default: {
                std::cerr << "X Optiune invalida!\n";
                break;
            }
        }
    }
}

void meniuRezervari(CompanieAeriana& companie) {
    bool ruleaza = true;
    while (ruleaza) {
        std::cout <<"\n---MENIU REZERVARI---\n";
        std::cout <<"1. Adauga un nou zbor\n";
        std::cout <<"2. Adauga pasager\n";
        std::cout <<"3. Modifica poarta zbor\n";
        std::cout <<"4. Aplica discount bilet pasager\n";
        std::cout <<"5. Modifica loc pasager!";
        std::cout <<"0. Inapoi la meniul principal\n";

        int optiune = citesteInt("Alege: ");

        switch (optiune) {
            case 1: {
                Zbor zborNou = creeazaZbor();
                companie.adaugaZbor(zborNou);
                std::cout << "Zborul a fost adaugat cu succes!";
                break;
            }
            case 2: {
                Zbor* zbor = cautaZbor(companie);;
                if (zbor != nullptr) {
                    if (zbor->isFull()) {
                        std::cerr << "EROARE: Zborul este Complet! Cauta alt zbor!!";
                    } else {
                        Pasager pasagerNou = creeazaPasager();
                        bool ok = zbor->adaugaPasager(pasagerNou);
                        if (ok == true) {
                            std::cout << "Pasagerul '" << pasagerNou.getNume() << "' a fost adaugat cu succes\n";
                            std::cout << "Locuri disponibile: " << (zbor->getCapacitateMaxima() - zbor->getLocuriOcupate()) << "\n";
                        }
                    }
                }
                break;
            }
            case 3: {
                Zbor* zbor = cautaZbor(companie);;
                if (zbor != nullptr) {
                    std::cout << "Poarta curenta: " << zbor->getPoarta() << std::endl;
                    std::string poartaNoua = citesteString("Introduceti noua poarta (ex: C15): ");
                    zbor->setPoarta(poartaNoua);
                    std::cout << "Poarta actualizata: " << zbor->getPoarta() << std::endl;
                }
                break;
            }
            case 4: {
                Zbor* zbor = cautaZbor(companie);;
                if (zbor != nullptr) {
                    std::string numePasager = citesteString("Introduceti numele pasagerului: ");
                    Pasager* pasagerGasit = zbor->cautaPasagerDupaNume(numePasager.c_str());

                    if (pasagerGasit != nullptr) {
                        Bilet biletCurent = pasagerGasit->getBilet();
                        int discount = citesteInt("Noul Discount (0 - 80%): ");
                        biletCurent.aplicaDiscount(discount);
                        pasagerGasit->setBilet(biletCurent);
                        std::cout << "Pret nou: " << std::fixed << std::setprecision(2)
                                  << biletCurent.getPretFinal() << " EUR\n";
                    } else {
                        std::cerr <<"EROARE: Pasagerul nu a fost gasit!\n";
                    }
                }
                break;
            }
            case 5: {
                Zbor* zbor = cautaZbor(companie);
                if (zbor != nullptr) {
                    std::string numePasager = citesteString("Introduceti numele pasagerului: ");
                    Pasager* pasagerGasit = zbor->cautaPasagerDupaNume(numePasager.c_str());

                    if (pasagerGasit != nullptr) {
                        Bilet biletCurent = pasagerGasit->getBilet();
                        std::cout <<"Loc curent: " << biletCurent.getLoc() << "\n";

                        std::string locNou = citesteString("Introduceti noul loc (ex: 12F): ");
                        biletCurent.setLoc(locNou);

                        pasagerGasit->setBilet((biletCurent));
                        std::cout <<"Loc actualizat: " << biletCurent.getLoc() << "\n";
                        std::cout << "Loc la geam: " << (biletCurent.isWindowSeat() ? "DA" : "NU");
                    } else {
                        std::cerr << "EROARE: Pasagerul nu a fost gasit!\n";
                    }
                }
                break;
            }
            case 0: {
                ruleaza = false;
                std::cout << "Revenire la meniul principal...\n";
                break;
            }
            default: {
                std::cerr << "X Optiune invalida!\n";
                break;
            }
        }
    }
}

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
            case 2:
                meniuRezervari(companie);
                break;
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

    meniuPrincipal(companie);

    return 0;
}



