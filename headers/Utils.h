#pragma once
#include <sstream>
#include <string>
#include <algorithm>	// STL: transform, sort, find, max_element, ..
#include <cctype>		// conversion: isdifit, islower ...
#include <iomanip>		// setprecision()
#include <iostream>
#include "Passenger.h"

namespace Validation {

	inline bool isFormatValid(const std::string& str, bool firstDigit) {
		if (str.length() < 2 || str.length() > 3) {
			return false;
		}
		if (firstDigit) {
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

namespace Format {
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

	inline std::string getFormattedPrice(double sum) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << sum << " EUR";
		return oss.str();
	}

}

namespace UI {
	inline void Line(std::ostream& file, char caracter = '=', int length = 70) {
		file << std::string(length, caracter) << "\n";
	}

	inline void titlu(std::ostream& file, const std::string& text, char character = '=', int length = 70) {
		Line(file, character, length);
		file << " " << text << "\n";
		Line(file, character, length);
	}

	inline void PrintPasager(std::ostream& file, const Passenger& p, char character = '=', int length = 70) {
		Line(file, character, length);
		file << p << "\n";
		Line(file, character, length);
	}

	inline void Subtitle(const std::string& text) {
		std::cout << "\n--- " << text << " ---\n";
	}

	inline void successMessage(const std::string& text) {
		std::cout << "[OK] " << text << "\n";
	}

	inline void errorMessage(const std::string& text) {
		std::cerr << "[x] ERROR: " << text << "\n";
	}

	inline void infoMessage(const std::string& text) {
		std::cout << "[info] " << text << "\n";
	}

	inline void progressBar(int curr, int total, int length = 40) {
		if (total == 0) return;

		float progress = (float) curr / total;
		int position = length * progress;

		std::cout << "[";
		for (int i = 0; i < length; ++i) {
			if (i < position) std::cout << "||";
			else std::cout << "*";
		}
		std::cout << "] " << (int)(progress * 100.0) << "%\r";
		std::cout.flush();
	}
}

using Format::toUpperCase;
using Format::toLowerCase;
using Validation::isFormatValid;

using UI::successMessage;
using UI::errorMessage;
using UI::infoMessage;
