#pragma once
#include <string>
#include <iostream>

class Bilet {
private:
    int biletID;
    std::string loc;                    //14A
    std::string tipClasa;               //Economic, Business
    double pretBaza;                    //fara taxe + discount
    int discountProcent;                // procent discount 0-80%

    //MEMBRII STATICI - comuni pentru toate biletele
    static int counterID;               //contor global pentru ID
    const static double TAXA_AEROPORT;  //taxa fixa de aeroport

    //verificam daca locul are 2-3 caractere
    static bool esteLocValid(const std::string& Loc);

public:
    Bilet();
    Bilet(const std::string& Loc, const std::string& tipClasa, double pretBaza);

    void setLoc(const std::string& nouLoc);

    // Functii netrivale
    double getPretFinal() const; // dupa taxe si discount-uri
    void aplicaDiscount(int procent);
    bool isWindowSeat() const;

    // Supraincarcare
    friend std::ostream& operator<<(std::ostream& COUT, const Bilet& b);

};