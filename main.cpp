#include "headers/Bilet.h"
#include "headers/Pasager.h"
#include "headers/Zbor.h"
#include "headers/CompanieAeriana.h"
#include "headers/Bagaj.h"
#include "headers/CheckIn.h"
#include "headers/Exceptii.h"
#include "input/populareDate.h"
#include "input/saveData.h"
#include "Pattern/BiletFactory.h"
#include "headers/Utils.h"

void adaugaZbor(CompanieAeriana& companie) {
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

void cautaZbor(CompanieAeriana& companie) {
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

bool adaugaPasager(CompanieAeriana& companie) {
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
		return false;
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
	return true;
}

bool cautaPasager(CompanieAeriana& companie) {
	UI::subtitlu("CAUTARE PASAGER");

	std::string numar, nume;
	std::cout << "Numar zbor: "; std::cin >> numar;
	std::cin.ignore();

	Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}
	std::cout << "Nume: "; std::getline(std::cin, nume);
	const Pasager* p = z->cautaPasagerDupaNume(nume);
	if (p) {
		std::cout << "\n" << *p << "\n";
	} else {
		mesajEroare("Pasager negasit!");
	}
	return true;
}

bool modificaPoarta(CompanieAeriana& companie) {
	UI::subtitlu("MODIFICARE POARTA");

	std::string numar, poarta;
	std::cout << "Numar zbor: "; std::cin >> numar;

	Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}

	UI::Linie(std::cout, '-', 40);
	std::cout << "Poarta veche: " << z->getPoarta() << "\n";
	std::cout << "Poarta noua: "; std::cin >> poarta;
	if (z->setPoarta(poarta)) {
		mesajSucces("Poarta schimbata cu succes!");
	} else {
		mesajInfo("Poarta a ramas aceeasi!");
	}
	return true;
}

bool modificaLocBilet(CompanieAeriana& companie) {
	UI::subtitlu("MODIFICARE LOC BILET");

	std::string numar, nume, locNou;
	std::cout << "Numar zbor: "; std::cin >> numar;
	std::cin.ignore();

	Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}

	std::cout << "Nume: "; std::getline(std::cin, nume);
	Pasager* p = z->cautaPasagerDupaNume(nume);
	if (!p) {
		mesajEroare("Pasager negasit!");
		return false;
	}

	if (!p->areBilet()) {
		mesajEroare("Pasagerul nu are bilet inregistrat!");
		return false;
	}

	UI::Linie(std::cout, '-', 40);
	std::cout << "Bilet curent:\n " << *p << "\n";
	std::cout << "Loc nou: "; std::cin >> locNou;

	std::string locUpper = toUpperCase(locNou);
	if (z->esteLocOcupat(locUpper, nume)) {
		mesajEroare("Locul " + locUpper + " este deja ocupat de alt pasager!");
		return false;
	}

	try {
		p->modificaLoc(locUpper);
		mesajSucces("Locul modificat cu succes!");
	}
	catch (const ExceptieZboruri& e) {
		mesajEroare(e.what());
	}
	return true;
}

bool calculeazaIncasari(CompanieAeriana& companie) {
	UI::subtitlu("CALCUL INCASARI");

	std::string numar;
	std::cout << "Numar zbor: "; std::cin >> numar;

	const Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}

	std::cout << "Incasari: " << std::fixed << std::setprecision(2)
			  << z->calculeazaIncasariTotale() << " EUR\n";
	return true;
}

bool verificaLocGeam(CompanieAeriana& companie) {
	UI::subtitlu("VERIFICARE LOC GEAM");

	std::string numar, nume;
	std::cout << "Numar zbor: "; std::cin >> numar;
	std::cin.ignore();

	Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}

	std::cout << "Nume: "; std::getline(std::cin, nume);
	const Pasager* p = z->cautaPasagerDupaNume(nume);
	if (!p) {
		mesajEroare("Pasager negasit!");
		return false;
	}

	if (p->areBilet()) {
		mesajSucces("DA, este loc la geam!");
	} else {
		mesajInfo("NU, nu este loc la geam!");
	}
	return true;
}

bool verificaZborPlin(CompanieAeriana& companie) {
	UI::subtitlu("VERIFICARE ZBOR PLIN");

	std::string numar;
	std::cout << "Numar zbor: "; std::cin >> numar;

	const Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}

	z->afiseazaDetaliiCapacitate();
	return true;
}

bool upgradeBilet(CompanieAeriana& companie) {
	UI::subtitlu("UPGRADE BILET PASAGER");

	std::string numar, nume;
	std::cout << "Numar zbor: "; std::cin >> numar;
	std::cin.ignore();

	Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}
	std::cout << "Nume pasager: "; std::getline(std::cin, nume);

	const Pasager* p = z->cautaPasagerDupaNume(nume);
	if (p && p->areBilet()) {
		UI::PrintPasager(std::cout, *p, '-', 70);
	}

	char confirm;
	std::cout << "\nConfirmati upgrade-ul? (y/n): ";
	std::cin >> confirm;

	if (confirm == 'y' || confirm == 'Y') {
		if (z->upgradeBiletPasager(nume)) {
			mesajSucces("Upgrade realizat cu succes!");
			const Pasager* pNou = z->cautaPasagerDupaNume(nume);
			if (pNou && pNou->areBilet()) {
				std::cout << "\nBILET ACTUALIZAT:\n";
				std::cout << *pNou << "\n";
			}
		}
	} else {
		mesajInfo("Upgrade anulat.");
	}
	return true;
}

void sorteazaZboruri(CompanieAeriana& companie) {
	UI::subtitlu("SORTARE ZBORURI");

	int subOptiune;
	while (true) {
		std::cout << "1. Dupa incasari (descrescator)\n";
		std::cout << "2. Dupa ocupare (descrescator)\n";
		std::cout << "3. Dupa destinatie (alfabetic)\n";
		std::cout << "0. Meniu Principal\n";
		std::cout << "Optiune: ";

		std::cin >> subOptiune;

		if (subOptiune == 0) break;

		if (subOptiune == 1) {
			companie.sorteazaZboruriDupaIncasari();
			companie.afisareFaraPasageri(true);
		}
		else if (subOptiune == 2) {
			companie.sorteazaZboruriDupaOcupare();
			companie.afisareFaraPasageri(false);
		}
		else if (subOptiune == 3) {
			companie.sorteazaZboruriDupaDestinatie();
			companie.afisareFaraPasageri(false);
		}
	}
}

void filtreazaZboruri(CompanieAeriana& companie) {
	UI::subtitlu("FILTRARE ZBORURI");

	while (true) {
		std::cout << "1. Zboruri pline\n";
		std::cout << "2. Zboruri goale\n";
		std::cout << "3. Cauta dupa destinatie\n";
		std::cout << "0. Meniu Principal\n";
		std::cout << "Optiune: ";

		int subOptiune;
		std::cin >> subOptiune;

		if (subOptiune == 0) break;

		std::vector<Zbor*> zboruri;

		if (subOptiune == 1) {
			zboruri = companie.filtreazaZboruriPline();
		}
		else if (subOptiune == 2) {
			zboruri = companie.filtreazaZboruriGoale();
		}
		else if (subOptiune == 3) {
			std::string dest;
			std::cout << "Destinatie: ";
			std::cin >> dest;
			zboruri = companie.cautaZboruriDupaDestinatie(dest);
		}

		if (zboruri.empty()) {
			mesajInfo("Nu exista zboruri care sa indeplineasca criteriul.");
		} else {
			UI::Linie(std::cout, '=', 90);
			for (const auto* z : zboruri) {
				z->afisareFaraPasageri(false);
			}
		}
	}
}

bool checkInPasager(CompanieAeriana& companie) {
	UI::subtitlu("CHECK-IN PASAGER");

	std::string numar, nume;
	std::cout << "Numar zbor: ";
	std::cin >> numar;
	std::cin.ignore();

	Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}

	std::cout << "Nume pasager: ";
	std::getline(std::cin, nume);

	Pasager* p = z->cautaPasagerDupaNume(nume);
	if (!p) {
		mesajEroare("Pasager negasit!");
		return false;
	}

	if (!p->areBilet()) {
		mesajEroare("Pasagerul nu are bilet!");
		return false;
	}

	p->efectueazaCheckIn(numar);
	return true;
}

bool adaugaBagaj(CompanieAeriana& companie) {
	UI::subtitlu("ADAUGARE BAGAJ");

	std::string numar, nume;
	std::cout << "Numar zbor: ";
	std::cin >> numar;
	std::cin.ignore();

	Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}

	std::cout << "Nume pasager: ";
	std::getline(std::cin, nume);

	const Pasager* p = z->cautaPasagerDupaNume(nume);
	if (!p) {
		mesajEroare("Pasager negasit!");
		return false;
	}

	if (!p->areCheckIn()) {
		mesajEroare("Pasagerul nu are check-in efectuat!");
		return false;
	}

	std::cout << "\nTipuri bagaj:\n";
	std::cout << "1. De mana (10kg, gratis)\n";
	std::cout << "2. Cabina (10kg, 20 EUR)\n";
	std::cout << "3. Cala mic (23kg, 35 EUR)\n";
	std::cout << "4. Cala mare (32kg, 50 EUR)\n";

	int tipBagaj;
	double greutate;

	std::cout << "Tip bagaj: ";
	std::cin >> tipBagaj;
	std::cout << "Greutate (kg): ";
	std::cin >> greutate;

	TipBagaj tip;
	switch (tipBagaj) {
		case 1: tip = TipBagaj::DE_MANA; break;
		case 2: tip = TipBagaj::CABINA; break;
		case 3: tip = TipBagaj::CALA_MIC; break;
		case 4: tip = TipBagaj::CALA_MARE; break;
		default:
			mesajEroare("Tip invalid!");
			return false;
	}

	Bagaj bagaj(tip, greutate);
	std::cout << "\n" << bagaj << "\n";

	char confirma;
	std::cout << "\nAdaugi bagajul? (y/n): ";
	std::cin >> confirma;

	if (confirma == 'y' || confirma == 'Y') {
		p->getCheckIn()->adaugaBagaj(bagaj);
	} else {
		mesajInfo("Bagaj neadaugat.");
	}
	return true;
}

bool afiseazaDetaliiCheckIn(CompanieAeriana& companie) {
	UI::subtitlu("DETALII CHECK-IN");

	std::string numar, nume;
	std::cout << "Numar zbor: ";
	std::cin >> numar;
	std::cin.ignore();

	Zbor* z = companie.cautaZborDupaNumar(numar);
	if (!z) {
		mesajEroare("Zbor negasit!");
		return false;
	}

	std::cout << "Nume pasager: ";
	std::getline(std::cin, nume);

	const Pasager* p = z->cautaPasagerDupaNume(nume);
	if (!p) {
		mesajEroare("Pasager negasit!");
		return false;
	}

	if (!p->areCheckIn()) {
		mesajEroare("Pasagerul nu are check-in efectuat!");
		return false;
	}

	std::cout << *(p->getCheckIn()) << "\n";
	return true;
}

void PrintMeniu () {
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
	std::cout << "14. Check-in pasager\n";
	std::cout << "15. Adauga bagaj la check-in\n";
	std::cout << "16. Afiseaza detalii check-in\n";
	std::cout <<"0. Salveaza si iesi:\n";
}

int main() {
	CompanieAeriana companie("Wizz");
	UI::titlu(std::cout, "SISTEM MANAGEMENT ZBORURI - WIZZ AIR", '=', 70);

	// Populare date cu gestionare exceptii
	try {
		populareDate(companie);
	}
	catch (const ExceptieZboruri& e) {
		mesajEroare(std::string("La populare: ") + e.what());
		return 0;
	}

	int optiune ;
	while (true) {
		PrintMeniu();

		std::cin >> optiune;
		if (optiune == 0) {
			UI::subtitlu("SALVARE DATE");
			saveData(companie, "date.txt");
			break;
		}

		try {
			switch (optiune) {
				case 1:
					std::cout << "\n" << companie << "\n";
					break;
				case 2:
					adaugaZbor(companie);
					break;
				case 3:
					cautaZbor(companie);
					break;
				case 4:
					adaugaPasager(companie);
					break;
				case 5:
					cautaPasager(companie);
					break;
				case 6:
					modificaPoarta(companie);
					break;
				case 7:
					modificaLocBilet(companie);
					break;
				case 8:
					calculeazaIncasari(companie);
					break;
				case 9:
					verificaLocGeam(companie);
					break;
				case 10:
					verificaZborPlin(companie);
					break;
				case 11:
					upgradeBilet(companie);
					break;
				case 12:
					sorteazaZboruri(companie);
					break;
				case 13:
					filtreazaZboruri(companie);
					break;
				case 14:
					checkInPasager(companie);
					break;
				case 15:
					adaugaBagaj(companie);
					break;
				case 16:
					afiseazaDetaliiCheckIn(companie);
					break;

				default:
					mesajEroare("Optiune invalida!");
			}
		}
		catch (const ExceptieZboruri& e) {
			mesajEroare(e.what());
		}
	}
	mesajInfo("La revedere! Sa aveti o zi buna!");

	return 0;
}
