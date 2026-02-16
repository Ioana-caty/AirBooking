#include "../headers/SortStrategy.h"
#include "../headers/Airline.h"
#include "../headers/Exceptions.h"
#include <iostream>

Airline::Airline() : companyName("CAnonymous Airline") {
}
Airline::Airline(const std::string& name) : companyName(name) {
}

bool Airline::isDuplicateFlight(const std::string& flightNumber) const {
    for (const auto& flight : flightFleet) {
	    if (toUpperCase(flight.getFlightNumber()) == toUpperCase(flightNumber)) {
		    return true;
	    }
    }
	return false;
}

bool Airline::addFlight(const Flight& flight) {
	if (this->isDuplicateFlight(flight.getFlightNumber())) {
		throw OperationException("Zborul " + flight.getFlightNumber() + " exista deja");
	}
	this->flightFleet.push_back(flight);
	return true;
}

Flight *Airline::findFlightByNumber(const std::string& flightNumber) {
    for (auto& flight: flightFleet) {
        if (flight.matchesNumber(flightNumber)) {
            return &flight;
        }
    }
    return nullptr;
}

void Airline::setSortStrategy(std::shared_ptr<SortStrategy> s) {
	sortStrategy = s;
}

void Airline::sortFlights() {
	if (sortStrategy == nullptr) {
		errorMessage("No sorting strategy set!");
		return;
	}
	sortStrategy->sort(flightFleet);
	successMessage(sortStrategy->getName());
}

std::vector<Flight*> Airline::filterFullFlights() {
	std::vector<Flight*> result;

	for (auto& flight : flightFleet) {
		if (flight.isFull()) {
			result.push_back(&flight);
		}
	}

	return result;
}

std::vector<Flight *> Airline::filterEmptyFlights() {
	std::vector<Flight*> result;

	for (auto& flight: flightFleet) {
		if (flight.getOccupiedSeats() == 0) {
			result.push_back(&flight);
		}
	}

	return result;
}

std::vector<Flight*> Airline::findFlightsByDestination(const std::string& dest) {
	std::vector<Flight*> result;

	std::string destUpper = toUpperCase(dest);

	for (auto& flight: flightFleet) {
		if (toUpperCase(flight.getDestination()) == destUpper) {
			result.push_back(&flight);
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& COUT, const Airline& a) {

	UI::Line(COUT, '=', 94);
    COUT << "AIRLINE: " << a.companyName << "\n";
    COUT << "FLIGHT FLEET (" << a.flightFleet.size() << "):\n";
	UI::Line(COUT, '=', 94);

	if (a.flightFleet.empty()) {
		COUT << "No flights registered\n";
	} else {
		for (const auto& flight : a.flightFleet) {
			COUT << flight << "\n\n";
		}
	}
	return COUT;
}

void Airline::displayWithoutPassengers(bool includeRevenue) const {
	UI::Line(std::cout, '=', 94);
	for (const auto& flight : flightFleet) {
		flight.displayWithoutPassengers(includeRevenue);
	}
	UI::Line(std::cout, '=', 94);
}