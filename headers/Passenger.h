#pragma once
#include <iostream>
#include <string>
#include "Ticket.h"

class AirlineCompany;
class CheckIn;

class Passenger {
	std::string name;
	std::string email;
	int passengerID;
	static int counterID;

	Ticket* ticket;
	CheckIn* checkIn;

public:
	Passenger(const std::string& name, const std::string& email, Ticket* newTicket);
	Passenger();

	Passenger(const Passenger& other);
	Passenger& operator=(const Passenger& other);

	const std::string& getName() const { return name; }
	const std::string& getEmail() const { return email; }
	const Ticket* getTicket() const { return ticket; }

	const std::string& getKey() const { return name; }

	bool hasTicket() const { return ticket != nullptr; }
	bool matchesName(const std::string& verifiedName) const;
	void modifySeat(const std::string& newSeat);
	void updateTicket(const Ticket* newTicket);
	void getRevenue(double& total) const;

	bool hasCheckIn() const { return checkIn != nullptr; }
	CheckIn* getCheckIn() const { return checkIn; }
	void performCheckIn(const std::string& flightNumber);

	~Passenger();

	friend std::ostream& operator<<(std::ostream& os, const Passenger& p);
	friend void saveData(const AirlineCompany& company, const std::string& fileName);
};