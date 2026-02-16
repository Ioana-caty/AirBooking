#pragma once
#include <string>
#include <vector>
#include "Baggage.h"
#include "Ticket.h"


class CheckIn {
	std::string passengerName;
	std::string flightNumber;
	std::string seat;
	std::vector<Baggage> luggage;

	Ticket* passengerTicket;

public:
	CheckIn(const std::string& passenger, const std::string& flight, const std::string& seat, Ticket* ticket);

	void addBaggage(const Baggage& baggage);
	double getTotalWeight() const;
	double getTotalBaggageFees() const;

	friend std::ostream& operator<<(std::ostream& os, const CheckIn& c);
};