#include "headers/Bilet.h"
#include "headers/Pasager.h"
#include "headers/Zbor.h"
#include "headers/CompanieAeriana.h"
#include "headers/Exceptii.h"
#include "input/populareDate.h"
#include "input/saveData.h"
#include "Pattern/BiletFactory.h"
#include "headers/Utils.h"


int main() {
	CompanieAeriana companie("Wizz");
	UI::titlu("SISTEM MANAGEMENT ZBORURI - WIZZ AIR");

	// Populare date cu gestionare exceptii
	try {
		populareDate(companie);
	}
	catch (const ExceptieZboruri& e) {
		mesajEroare(std::string("La populare: ") + e.what());
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
		std::cout <<"0. Salveeaza si iesi:\n";

		std::cin >> optiune;
		if (optiune == 0) {
			const std::string FISIER_DATE = "tastatura2.txt";
			UI::subtitlu("SALVARE DATE");
			saveData(companie, FISIER_DATE);
			break;
		}

		try {
			if (optiune == 1) {
				std::cout << "\n" << companie << "\n";
			}
			if (optiune == 2) {
				UI::subtitlu("ADAUGARE ZBOR");

				std::string numar, destinatie, poarta;
				int capacitateMax;
				std::cout << "Numar zbor: "; std::cin >> numar;
				std::cout << "Destinatie: "; std::cin >> destinatie;
				std::cout << "Poarta: "; std::cin >> poarta;
				std::cout << "Capacitate: "; std::cin >> capacitateMax;

				Zbor zbor(numar, destinatie, poarta, capacitateMax);
				if (zbor.setPoarta(poarta)) {
					companie.adaugaZbor(zbor);
					mesajSucces("Zbor adaugat cu succes!");
				}
			}
			if (optiune == 3) {
				UI::subtitlu("CAUTARE ZBOR");

				std::string numar;
				std::cout << "Numar zbor: "; std::cin >> numar;

				const Zbor* z = companie.cautaZborDupaNumar(numar);
				if (z) {
					std::cout << "\n" << *z << "\n";
				} else {
					mesajEroare("Zbor negasit!");
				}
			}
			if (optiune == 4) {
				UI::subtitlu("ADAUGARE PASAGER");

				std::string numar, email, loc, clasa, nume;
				double pret;
				int discount;

				std::cout << "Numar zbor: ";
				std::cin >> numar;
				std::cin.ignore();

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					mesajEroare("Zbor negasit!");
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
				mesajSucces("Pasager adaugat cu succes!");
			}
			if (optiune == 5) {
				UI::subtitlu("CAUTARE PASAGER");

				std::string numar, nume;
				std::cout << "Numar zbor: "; std::cin>>numar;
				std::cin.ignore();

				Zbor *z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					mesajEroare("Zbor negasit!");
					continue;
				}
				std::cout << "Nume: "; std::getline(std::cin, nume);
				const Pasager* p = z->cautaPasagerDupaNume(nume);
				if (p) {
					std::cout << "\n" << *p << "\n";
				} else {
					mesajEroare("Pasager negasit!");
				}
			}
			if (optiune == 6) {
				UI::subtitlu("MODIFICARE POARTA");

				std::string numar, poarta;
				std::cout << "Numar zbor: "; std::cin >> numar;

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					mesajEroare("Zbor negasit!");
					continue;
				}

				UI::Linie('-', 40);
				std::cout << "Poarta veche: " << z->getPoarta() << "\n";
				std::cout << "Poarta noua: "; std::cin >> poarta;
				if (z->setPoarta(poarta)) {
					mesajSucces("Poarta schimbata cu succes!");
				} else {
					mesajInfo("Poarta a ramas aceeasi!");
				}
			}
			if (optiune == 7) {
				UI::subtitlu("MODIFICARE LOC BILET");

				std::string numar, nume, locNou;
				std::cout << "Numar zbor: "; std::cin >> numar;
				std::cin.ignore();

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					mesajEroare("Zbor negasit!");
					continue;
				}

				std::cout << "Nume: "; std::getline(std::cin, nume);
				Pasager* p = z->cautaPasagerDupaNume(nume);
				if (!p) {
					mesajEroare("Pasager negasit!");
					continue;
				}

				if (!p->areBilet()) {
					mesajEroare("Pasagerul nu are bilet inregistrat!");
					continue;
				}

				UI::Linie('-', 40);
				std::cout << "Bilet curent:\n " << *p << "\n";
				std::cout << "Loc nou: "; std::cin >> locNou;

				std::string locUpper = toUpperCase(locNou);
				if (z->esteLocOcupat(locUpper, nume)) {
					mesajEroare("Locul " + locUpper + " este deja ocupat de alt pasager!");
					continue;
				}

				try {
					p->modificaLoc(locUpper);
					mesajSucces("Locul modificat cu succes!");
				}
				catch (const ExceptieZboruri& e) {
					mesajEroare(e.what());
				}
			}
			if (optiune == 8) {
				UI::subtitlu("CALCUL INCASARI");

				std::string numar;
				std::cout << "Numar zbor: "; std::cin >> numar;

				const Zbor *z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					mesajEroare("Zbor negasit!");
					continue;
				}

				std::cout   << "Incasari: " << std::fixed << std::setprecision(2)
							<< z->calculeazaIncasariTotale() << " EUR\n";
			}
			if (optiune == 9) {
				UI::subtitlu("VERIFICARE LOC GEAM");

				std::string numar, nume;
				std::cout << "Numar zbor: "; std::cin >> numar;
				std::cin.ignore();

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					mesajEroare("Zbor negasit!");
					continue;
				}

				std::cout << "Nume: "; std::getline(std::cin, nume);
				const Pasager* p = z->cautaPasagerDupaNume(nume);
				if (!p) {
					mesajEroare("Pasager negasit!");
					continue;
				}

				if (p->areBilet()) {
					mesajSucces("DA, este loc la geam!");
				} else {
					mesajInfo("NU, nu este loc la geam!");
				}
			}
			if (optiune == 10) {
				UI::subtitlu("VERIFICARE ZBOR PLIN");

				std::string numar;
				std::cout << "Numar zbor: "; std::cin >> numar;

				const Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					mesajEroare("Zbor negasit!");
					continue;
				}

				z->afiseazaDetaliiCapacitate();
			}
			if (optiune == 11) {
				UI::subtitlu("UPGRADE BILET PASAGER");

				std::string numar, nume;
				std::cout << "Numar zbor: "; std::cin >> numar;
				std::cin.ignore();

				Zbor* z = companie.cautaZborDupaNumar(numar);
				if (!z) {
					mesajEroare("Zbor negasit!");
					continue;
				}
				std::cout << "Nume pasager: "; std::getline(std::cin, nume);

				const Pasager* p = z->cautaPasagerDupaNume(nume);
				if (p && p->areBilet()) {
					UI::Linie('-', 40);
					std::cout << *p << "\n";
					UI::Linie('-', 40);
				}

				char confirm;
				std::cout <<"\nConfirmati upgrade-ul? (y/n): ";
				std::cin >> confirm;

				if (confirm == 'y' || confirm == 'Y') {
					if (z->upgradeBiletPasager(nume)) {
						mesajSucces("Upgrade realizat cu succes!");
						const Pasager* pNou = z->cautaPasagerDupaNume(nume);
						if (pNou && pNou->areBilet()) {
							std::cout <<"\nBILET ACTUALIZAT:\n";
							std::cout << *pNou << "\n";
						}
					}
				} else {
					mesajInfo("Upgrade anulat.");
				}
			}
			if (optiune == 12) {
				UI::subtitlu("SORTARE ZBORURI");

				int subOptiune;
				while (true) {
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
				UI::subtitlu("FILTRARE ZBORURI");

				while (true) {
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
						mesajInfo("Nu exista zboruri care sa indeplineasca criteriul.");
					} else {
						UI::Linie('=', 90);
						for (const auto* z : zboruri) {
							z->afisareFaraPasageri(false);
						}
					}
				}
			}
		}
		catch (const ExceptieZboruri& e) {
			mesajEroare(e.what());
		}
	}
	mesajInfo("La revedere! Sa aveti o zi buna!");
	return 0;
}