#pragma once
#include <string>
#include <algorithm>	//STL: transform, sort, find, max_element..
#include <cctype>		//conversii: isdifit, islower ...
#include <iomanip>		// setprecision()
#include <sstream>		// std::ostringstream
#include <iostream>

namespace Validari {
	//cifreIntai = true => Format: "12A"
	//cifreIntai = false => Format: "A12"
	inline bool esteFormatValid(const std::string& str, bool cifreIntai) {
		if (str.length() < 2 || str.length() > 3) {
			return false;
		}
		if (cifreIntai) {
			for (size_t i = 0; i < str.length() - 1; i++) {
				if (!std::isdigit(str[i])) {
					return false;
				}
			}
			return std::isupper(str.back());
		} else {
			if (!std::isupper(str[0])) {
				return false;
			}
			for (size_t i = 1; i < str.length(); i++) {
				if (!std::isdigit(str[i])) {
					return false;
				}
			}
			return true;
		}
	}
}

namespace Formatare {
	inline std::string toUpperCase(const std::string& str) {
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(),
					   [](unsigned char c){ return std::toupper(c); });
		return result;
	}

	inline std::string toLowerCase(const std::string& str) {
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(),
					   [](unsigned char c){ return std::tolower(c); });
		return result;
	}

	inline std::string formatareMoneda(double suma) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << suma << " EUR";
		return oss.str();
	}

	inline std::string formatareProcent(double procent) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(1) << procent << "%";
		return oss.str();
	}
}

namespace UI {
	inline void Linie(char caracter = '=', int lungime = 70) {
		std::cout << std::string(lungime, caracter) << "\n";
	}

	inline void titlu(const std::string& text) {
		Linie('=', 70);
		std::cout << " " << text << "\n";
		Linie('=', 70);
	}

	inline void subtitlu(const std::string& text) {
		std::cout << "\n--- " << text << " ---\n";
	}

	inline void mesajSucces(const std::string& text) {
		std::cout << "[OK] " << text << "\n";
	}

	inline void mesajEroare(const std::string& text) {
		std::cerr << "[x] EROARE: " << text << "\n";
	}

	inline void mesajInfo(const std::string& text) {
		std::cout << "[info] " << text << "\n";
	}

	inline void baraProgres(int curent, int total, int lungime = 40) {
		if (total == 0) return;

		float progres = (float)curent / total;
		int pozitie = lungime * progres;

		std::cout << "[";
		for (int i = 0; i < lungime; ++i) {
			if (i < pozitie) std::cout << "█";
			else std::cout << "░";
		}
		std::cout << "] " << (int)(progres * 100.0) << "%\r";
		std::cout.flush();
	}
}

using Formatare::toUpperCase;
using Formatare::toLowerCase;
using Validari::esteFormatValid;

using UI::mesajSucces;
using UI::mesajEroare;
using UI::mesajInfo;


