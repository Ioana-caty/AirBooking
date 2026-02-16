#pragma once
#include "../headers/Flight.h"
#include "../headers/Passenger.h"
#include "../headers/Ticket.h"
#include "../headers/Airline.h"
#include <fstream>
#include <iostream>
#include <vector>

void saveData(const Airline& company, const std::string& filename) {
	std::ofstream fout(filename);

	if (!fout.is_open()) {
		std::cerr << "ERROR: Could not open file '" << filename << "' for writing!";
		return;
	}

	const std::vector<Flight>& flights = company.flightFleet;

	fout << flights.size() << "\n";

	for (const auto& flight : flights) {
		fout << flight.getFlightNumber() << " "
			<< flight.getDestination() << " "
			<< flight.getGate() << " "
			<< flight.getMaxCapacity() << "\n";

		const std::vector<Passenger>& passengers = flight.getPassengers();

		fout << passengers.size() << "\n";

		for (const auto& passenger : passengers) {
			fout << passenger.getName() << "\n";
			fout << passenger.getEmail() << "\n";

			const Ticket* ticket = passenger.getTicket();
			if (ticket != nullptr) {
				fout << ticket->getSeat() << " "
					  << ticket->getClassType() << " "
					  << ticket->getBasePrice() << " "
					  << ticket->getDiscountPercentage() << "\n";
			} else {
				fout << "ERROR";
			}
		}
	}

	fout.close();
	successMessage("Data has been saved to file '" + filename + "'");
	infoMessage("Saved " + std::to_string(flights.size()) + " flights.");
}