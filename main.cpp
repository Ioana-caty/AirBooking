#include <iostream>
#include "Pasager.h"

int main() {

    // 1. Testare constructor cu parametri si operator<<
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
    p1 = p1;
    std::cout << "   " << p1 << std::endl;

    // 6. Testare Getters
    std::cout << "\n6. Testare Getters (pentru p3):" << std::endl;
    std::cout << "   Nume: " << p3.getNume() << std::endl;
    std::cout << "   Email: " << p3.getEmail() << std::endl;

    //7. Testare destructori

    return 0;
}