#include "../headers/Pasager.h"
#include "../headers/Bilet.h"
#include "../headers/Zbor.h"
#include "../headers/Exceptii.h"
#include "../input/populareDate.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>


void populareDate(CompanieAeriana &companie) {
	UI::subtitlu("POPULARE DATE");

	const std::string FISIER_DATE = "tastatura.txt";
	std::ifstream fin(FISIER_DATE);

	if (!fin.is_open()) {
		mesajEroare("Nu s-a putut deschide fisierul 'tastatura.txt'");
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

		try {
			Zbor zbor(codZbor, destinatie, poarta, capacitateMaxima);

			int numarPasageri;
			fin >> numarPasageri;
			fin.ignore();

			for (int j = 0; j < numarPasageri; j++) {
				std::string nume, email, loc, tipClasa;
				double pretBaza, discount;

				std::getline(fin, nume);
				nume = toUpperCase(nume);
				std::getline(fin, email);
				fin >> loc >> tipClasa >> pretBaza >> discount;
				fin.ignore();

				try {
					Bilet* bilet = nullptr;
					if (tipClasa == "Economic") {
						bilet = new BiletEconomic(loc, pretBaza, discount);
					} else if (tipClasa == "Business") {
						bilet = new BiletBusiness(loc, pretBaza, discount);
					} else if (tipClasa == "FirstClass") {
						bilet = new BiletFirstClass(loc, pretBaza, discount);
					} else {
						std::cerr << "Clasa necunoscuta: " << tipClasa << ", se foloseste Economic\n";
						bilet = new BiletEconomic(loc, pretBaza, discount);
					}

					Pasager pasager(nume, email, bilet);
					zbor.adaugaPasager(pasager);
				}
				catch (const ExceptieZboruri& e) {
					mesajEroare("Pasager " + nume + ": " + e.what());
				}
			}

			companie.adaugaZbor(zbor);
		}
		catch (const ExceptieZboruri& e) {
			mesajEroare("Zbor " + codZbor + ": " + e.what());
		}

		UI::baraProgres(i + 1, numarzboruri);
		// Folosește un tip de durată generic pentru a ocoli potentialele probleme de namespace
		// CORECT: Schimbați 'std::thread' cu 'std::this_thread'
		Sleep(2500);
	}

	UI::baraProgres(numarzboruri, numarzboruri);
	std::cout << "\n";

	fin.close();
	mesajSucces("Date implementate din fisier!");
}