#include "../headers/Ticket.h"
#include "../headers/Airline.h"
#include "../headers/Exceptions.h"
#include "../headers/Utils.h"
#include <iomanip>
#include <iostream>

int Ticket::counterID = 1000;
const double Ticket::AIRPORT_FEE = 15.75;
const double EconomyTicket::EXTRA_FEE = 3.0;
const double BusinessTicket::COMFORT_FEE = 35.5;
const double FirstClassTicket::LUXURY_FEE = 74.75;

Ticket::Ticket() : ticketID(counterID++), seat("N/A"), basePrice(0.0), discountPercentage(0.0) {}

Ticket::Ticket(const std::string &seat, double basePrice, int discountPercentage)
             : ticketID(counterID++), seat(seat), basePrice(basePrice >= 0 ? basePrice : 0.0), discountPercentage(discountPercentage) {

    if (this->discountPercentage < 0 || this->discountPercentage > 80) {
       throw ValidationException("Invalid discount: " + std::to_string(discountPercentage) + "% (allowed: 0-80%)");
    }

    if (!isSeatValid(seat)) {
       throw ValidationException("Invalid seat: " + seat + " (format: 1-2 digits + letter, e.g., 12A)");
    }
    this->seat = seat;

    if (basePrice < 0) {
       throw ValidationException("Invalid price: " + std::to_string(basePrice) + " EUR (must be >= 0)");
    }
}

Ticket::Ticket(const Ticket &other) : ticketID(other.ticketID), seat(other.seat), basePrice(other.basePrice), discountPercentage(other.discountPercentage) {}

Ticket & Ticket::operator=(const Ticket &other) {
    if (this == &other) {
       return *this;
    }

    this->ticketID = other.ticketID;
    this->seat = other.seat;
    this->basePrice = other.basePrice;
    this->discountPercentage = other.discountPercentage;

    return *this;
}

bool Ticket::isSeatValid(const std::string &seat) {
    return isFormatValid(seat, true);
}

bool Ticket::setSeat(const std::string &newSeat) {
    if (this->isSeatValid(toUpperCase(newSeat))) {
       this->seat = toUpperCase(newSeat);
       return true;
    } else {
       return false;
    }
}

std::ostream & operator<<(std::ostream &COUT, const Ticket &t) {
    COUT   << "Ticket [ID: " << t.ticketID
          << ", Seat: " << t.seat
          << ", Class: " << t.getClassType()
          << ", Final Price: ";
    if (t.basePrice <= 0) {
       COUT << "N/A";
    } else {
       COUT << Format::getFormattedPrice(t.getFinalPrice());
    }

    return COUT;
}
Ticket::~Ticket() {}

// ECONOMY:
EconomyTicket::EconomyTicket() : Ticket() {}
EconomyTicket::EconomyTicket(const std::string &seat, double basePrice, int discountPercentage) :
    Ticket(seat, basePrice, discountPercentage) {}

double EconomyTicket::getFinalPrice() const {
    const double priceWithFees = getBasePrice() + Ticket::AIRPORT_FEE + EconomyTicket::EXTRA_FEE;
    double discount = 0.0;
    if (getDiscountPercentage() > 0) {
       discount = priceWithFees * (static_cast<double>(getDiscountPercentage()) / 100.0);
    }
    return priceWithFees - discount;
}

std::string EconomyTicket::getClassType() const { return "Economy"; }
Ticket* EconomyTicket::clone() const { return new EconomyTicket(*this); }

Ticket* EconomyTicket::createUpgrade() const {
    bool drink, priority;
    std::cout << "\nConfiguring Upgrade to PREMIUM:\n";
    std::cout << "Free drink (1-YES/0-NO): "; std::cin >> drink;
    std::cout << "Priority boarding (1-YES/0-NO): "; std::cin >> priority;

    return new PremiumTicket(getSeat(), getBasePrice() + 40.0, getDiscountPercentage(), drink, priority);
}
EconomyTicket::~EconomyTicket() {}

// BUSINESS:
BusinessTicket::BusinessTicket() : Ticket(), loungeAccess(true) {}

BusinessTicket::BusinessTicket(const std::string &seat, double basePrice, int discountPercentage, bool loungeAccess) :
    Ticket(seat, basePrice, discountPercentage), loungeAccess(loungeAccess) {}

double BusinessTicket::getFinalPrice() const {
    double priceWithFees = getBasePrice() + Ticket::AIRPORT_FEE + BusinessTicket::COMFORT_FEE;
    if (this->loungeAccess) {
       priceWithFees += 20.0;
    }
    double discount = 0.0;
    if (getDiscountPercentage() > 0) {
       discount = priceWithFees * (static_cast<double>(getDiscountPercentage()) / 100.0);
    }
    return priceWithFees - discount;
}

std::string BusinessTicket::getClassType() const { return "Business"; }
Ticket * BusinessTicket::clone() const { return new BusinessTicket(*this); }

Ticket* BusinessTicket::createUpgrade() const {
    bool mealService, priorityFC;
    std::cout << "\nConfiguring Upgrade to FIRST CLASS:\n";
    std::cout << "Meal service (1-YES/0-NO): "; std::cin >> mealService;
    std::cout << "Priority (1-YES/0-NO): "; std::cin >> priorityFC;

    return new FirstClassTicket(getSeat(), getBasePrice() + 100.0, getDiscountPercentage(), mealService, priorityFC);
}

void BusinessTicket::enterLounge() const {
    if (this->loungeAccess) {
       successMessage("[BUSINESS LOUNGE] Access granted! Buffet and Wi-Fi available.");
    } else {
       infoMessage("[LOUNGE] Business Ticket is valid, but Lounge option was NOT purchased.");
    }
}
BusinessTicket::~BusinessTicket() {}

// FIRST CLASS:
FirstClassTicket::FirstClassTicket() : Ticket(), mealService(true), priorityBoarding(true) {}
FirstClassTicket::FirstClassTicket(const std::string &seat, double basePrice, int discountPercentage, bool mealService, bool priorityBoarding) :
    Ticket(seat, basePrice, discountPercentage), mealService(mealService), priorityBoarding(priorityBoarding) {}

double FirstClassTicket::getFinalPrice() const {
    double priceWithFees = getBasePrice() + Ticket::AIRPORT_FEE + FirstClassTicket::LUXURY_FEE;
    if (this->mealService) {
       priceWithFees += 45.0;
    }
    if (this->priorityBoarding) {
       priceWithFees += 25.0;
    }
    double discount = 0.0;
    if (getDiscountPercentage() > 0) {
       discount = priceWithFees * (static_cast<double>(getDiscountPercentage()) / 100.0);
    }
    return priceWithFees - discount;
}

std::string FirstClassTicket::getClassType() const { return "FirstClass"; }
Ticket * FirstClassTicket::clone() const { return new FirstClassTicket(*this); }
Ticket* FirstClassTicket::createUpgrade() const { return nullptr; }

void FirstClassTicket::enterLounge() const {
    std::cout << "[LOUNGE] Welcome to the VIP First Class Lounge! Champagne and services included.\n";
}
FirstClassTicket::~FirstClassTicket() {}

// PREMIUM TICKET:
const double PremiumTicket::PREMIUM_FEE = 45.0;

PremiumTicket::PremiumTicket() : Ticket(), drink(true), priority(true) {}

PremiumTicket::PremiumTicket(const std::string& seat, double basePrice, int discountPercentage, bool drink, bool priority):
    Ticket(seat, basePrice, discountPercentage), drink(drink), priority(priority) {}

double PremiumTicket::getFinalPrice() const {
    double priceWithFees = getBasePrice() + Ticket::AIRPORT_FEE + PremiumTicket::PREMIUM_FEE;
    if (this->drink) {
       priceWithFees += 10.0;
    }
    if (this->priority) {
       priceWithFees += 14.0;
    }
    double discount = 0.0;
    if (getDiscountPercentage() > 0) {
       discount = priceWithFees * (static_cast<double>(getDiscountPercentage()) / 100.0);
    }
    return priceWithFees - discount;
}

std::string PremiumTicket::getClassType() const { return "Premium"; }
Ticket* PremiumTicket::clone() const { return new PremiumTicket(*this); }

Ticket* PremiumTicket::createUpgrade() const {
    bool loungeAccess;
    std::cout << "\nConfiguring Upgrade to BUSINESS:\n";
    std::cout << "Lounge access (1-YES/0-NO): "; std::cin >> loungeAccess;

    return new BusinessTicket(getSeat(), getBasePrice() + 30.0, getDiscountPercentage(), loungeAccess);
}
PremiumTicket::~PremiumTicket() {}