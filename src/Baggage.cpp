#include "../headers/Baggage.h"
#include "../headers/Utils.h"

Baggage::Baggage()
    : type(BaggageType::PERSONAL_ITEM), weight(5.0) {}

Baggage::Baggage(BaggageType type, double weight)
    : type(type), weight(weight) {}

bool Baggage::isOverweight() const {
    switch(type) {
        case BaggageType::PERSONAL_ITEM:
            return weight > 10.0;
        case BaggageType::CARRY_ON:
            return weight > 10.0;
        case BaggageType::CHECKED_SMALL:
            return weight > 23.0;
        case BaggageType::CHECKED_LARGE:
            return weight > 32.0;
    }
    return false;
}

double Baggage::getBaggageFee() const {
    switch(type) {
        case BaggageType::PERSONAL_ITEM:
            return 0.0;
        case BaggageType::CARRY_ON:
            return 20.0;
        case BaggageType::CHECKED_SMALL:
            return 35.0;
        case BaggageType::CHECKED_LARGE:
            return 50.0;
    }
    return 0.0;
}

double Baggage::getExtraFee() const {
    if (!isOverweight()) {
        return 0.0;
    }

    double extraWeight = 0.0;

    switch(type) {
        case BaggageType::PERSONAL_ITEM:
        case BaggageType::CARRY_ON:
            extraWeight = weight - 10.0;
            break;
        case BaggageType::CHECKED_SMALL:
            extraWeight = weight - 23.0;
            break;
        case BaggageType::CHECKED_LARGE:
            extraWeight = weight - 32.0;
            break;
    }

    return extraWeight * 15.0;
}

std::string Baggage::getTypeString() const {
    switch(type) {
        case BaggageType::PERSONAL_ITEM: return "Personal Item";
        case BaggageType::CARRY_ON: return "Carry-on";
        case BaggageType::CHECKED_SMALL: return "Checked (23kg)";
        case BaggageType::CHECKED_LARGE: return "Checked (32kg)";
    }
    return "Unknown";
}

std::ostream& operator<<(std::ostream& os, const Baggage& b) {
    os << "Baggage: " << b.getTypeString() << "\n";
    os << "  Weight: " << b.weight << " kg";

    if (b.isOverweight()) {
        os << " [OVERWEIGHT!]";
    }
    os << "\n";

    os << "  Baggage fee: " << Format::getFormattedPrice(b.getBaggageFee()) << "\n";

    if (b.getExtraFee() > 0) {
        os << "  Extra fee: " << Format::getFormattedPrice(b.getExtraFee()) << "\n";
    }

    os << "  Total: " << Format::getFormattedPrice(b.getBaggageFee() + b.getExtraFee());

    return os;
}