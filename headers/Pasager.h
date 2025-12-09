#pragma once
#include <iostream>
#include <string>
#include "../headers/Bilet.h"

class CompanieAeriana;

class Pasager {
private:
	std::string nume;
	std::string email;
	int pasagerID;
	static int counterID;

	Bilet* bilet;

public:
	Pasager(const std::string& nume, const std::string& Email, Bilet* biletNou);
	Pasager();

	Pasager(const Pasager& another);
	Pasager& operator=(const Pasager& another);

	bool areBilet() const { return bilet != nullptr; }
	bool corespundeNumelui(const std::string& numeVerificat) const;
	void modificaLoc(const std::string& locNou);
	void actualizeazaBilet(const Bilet* biletNou);
	void incasari(double& total) const;

	~Pasager();

	friend class Zbor;
	friend std::ostream& operator<<(std::ostream&os, const Pasager& p);
	friend void saveData(const CompanieAeriana& companie, const std::string& nameFile);
};