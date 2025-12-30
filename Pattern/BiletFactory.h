#pragma once
#include <iostream>
#include "../headers/Bilet.h"
#include "../headers/Utils.h"

class BiletFactory {
public:
	static Bilet* creeazaBilet(const std::string& tipClasa, const std::string& Loc, double pretBaza, int discountProcent) {
		std::string tip = toLowerCase(tipClasa);
		if (tip == "economic") {
			return new BiletEconomic(Loc, pretBaza, discountProcent);
		} else if (tip == "business") {
			bool accesLounge = false;
			std::cout << "Acces lounge (1-DA/0-NU): ";
			std::cin >> accesLounge;
			return new BiletBusiness(Loc, pretBaza, discountProcent, accesLounge);
		} else if (tip == "firstclass") {
			bool servireMasa, prioritate;
			std::cout << "Servire masa (1-DA/0-NU): ";
			std::cin >> servireMasa;
			std::cout << "Prioritate imbarcare (1-DA/0-NU): ";
			std::cin >> prioritate;
			return new BiletFirstClass(Loc, pretBaza, discountProcent, servireMasa, prioritate);
		} else if (tip == "premium") {
			bool bautura, prioritate;
			std::cout << "Bautura gratuita (1-DA/0-NU): ";
			std::cin >> bautura;
			std::cout << "Prioritate imbarcare (1-DA/0-NU): ";
			std::cin >> prioritate;
			return new BiletPremium(Loc, pretBaza, discountProcent, bautura, prioritate);
		} else {
			std::cerr << "Clasa necunoscuta: " << tipClasa << ", se foloseste Economic\n";
			return new BiletEconomic(Loc, pretBaza, discountProcent);
		}
	}
};
