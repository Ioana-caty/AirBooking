#include <iomanip>
#include <iostream>
#include "Pasager.h"
#include "Bilet.h"
#include "Zbor.h"

int main() {

    /*// 1. Testare constructor cu parametri si operator<<
    std::cout << "\n1. Creare p1 (constructor cu parametri):" << std::endl;
    Pasager p1("Mihai Eminescu", "m.eminescu@poet.ro");
    std::cout << "   " << p1 << std::endl;

    // 2. Testare constructor default
    std::cout << "\n2. Creare p2 (constructor default):" << std::endl;
    Pasager p2;
    std::cout << "   " << p2 << std::endl;

    // 3. Testare Constructor de Copiere
    std::cout << "\n3. Creare p3 (constructor de copiere, p3 = p1):" << std::endl;
    Pasager p3 = p1; // Pasager p3(p1);
    std::cout << "   " << p3 << std::endl;

    // 4. Testare Operator= (de atribuire)
    std::cout << "\n4. Testare operator= (atribuire, p2 = p1):" << std::endl;
    p2 = p1;
    std::cout << "   " << p2 << std::endl;


    // 5. Testare auto-atribuire
    std::cout << "\n5. Testare auto-atribuire (p1 = p1):" << std::endl;
    Pasager* pointer = &p1;
    p1 = *pointer;
    std::cout << "   " << p1 << std::endl;

    // 6. Testare Getters
    std::cout << "\n6. Testare Getters (pentru p3):" << std::endl;
    std::cout << "   Nume: " << p3.getNume() << std::endl;
    std::cout << "   Email: " << p3.getEmail() << std::endl;

    //7. Testare destructori*/


    /* BILETE
    // 1. CONSTRUCTOR + OPERATOR
    std::cout << "\n1. Creare b1 cu constructor cu parametri:" << std::endl;
    Bilet b1("14A", "Business", 250.0);
    std::cout << "  " << b1 << std::endl;

    //2.CONSTRUCTOR DEFAULT
    std::cout << "\n2. Creare b2 cu constructor default: " << std::endl;
    Bilet b2;
    std::cout << "  " << b2 << std::endl;

    //3. SETTERS
    b2.setTipClasa("Economic");
    b2.setLoc("22C");
    b2.setPretBaza(99.90);
    std::cout << "   SETTERS b2: " << b2 << std::endl;

    b2.setPretBaza(-52);
    std::cout << b2 << std::endl;
    b2.setLoc("11111A");
    std::cout << b2 << std::endl;

    //Functii netriviale
    std::cout << "\nEste locul lui b1(" << b1.getLoc() << ") la geam?";
    std::cout << (b1.isWindowSeat() ? " DA" : " NU") << std::endl;

    Bilet b3("10F", "Economic", 100);
    std::cout << "Este locul lui b3(" << b3.getLoc() << ") la geam?";
    std::cout << (b3.isWindowSeat() ? " DA" : " NU") << std::endl;

    b2.setLoc("15B");
    std::cout << "Este locul lui b2(" << b2.getLoc() << ") la geam?";
    std::cout << (b2.isWindowSeat() ? " DA" : " NU") << std::endl;

    std::cout << "\nPret inital b1: " << b1.getPretBaza();
    b1.aplicaDiscount(150);
    b1.aplicaDiscount(25);
    std::cout << "Pretul lui b1 schimbat: " << b1.getPretFinal() ;
    */


    /*
    //PASAGER + BILET
    Bilet b1("25C", "Economic", 120.50);
    b1.aplicaDiscount(10);
    std::cout << "Informatii bilet: " << b1 << std::endl;
    Pasager p1("Tudor Deaconu", "t.deaconu@gamil.com", b1);
    std::cout <<"Informatii pasager1:\n   " << p1 << std::endl;

    Bilet b2("17A", "Economic", 200);
    b2.aplicaDiscount(0);
    Pasager p2("Iustina Caramida", "i.caramida@gmail.com", b2);
    std::cout <<"Informatii pasager2:\n   " << p2 << std::endl;

    p2 = p1;
    std::cout << "\nInformatii pasager2:\n  " << p2 << std::endl;

    Pasager p3;
    std::cout << "\nInformatii pasager3:\n  " << p3 << std::endl;
    p3 = p1;
    std::cout << "Noile informatii ale pasagerului3:\n  " << p3 << std::endl;
    */

    Bilet b1("10A", "Buisness", 300.0);
    Bilet b2("22B", "Economic", 80.0);
    b2.aplicaDiscount(50);
    Bilet b3("22C", "Economic", 80.0);

    Pasager p1("Tudor Deaconu", "t.deaconu@gmail.com", b1);
    Pasager p2("Iustina Caramida", "i.caramida@gmail.com", b2);
    Pasager p3("Costi Sin", "sin.costin@gmail.com", b3);

    Zbor zborRO256("RO256", "Paris", "A12");
    zborRO256.adaugaPasager(p2);
    zborRO256.adaugaPasager(p1);
    zborRO256.adaugaPasager(p3);
    std::cout<< zborRO256 << std::endl;
    std::cout << std::fixed << std::setprecision(2) << zborRO256.calculeazaIncasariTotale() << " EUR" << std::endl;

    Pasager* pGasit = zborRO256.cautaPasagerDupaNume("Iustina Caramida");
    if (pGasit != nullptr) {
        std::cout << "Gasit: " << *pGasit << std::endl;
    }

    std::cout << "Poarta initiala: " << zborRO256.getPoarta() << std::endl;
    zborRO256.setPoarta("C5");
    std::cout << "Poarta finala: " << zborRO256.getPoarta() << std::endl;

    return 0;
}