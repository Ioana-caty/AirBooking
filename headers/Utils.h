#pragma once
#include <string>
#include <algorithm>
#include <cctype>

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

inline bool esteFormatValid(const std::string& str, bool cifreIntai) {
	if (str.length() < 2 || str.length() > 3) {
		return false;
	}

	if (cifreIntai) {
		// Format: 1-2 cifre + literă (ex: "12A", "5B")
		for (size_t i = 0; i < str.length() - 1; i++) {
			if (!std::isdigit(str[i])) {
				return false;
			}
		}
		return std::isupper(str.back());
	} else {
		// Format: literă + 1-2 cifre (ex: "A12", "B5")
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