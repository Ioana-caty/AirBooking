#pragma once
#include <string>

enum class TipBagaj {
	DE_MANA,
	CABINA,
	CALA_MIC,
	CALA_MARE
};

class Bagaj {
private:
	TipBagaj tip;
	double greutate;

public:
	Bagaj();
	Bagaj(TipBagaj tip, double greutate);

	TipBagaj getTip() const { return tip; }
	double getGreutate() const { return greutate; }

	bool esteSupraponderal() const;
	double getTaxaBagaj() const;      
	double getTaxaExtra() const;
	std::string getTipString() const;

	friend std::ostream& operator<<(std::ostream& os, const Bagaj& b);
};