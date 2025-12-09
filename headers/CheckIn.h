#pragma once
#include <string>
#include <vector>
#include "Bagaj.h"

class CheckIn {
private:
	std::string numePasager;
	std::string numarZbor;
	std::string loc;
	std::vector<Bagaj> bagaje;

public:
	CheckIn(const std::string& pasager, const std::string& zbor, const std::string& loc);

	void adaugaBagaj(const Bagaj& b);
	double getGreutateTotala() const;
	double getTaxeTotaleBagaje() const;

	friend std::ostream& operator<<(std::ostream& os, const CheckIn& c);
};