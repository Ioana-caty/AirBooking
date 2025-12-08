#pragma once
#include <exception>
#include <string>

class ExceptieZboruri : public std::exception {
protected:
	std::string mesaj;
public:
	explicit ExceptieZboruri(const std::string& msg) : mesaj(msg) {}
	const char* what() const noexcept {
		return mesaj.c_str();
	}
};

class ExceptieValidare : public ExceptieZboruri {
public:
	ExceptieValidare(const std::string& msg) : ExceptieZboruri(msg) {}
};

class ExceptieCapacitate : public ExceptieZboruri {
public:
	ExceptieCapacitate(const std::string& msg) : ExceptieZboruri(msg) {}
};

class ExceptieOperatie : public ExceptieZboruri {
public:
	ExceptieOperatie(const std::string& msg) : ExceptieZboruri(msg) {}
};