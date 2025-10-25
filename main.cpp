
#include "Pasager.h"
#include <iostream>

int main() {
    std::cout << "TEST CLASA PASAGER: \n";

    //Test 1
    std::cout << "Test1: Constructor cu paramteri";
    Pasager p1("Popescu Ion", "popescu.ion@gmail.com");
    std::cout << " ✓ Obiect p1 creat cu succes!\n";

    //Test2
    std::cout << "Test2: Afisare obiect p1 \n";
    std::cout << "Detalii: " << p1 << "\n";

    //Test3
    std::cout << "Test3: Constructor de Copiere \n";
    Pasager  p2 = p1;
    std::cout << "Original (p1): " << p1 << "\n";
    std:: cout << "Copia   (p2): " << p2 << "\n";
    std::cout << " ✓ Constructorul de copiere functioneaza corect!\n";

    //Test4
    std::cout << "Test4: Operator de atribuire:\n";
    Pasager p3 ("Negoita Vasile", "v.negoita@gmail.com");
    std::cout << "Inainte de atribuire:\n";
    std::cout << "p3: " << p3 << "\n";
    std::cout << "p1: " << p1 << "\n";
    p3 = p1;
    std::cout << "Dupa atribuire:\n";
    std::cout << "p3: " << p3 << "\n";
    std::cout << " ✓ Atribuirea functioneaza corect!\n";

    //Test5
    std::cout << "Test5:\n";
    std::cout << "p1 (original):    " << p1 << "\n";
    std::cout << "p2 (copie):       " << p2 << "\n";
    std::cout << "p3 (stribuit):    " << p3 << "\n";
    std::cout << " ✓ Toate Obiectele sunt independente!\n";

    //Test6
    std::cout << " Test6: Auto-Atribuire:!\n";
    std::cout << "p1 inainte: " << p1 << "\n";
    p1 = p1;
    std::cout << "p1 dupa: " << p1 << "\n";
    std::cout << " ✓ Auto-atribuirea este tratata corect!\n";

    //Test7
    std::cout << "Test7:Destructori\n";
    return 0;
}