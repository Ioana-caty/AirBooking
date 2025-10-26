#pragma once

#include <string>
#include <iostream>


class Bilet {
private:
    int biletID;
    std::string loc;        //14A
    std::string tipClasa;   //Economic, Business
    double pretBaza;
    int discountProcent;

    //Membrii statici
    static int counterID;
    const static double TAXA_AEROPORT;

    bool esteLocValid(const std::string& loc) const;

public:
    Bilet();
    Bilet(const std::string& nouLoc, const std::string& tipClasa, double pretBaza);

    std::string getLoc() const;
    void setLoc(const std::string& nouLoc);


    // Functii netrivale
    double getPretFinal() const; // dupa taxe si discount-uri
    void aplicaDiscount(int procent);
    bool isWindowSeat() const;

    // Supraincarcare
    friend std::ostream& operator<<(std::ostream& COUT, const Bilet& b);

};