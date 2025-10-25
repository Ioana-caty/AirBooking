#pragma once

#include <string>
#include <iostream>
#include <ostream>

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
    // Constructor default
    Bilet();

    //Constructor cu parametri
    Bilet(const std::string& loc, const std::string& tipClasa, double pretBaza);

    // Getters
    int getBiletID() const;
    std::string getLoc() const;
    std::string getTipClasa() const;
    double getPretBaza() const;
    int getDiscountProcent() const;

    // Setters
    void setLoc(const std::string& loc);
    void setTipClasa(const std::string& tipClasa);
    void setPretBaza(double pretBaza);

    // Functii netrivale
    double getPretFinal() const; // dupa taxe si discount-uri
    void aplicaDiscount(int procent);
    bool isWindowSeat() const;

    // Supraincarcare
    friend std::ostream& operator<<(std::ostream& COUT, const Bilet& b);

};