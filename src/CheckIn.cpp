#include "../headers/CheckIn.h"
#include "../headers/Ticket.h"
#include "../headers/Utils.h"
#include <cstring>


CheckIn::CheckIn(const std::string& passenger, const std::string& flight, const std::string& seat, Ticket* ticket)
    : passengerName(toUpperCase(passenger)),
      flightNumber(toUpperCase(flight)),
      seat(toUpperCase(seat)),
      passengerTicket(ticket) {

    successMessage("Check-in created for " + passengerName);
}

void CheckIn::addBaggage(const Baggage& baggage) {
    luggage.push_back(baggage);

    if (passengerTicket != nullptr) {
       const double baggageFee = baggage.getBaggageFee() + baggage.getExtraFee();
       passengerTicket->addBaggageFee(baggageFee);
       successMessage("Baggage added: " + baggage.getTypeString());
       infoMessage("Updated ticket price: +" + Format::getFormattedPrice(baggageFee));
    }

    if (baggage.isOverweight()) {
        infoMessage("ATTENTION: Overweight baggage! Extra fee: " +
                  Format::getFormattedPrice(baggage.getExtraFee()));
    }
}

double CheckIn::getTotalWeight() const {
    double total = 0.0;
    for (const auto& b : luggage) {
        total += b.getWeight();
    }
    return total;
}

double CheckIn::getTotalBaggageFees() const {
    double total = 0.0;
    for (const auto& b : luggage) {
        total += b.getBaggageFee() + b.getExtraFee();
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const CheckIn& c) {
    os << "\n";
    UI::titlu(os, "PASSENGER CHECK-IN: " + c.passengerName, '=', 60);
    os << "Flight: " << c.flightNumber << " | Seat: " << c.seat << "\n";
    os << "Number of bags: " << c.luggage.size() << "\n";

    if (!c.luggage.empty()) {
        os << "\nRegistered Baggage:\n";
        UI::Line(std::cout, '-', 60);

        for (size_t i = 0; i < c.luggage.size(); i++) {
            os << (i + 1) << ". " << c.luggage[i].getTypeString()
               << " - " << c.luggage[i].getWeight() << " kg";

            if (c.luggage[i].isOverweight()) {
                os << " [OVERWEIGHT]";
            }

            os << " - " << Format::getFormattedPrice(
                c.luggage[i].getBaggageFee() + c.luggage[i].getExtraFee()) << "\n";
        }

        UI::Line(std::cout, '-', 60);
        os << "Total weight: " << c.getTotalWeight() << " kg\n";
        os << "Total baggage fees: " << Format::getFormattedPrice(c.getTotalBaggageFees()) << "\n";
    } else {
        os << "\nNo baggage registered.\n";
    }

    if (c.passengerTicket != nullptr) {
       os << "\n>>> UPDATED TICKET PRICE: "
          << Format::getFormattedPrice(c.passengerTicket->getFinalPrice()) << " <<<\n";
    }

    UI::Line(std::cout, '=', 60);

    return os;
}