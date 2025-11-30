#pragma once
#include <iostream>
#include <algorithm>
#include "../headers/Bilet.h"

class BiletFactory {
public:
	static Bilet* creeazaBilet(const std::string& tipClasa, const std::string& Loc, double pretBaza, int discountProcent) {
		std::string tip = toLower(tipClasa);
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
		} else {
			std::cerr << "Clasa necunoscuta: " << tipClasa << ", se foloseste Economic\n";
			return new BiletEconomic(Loc, pretBaza, discountProcent);
		}
	}

private:
	static std::string toLower(const std::string& str) {
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(),
					  [](unsigned char c){ return std::tolower(c); });
		return result;
	}
};
