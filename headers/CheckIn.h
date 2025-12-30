#pragma once
#include <string>
#include <vector>
#include "Bagaj.h"
#include "../headers/Bilet.h"


class CheckIn {
private:
	std::string numePasager;
	std::string numarZbor;
	std::string loc;
	std::vector<Bagaj> bagaje;

	Bilet* biletPasager;

public:
	CheckIn(const std::string& pasager, const std::string& zbor, const std::string& loc, Bilet* bilet);

	void adaugaBagaj(const Bagaj& bagaj);
	double getGreutateTotala() const;
	double getTaxeTotaleBagaje() const;

	friend std::ostream& operator<<(std::ostream& os, const CheckIn& c);
};