#include "../headers/Bagaj.h"
#include "../headers/Utils.h"
#include <iostream>

Bagaj::Bagaj()
    : tip(TipBagaj::DE_MANA), greutate(5.0) {}

Bagaj::Bagaj(TipBagaj tip, double greutate)
    : tip(tip), greutate(greutate) {}

bool Bagaj::esteSupraponderal() const {
    switch(tip) {
        case TipBagaj::DE_MANA:
            return greutate > 10.0;
        case TipBagaj::CABINA:
            return greutate > 10.0;
        case TipBagaj::CALA_MIC:
            return greutate > 23.0;
        case TipBagaj::CALA_MARE:
            return greutate > 32.0;
    }
    return false;
}

double Bagaj::getTaxaBagaj() const {
    switch(tip) {
        case TipBagaj::DE_MANA:
            return 0.0;
        case TipBagaj::CABINA:
            return 20.0;
        case TipBagaj::CALA_MIC:
            return 35.0;
        case TipBagaj::CALA_MARE:
            return 50.0;
    }
    return 0.0;
}

double Bagaj::getTaxaExtra() const {
    if (!esteSupraponderal()) {
        return 0.0;
    }

    double greutateExtra = 0.0;

    switch(tip) {
        case TipBagaj::DE_MANA:
        case TipBagaj::CABINA:
            greutateExtra = greutate - 10.0;
            break;
        case TipBagaj::CALA_MIC:
            greutateExtra = greutate - 23.0;
            break;
        case TipBagaj::CALA_MARE:
            greutateExtra = greutate - 32.0;
            break;
    }

    return greutateExtra * 15.0;
}

std::string Bagaj::getTipString() const {
    switch(tip) {
        case TipBagaj::DE_MANA: return "De mana";
        case TipBagaj::CABINA: return "Cabina";
        case TipBagaj::CALA_MIC: return "Cala (23kg)";
        case TipBagaj::CALA_MARE: return "Cala (32kg)";
    }
    return "Necunoscut";
}

std::ostream& operator<<(std::ostream& os, const Bagaj& b) {
    os << "Bagaj: " << b.getTipString() << "\n";
    os << "  Greutate: " << b.greutate << " kg";

    if (b.esteSupraponderal()) {
        os << " [SUPRAPONDERAL!]";
    }
    os << "\n";

    os << "  Taxa bagaj: " << Formatare::formatareMoneda(b.getTaxaBagaj()) << "\n";

    if (b.getTaxaExtra() > 0) {
        os << "  Taxa extra: " << Formatare::formatareMoneda(b.getTaxaExtra()) << "\n";
    }

    os << "  Total: " << Formatare::formatareMoneda(b.getTaxaBagaj() + b.getTaxaExtra());

    return os;
}