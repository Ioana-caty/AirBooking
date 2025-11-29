#pragma once
#include <iostream>
#include <string>
#include "../headers//Bilet.h"

class Pasager {
private:
    std::string nume;
    std::string email;
    int pasagerID;
    static int counterID;

    Bilet* bilet;
	/*
		- ne putem referi acum la BiletEconomic, BiletBusiness, BiletFirstClass
		- putem sa facem polimorfism
	 */

public:
    Pasager(const std::string& nume, const std::string& Email, Bilet* biletNou);
    Pasager();

    Pasager(const Pasager& another);
    Pasager& operator=(const Pasager& another);

    const std::string& getNume() const;
    const Bilet* getBilet() const;
    void setBilet(const Bilet* biletNou);

	virtual ~Pasager();
    friend std::ostream& operator<<(std::ostream&os, const Pasager& p);
};