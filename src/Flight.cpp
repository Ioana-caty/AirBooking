#include "../headers/Flight.h"
#include "../headers/Airline.h"
#include "../headers/Exceptions.h"
#include "../headers/Utils.h"
#include <iostream>
#include <iomanip>

Flight::Flight()
    : flightNumber("N/A"), destination("N/A"), gate("N/A"), maxCapacity(0) {
}

Flight::Flight(const std::string& number, const std::string& dest, const std::string& g, int cap)
    : destination(dest), maxCapacity(cap) {

    if (cap <= 0) {
       throw ValidationException("Invalid capacity: " + std::to_string(cap) + " (must be > 0)");
    }

    std::string numberUpper = toUpperCase(number);
    this->flightNumber = numberUpper;

    std::string gateUpper = toUpperCase(g);
    if (!isGateValid(gateUpper)) {
       throw ValidationException("Invalid gate: " + gateUpper + " (format: letter + digits, ex: A12)");
    }
    this->gate = gateUpper;
}

bool Flight::isGateValid(const std::string& newGate) const {
    return isFormatValid(newGate, false);
}

bool Flight::passengerExists(const std::string& name) const {
    for (const auto& passenger : this->passengerList) {
       if (passenger.matchesName(name)) {
          return true;
       }
    }
    return false;
}

bool Flight::setGate(const std::string& newGate) {
    std::string gateUpper = toUpperCase(newGate);
    if (this->isGateValid(gateUpper)) {
        this->gate = gateUpper;
        return true;
    } else {
        return false;
    }
}

bool Flight::isFull() const {
    return this->passengerList.size() >= this->maxCapacity;
}

bool Flight::addPassenger(const Passenger& p) {
    if (this->isFull()) {
       throw CapacityException("Flight " + this->flightNumber + " is full");
    }

    if (this->passengerExists(p.getName())) {
       throw OperationException("Passenger " + p.getName() + " is already on flight " + this->flightNumber);
    }

    if (p.getTicket() != nullptr) {
       std::string seat = p.getTicket()->getSeat();
       if (isSeatOccupied(seat, "")) {
          throw OperationException("Seat " + seat + " is occupied on flight " + this->flightNumber);
       }
    }

    this->passengerList.push_back(p);
    return true;
}

double Flight::calculateTotalRevenue() const {
    double total = 0.0;
    for (const auto& passenger : this->passengerList) {
        passenger.getRevenue(total);
    }
    return total;
}

Passenger* Flight::findPassengerByName(const std::string& name) {
    for (auto& passenger : this->passengerList) {
       if (passenger.matchesName(name)) {
          return &passenger;
       }
   }
    return nullptr;
}

bool Flight::upgradePassengerTicket(const std::string& name) {
    Passenger* passenger = findPassengerByName(name);
    if (passenger == nullptr) {
       std::cerr << "Passenger not found!\n";
       return false;
    }

    const Ticket* oldTicket = passenger->getTicket();
    if (oldTicket == nullptr) {
       std::cerr << "Passenger does not have a ticket!\n";
       return false;
    }

    UI::Subtitle("TICKET UPGRADE");
    infoMessage("Current class: " + oldTicket->getClassType());
    infoMessage("Current price: " + Format::getFormattedPrice(oldTicket->getFinalPrice()));

    Ticket* newTicket = oldTicket->createUpgrade();

    if (newTicket == nullptr) {
       infoMessage("Ticket is already at maximum level! No further upgrade possible!");
       return false;
    }

    infoMessage("New class: " + newTicket->getClassType());
    infoMessage("New price: " + Format::getFormattedPrice(newTicket->getFinalPrice()));

    passenger->updateTicket(newTicket);
    delete newTicket;
    successMessage("Upgrade completed successfully!");
    return true;
}

void Flight::displayOccupiedSeats() const {
    std::cout << "----Occupied Seats---- ";
    for (const auto& passenger: this->passengerList) {
       if (passenger.getTicket() != nullptr) {
          std::cout << passenger.getTicket()->getSeat() << " ";
       }
    }
    std::cout << "\n";
}

bool Flight::isSeatOccupied(const std::string& seat, const std::string& nameToExclude) const {
    for (const auto& passenger : this->passengerList) {
       if (passenger.getName() == toUpperCase(nameToExclude)) {
          continue;
       }
       if (passenger.getTicket() != nullptr && passenger.getTicket()->getSeat() == seat) {
          return true;
       }
    }
    return false;
}

void Flight::displayCapacityDetails() const {
    if (isFull()) {
       std::cout << "Flight is FULL (" << passengerList.size()
               << "/" << maxCapacity << ")\n";
    } else {
       int available = maxCapacity - passengerList.size();
       std::cout << "Flight has " << available << " seats remaining ("
              << passengerList.size() << "/" << maxCapacity << ")\n";
    }
}

bool Flight::matchesNumber(const std::string& number) const {
    return toUpperCase(flightNumber) == toUpperCase(number);
}

Flight::~Flight() {}

std::ostream& operator<<(std::ostream& COUT, const Flight& f) {
    COUT    << "FLIGHT: " << f.flightNumber
            <<" | DESTINATION: " << f.destination
            <<" | GATE: " << f.gate
            <<" | SEATS: " << f.getOccupiedSeats() << "/" << f.maxCapacity << "\n";
    COUT << "----------------------------------------------------------------------------------------------\n";
    COUT    <<"Passenger list (" << f.passengerList.size() << ")\n";

    if (f.passengerList.empty()) {
        COUT << "No passengers registered\n";
    } else {
        for (size_t i = 0; i < f.passengerList.size(); i++) {
            COUT << f.passengerList[i] << "\n";
        }
    }
    return COUT;
}

void Flight::displayWithoutPassengers(bool showRevenue) const {
    std::cout << "FLIGHT: " << flightNumber
            << " | DESTINATION: " << destination
            << " | GATE: " << gate
            << " | SEATS: " << getOccupiedSeats() << "/" << maxCapacity;

    if (showRevenue) {
       std::cout << " | REVENUE: " << Format::getFormattedPrice(calculateTotalRevenue());
    }

    std::cout << "\n";
}