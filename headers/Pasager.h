#pragma once
#include <iostream>
#include <string>
#include "Bilet.h"

class CompanieAeriana;
class CheckIn;

class Pasager {
private:
	std::string nume;
	std::string email;
	int pasagerID;
	static int counterID;

	Bilet* bilet;
	CheckIn* checkIn;

public:
	Pasager(const std::string& nume, const std::string& Email, Bilet* biletNou);
	Pasager();

	Pasager(const Pasager& another);
	Pasager& operator=(const Pasager& another);

	const std::string& getNume() const { return nume; }
	const Bilet* getBilet() const { return bilet; }

	bool areBilet() const { return bilet != nullptr; }
	bool corespundeNumelui(const std::string& numeVerificat) const;
	void modificaLoc(const std::string& locNou);
	void actualizeazaBilet(const Bilet* biletNou);
	void incasari(double& total) const;

	bool areCheckIn() const { return checkIn != nullptr; }
	CheckIn* getCheckIn() const { return checkIn; }
	void efectueazaCheckIn(const std::string& numarZbor);

	~Pasager();

	friend std::ostream& operator<<(std::ostream&os, const Pasager& p);
	friend void saveData(const CompanieAeriana& companie, const std::string& nameFile);
};