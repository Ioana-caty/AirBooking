#include "../headers/Pasager.h"
#include "../headers/Bilet.h"
#include "../headers/Zbor.h"
#include "../headers/Exceptii.h"
#include "../input/populareDate.h"
#include <iostream>
#include <fstream>
#include <string>

void populareDate(CompanieAeriana &companie) {
	std::cout << "---POPULARE DATE---\n";

	const std::string FISIER_DATE = "tastatura.txt";
	std::ifstream fin(FISIER_DATE);

	if (!fin.is_open()) {
		std::cerr << "EROARE: Nu s-a putut deschide fisierul 'tastatura.txt'\n";
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
					std::cerr << "[EROARE] pasager " << nume << ": " << e.what() << "\n";
				}
			}
			companie.adaugaZbor(zbor);
		}
		catch (const ExceptieZboruri& e) {
			std::cerr << "[EROARE] zbor " << codZbor << ": " << e.what() << "\n";
		}
	}
	fin.close();
	std::cout << "S-au implementat datele din fisier!\n";
}
