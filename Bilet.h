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
    Bilet(const std::string& loc, const std::string& tipClasa, double pretBaza);

    int getBiletID() const;
    std::string getLoc() const;
    std::string getTipClasa() const;
    double getPretBaza() const;
    int getDiscountProcent() const;

    void setLoc(const std::string& loc);
    void setTipClasa(const std::string& tipClasa);
    void setPretBaza(double pretBaza);

    double getPretFinal() const; // dupa taxe si discount-uri
    void aplicaDiscount(int procent);
    bool isWindowSeat() const;

    friend std::ostream& operator<<(std::ostream& COUT, const Bilet& b);

};