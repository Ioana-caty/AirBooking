#include "headers/Bilet.h"
#include "headers/Pasager.h"
#include "headers/Zbor.h"
#include "headers/CompanieAeriana.h"
#include "headers/Exceptii.h"
#include "input/populareDate.h"
#include "input/saveData.h"
#include "Pattern/BiletFactory.h"
#include <iostream>
#include <iomanip>
#include <fstream>

int main() {
	CompanieAeriana companie("Wizz");

	// Populare date cu gestionare exceptii
	try {
		populareDate(companie);
	}
	catch (const ExceptieZboruri& e) {
		std::cerr << "EROARE la populare: " << e.what() << "\n";
	}

	int optiune ;
	while (true) {
		std::cout << "\n---MENIU---\n";
		std::cout << "1. Afiseaza date companie\n";
		std::cout << "2. Adauga zbor\n";
		std::cout << "3. Cauta zbor\n";
		std::cout << "4. Adauga pasager\n";
		std::cout << "5. Cauta pasager (nume)\n";
		std::cout << "6. Modifica poarta\n";
		std::cout << "7. Modifica loc bilet\n";
		std::cout << "8. Calculeaza incasari\n";
		std::cout << "9. Verifica loc geam\n";
		std::cout << "10. Verifica daca zborul este plin\n";
		std::cout << "11. Upgrade bilet pasager\n";
		std::cout << "12. Sorteaza zboruri\n";
		std::cout << "13. Filtreaza zboruri\n";
		std::cout <<"0. Optiune: ";
		std::cin >> optiune;

		if (optiune == 0) {
			const std::string FISIER_DATE = "tastatura2.txt";
			saveData(companie, FISIER_DATE);
			break;
		}

		try {
			if (optiune == 1) {
				std::cout << "\n" << companie << "\n";
			}
			if (optiune == 2) {
				std::string numar, destinatie, poarta;
				int capacitateMax;
				std::cout << "Numar zbor: "; std::cin >> numar;
				std::cout << "Destinatie: "; std::cin >> destinatie;
				std::cout << "Poarta: "; std::cin >> poarta;
				std::cout << "Capacitate: "; std::cin >> capacitateMax;

				Zbor zbor(numar, destinatie, poarta, capacitateMax);
				if (zbor.setPoarta(poarta)) {
					companie.adaugaZbor(zbor);
					std::cout << "\nZbor adaugat cu succes!\n";
				}
			}
			if (optiune == 3) {
				std::string numar;
				std::cout << "Numar zbor: "; std::cin >> numar;

				const Zbor* z = companie.cautaZborDupaNumar(numar);
				if (z) {
					std::cout << "\n" << *z << "\n";
				} else {
					std::cerr << "\nZbor negasit!\n";
				}
			}
			if (optiune == 4) {
				std::string numar, email, loc, clasa, nume;
				double pret;
				int discount;

				std::cout << "Numar zbor: ";
				std::cin >> numar;
				std::cin.ignore();

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					std::cerr << "Zbor negasit!\n";
					continue;
				}

				std::cout << "Nume: "; std::getline(std::cin, nume);
				std::cout << "Email: "; std::cin >> email;

				z->afiseazaLocuriOcupate();
				std::cout << "Loc: "; std::cin >> loc;
				std::cout << "Tip clasa: "; std::cin >> clasa;
				std::cout << "Pret: "; std::cin >> pret;
				std::cout << "Discount: "; std::cin >> discount;

				Bilet* bilet = BiletFactory::creeazaBilet(clasa, loc, pret, discount);
				Pasager p(nume, email, bilet);
				z->adaugaPasager(p);
				std::cout << "\nPasager adaugat cu succes!\n";
			}
			if (optiune == 5) {
				std::string numar, nume;
				std::cout << "Numar zbor: "; std::cin>>numar;
				std::cin.ignore();

				Zbor *z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					std::cerr << "\nZbor negasit!\n";
					continue;
				}
				std::cout << "Nume: "; std::getline(std::cin, nume);
				const Pasager* p = z->cautaPasagerDupaNume(nume);
				if (p) {
					std::cout << "\n" << *p << "\n";
				} else {
					std::cerr << "\nPasager negasit!\n";
				}
			}
			if (optiune == 6) {
				std::string numar, poarta;
				std::cout << "Numar zbor: "; std::cin >> numar;

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					std::cerr << "Zbor negasit!\n";
					continue;
				}

				std::cout << "----------------------------------------\n";
				std::cout << "Poarta veche: " << z->getPoarta() << "\n";
				std::cout << "Poarta noua: "; std::cin >> poarta;
				if (z->setPoarta(poarta)) {
					std::cout << "\n Poarta schimbata cu succes!\n";
				} else {
					std::cout << "\nPoarta a ramas aceeasi!\n";
				}
			}
			if (optiune == 7) {
				std::string numar, nume, locNou;
				std::cout << "Numar zbor: "; std::cin >> numar;
				std::cin.ignore();

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					std::cerr << "Zbor negasit!\n";
					continue;
				}

				std::cout << "Nume: "; std::getline(std::cin, nume);
				Pasager* p = z->cautaPasagerDupaNume(nume);
				if (!p) {
					std::cerr << "Pasager negasit!\n";
					continue;
				}

				if (!p->areBilet()) {
					std::cerr << "\nPasagerul nu are bilet inregistrat!\n";
					continue;
				}

				std::cout << "----------------------------------------\n";
				std::cout << "Bilet curent:\n " << *p << "\n";
				std::cout << "Loc nou: "; std::cin >> locNou;

				std::string locUpper = toUpperCase(locNou);
				if (z->esteLocOcupat(locUpper, nume)) {
					std::cerr << "!!!EROARE: Locul " << locUpper << " este deja ocupat de alt pasager!\n";
					continue;
				}

				try {
					p->modificaLoc(locUpper);
					std::cout << "Locul modificat cu succes!";
				}
				catch (const ExceptieZboruri& e) {
					std::cerr << "[EROARE] " << e.what() << "\n";
				}
			}
			if (optiune == 8) {
				std::string numar;
				std::cout << "Numar zbor: "; std::cin >> numar;

				const Zbor *z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					std::cerr << "Zbor negasit!\n";
					continue;
				}

				std::cout   << "Incasari: " << std::fixed << std::setprecision(2)
							<< z->calculeazaIncasariTotale() << " EUR\n";
			}
			if (optiune == 9) {
				std::string numar, nume;
				std::cout << "Numar zbor: "; std::cin >> numar;
				std::cin.ignore();

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					std::cerr <<"Zbor negasit!\n";
					continue;
				}

				std::cout << "Nume: "; std::getline(std::cin, nume);
				const Pasager* p = z->cautaPasagerDupaNume(nume);
				if (!p) {
					std::cerr << "Pasager negasit!\n";
					continue;
				}

				if (p->areBilet()) {
					std::cout << "DA, este loc la geam!\n";
				} else {
					std::cout << "NU, nu este loc la geam!\n";
				}
			}
			if (optiune == 10) {
				std::string numar;
				std::cout << "Numar zbor: "; std::cin >> numar;

				const Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					std::cerr << "Zbor negasit!\n";
					continue;
				}

				z->afiseazaDetaliiCapacitate();
			}
			if (optiune == 11) {
				std::string numar, nume;
				std::cout << "Numar zbor: "; std::cin >> numar;
				std::cin.ignore();

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					std::cerr << "Zbor negasit!\n";
					continue;
				}
				std::cout << "Nume pasager: "; std::getline(std::cin, nume);

				const Pasager* p = z->cautaPasagerDupaNume(nume);
				if (p && p->areBilet()) {
					std::cout << "\n--- BILET CURENT ---\n";
					std::cout << *p << "\n";
					std::cout << "--------------------------------------\n";
				}

				char confirm;
				std::cout <<"\nConfirmati upgrade-ul? (y/n): ";
				std::cin >> confirm;

				if (confirm == 'y' || confirm == 'Y') {
					if (z->upgradeBiletPasager(nume)) {
						std::cout << "\n--- BILET ACTUALIZAT ---\n";
						const Pasager* pNou = z->cautaPasagerDupaNume(nume);
						if (pNou && pNou->areBilet()) {
							std::cout << *pNou << "\n";
						}
						std::cout << "-----------------------------------\n";
					}
				} else {
					std::cout << "Upgrade anulat.\n";
				}
			}
			if (optiune == 12) {

				int subOptiune;
				while (true) {
					std::cout << "\n--- SORTEAZA ZBORURI ---\n";
					std::cout << "1. Dupa incasari (descrescator)\n";
					std::cout << "2. Dupa ocupare (descrescator)\n";
					std::cout << "3. Dupa destinatie (alfabetic)\n";
					std::cout << "0. Meniu Princial\n";
					std::cout << "Optiune: ";

					std::cin >> subOptiune;

					if (subOptiune == 0) {
						break;
					}
					if (subOptiune == 1) {
						companie.sorteazaZboruriDupaIncasari();
						companie.afisareFaraPasageri(true);   // cu incasari
					}
					if (subOptiune == 2) {
						companie.sorteazaZboruriDupaOcupare();
						companie.afisareFaraPasageri(false); // fara incasari
					}
					if (subOptiune == 3) {
						companie.sorteazaZboruriDupaDestinatie();
						companie.afisareFaraPasageri(false);
					}
				}
			}

			if (optiune == 13) {
				while (true) {
					std::cout << "\n--- FILTREAZA ZBORURI ---\n";
					std::cout << "1. Zboruri pline\n";
					std::cout << "2. Zboruri goale\n";
					std::cout << "3. Cauta dupa destinatie\n";
					std::cout << "0. Meniu Principal\n";
					std::cout << "Optiune: ";

					int subOptiune;
					std::cin >> subOptiune;

					if (subOptiune == 0) {
						break;
					}

					std::vector<Zbor*> zboruri;

					if (subOptiune == 1) {
						zboruri = companie.filtreazaZboruriPline();
					}
					if (subOptiune == 2) {
						zboruri = companie.filtreazaZboruriGoale();
					}
					if (subOptiune == 3) {
						std::string dest;
						std::cout << "Destinatie: ";
						std::cin >> dest;
						zboruri = companie.cautaZboruriDupaDestinatie(dest);
					}

					if (zboruri.empty()) {
						std::cout << "\nNu exista zboruri care sa indeplineasca criteriul.\n";
					} else {
						std::cout << "\n==============================================================================================\n";
						for (const auto* z : zboruri) {
							z->afisareFaraPasageri(false);
						}
						std::cout << "==============================================================================================\n";
					}
				}
			}
		}
		catch (const ExceptieZboruri& e) {
			std::cerr << "\nEROARE: " << e.what() << "\n";
		}
	}
	std::cout << "\nLA REVEDERE! SA AVETI O ZI BUNA!\n";
	return 0;
}