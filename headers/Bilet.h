#pragma once
#include <string>
#include <iostream>

class Bilet {
protected:
    int biletID;
    std::string loc;
    double pretBaza;
    int discountProcent;

    static int counterID;
    const static double TAXA_AEROPORT;

    static bool esteLocValid(const std::string& Loc);

public:
    Bilet();
    Bilet(const std::string& Loc, double pretBaza, int discountProcent);

	Bilet(const Bilet& other);
	Bilet& operator=(const Bilet& other);

    void setLoc(const std::string& nouLoc);
    bool isWindowSeat() const;

	const std::string& getLoc() const {return loc; }
	double getPretBaza() const { return pretBaza; }
	int getDiscountProcent() const { return discountProcent; }

	virtual double getPretFinal() const = 0;
	virtual std::string getTipClasa() const = 0;
	virtual Bilet* clone() const = 0;

	virtual ~Bilet();
    friend std::ostream& operator<<(std::ostream& COUT, const Bilet& b);
};

// DERIVATA1 : BILET ECONOMIC
class BiletEconomic : public Bilet {
private:
	static const double TAXA_EXTRA;
public:
	BiletEconomic();
	BiletEconomic(const std::string& Loc, double pretBaza, int discountProcent);

	double getPretFinal() const override;
	std::string getTipClasa() const override;
	Bilet* clone() const override;

	~BiletEconomic() override;
};

// DERIVATA2 : BILET BUSINESS
class BiletBusiness : public Bilet {
private:
	static const double TAXA_CONFORT;
	bool accesLounge;
public:
	BiletBusiness();
	BiletBusiness(const std::string& Loc, double pretBaza, int discountProcent, bool accesLounge = true);

	double getPretFinal() const override;
	std::string getTipClasa() const override;
	Bilet* clone() const override;

	// bool getAccesLounge() const { return accesLounge; }
	// void setAccesLounge(bool acces) { accesLounge = acces; }

	~BiletBusiness() override;
};


class BiletFirstClass : public Bilet {
private:
	static const double TAXA_LUXURY;
	bool servireMasa;
	bool prioritateImbracare;
public:
	BiletFirstClass();
	BiletFirstClass(const std::string& Loc, double pretBaza, int discountProcent,
					bool servireMasa = true, bool prioritateImbarcare = true);

	double getPretFinal() const override;
	std::string getTipClasa() const override;
	Bilet* clone() const override;

	~BiletFirstClass() override;
};