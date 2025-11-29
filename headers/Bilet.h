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
    Bilet(const std::string& Loc, double pretBaza);

	Bilet(const Bilet& other);
	Bilet& operator=(const Bilet& other);

    void setLoc(const std::string& nouLoc);
    void aplicaDiscount(int procent);
    bool isWindowSeat() const;

	int getBiletID() const { return biletID; }
	std::string getLoc() const { return loc; }
	double getPretBaza() const { return pretBaza; }

	virtual double getPretFinal() const = 0;
	virtual std::string getTipClasa() const = 0;
	virtual Bilet* clone() const = 0;

	virtual ~Bilet();
    friend std::ostream& operator<<(std::ostream& COUT, const Bilet& b);
};


class BiletEconomic : public Bilet {
private:
	static const double TAXA_EXTRA;
public:
	BiletEconomic();
	BiletEconomic(const std::string& Loc, double pretBaza);

	virtual double getPretFinal() const override;
	virtual std::string getTipClasa() const override;
	virtual Bilet* clone() const override;

	~BiletEconomic();
};

class BiletBusiness : public Bilet {
private:
	static const double TAXA_CONFORT;
	bool accesLounge;
public:
	BiletBusiness();
	BiletBusiness(const std::string& Loc, double pretBaza, bool accesLounge = true);

	virtual double getPretFinal() const override;
	virtual std::string getTipClasa() const override;
	virtual Bilet* clone() const override;

	bool getAccesLounge() const { return accesLounge; }
	void setAccesLounge(bool acces) { accesLounge = acces; }

	~BiletBusiness();
};


class BiletFirstClass : public Bilet {
private:
	static const double TAXA_LUXURY;
	bool servireMasa;
	bool prioritateImbracare;
public:
	BiletFirstClass();
	BiletFirstClass(const std::string& Loc, double pretBaza,
					bool servireMasa = true, bool prioritateImbarcare = true);

	virtual double getPretFinal() const override;
	virtual std::string getTipClasa() const override;
	virtual Bilet* clone() const override;

	bool getServireMasa() const { return servireMasa; }
	bool getPrioritateImbarcare() { return prioritateImbracare; }

	~BiletFirstClass();
};