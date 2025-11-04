#pragma once
#include <string>
#include <iostream>

class Bilet {
private:
    int biletID;
    std::string loc;
    std::string tipClasa;
    double pretBaza;
    int discountProcent;


    static int counterID;
    const static double TAXA_AEROPORT; //taxa fixa de aeroport

    //verificam daca locul are 2-3 caractere
    static bool esteLocValid(const std::string& Loc);

public:
    Bilet();
    Bilet(const std::string& Loc, const std::string& tipClasa, double pretBaza);

    void setLoc(const std::string& nouLoc);

    double getPretFinal() const; // dupa taxe si discount-uri
    void aplicaDiscount(int procent);
    bool isWindowSeat() const;

    friend std::ostream& operator<<(std::ostream& COUT, const Bilet& b);

};