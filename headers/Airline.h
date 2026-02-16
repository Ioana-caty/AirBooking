#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Flight.h"
#include "SortStrategy.h"

class Airline {
	std::string companyName;
	std::vector<Flight> flightFleet;
	std::shared_ptr<SortStrategy> sortStrategy;

	bool isDuplicateFlight(const std::string& flightNumber) const;
public:
	Airline();
	explicit Airline(const std::string& name);

	bool addFlight(const Flight& f);
	Flight* findFlightByNumber(const std::string& flightNumber);

	void setSortStrategy(std::shared_ptr<SortStrategy> s);
	void sortFlights();

	std::vector<Flight*> filterFullFlights();
	std::vector<Flight*> filterEmptyFlights();
	std::vector<Flight*> findFlightsByDestination(const std::string& dest);

	friend std::ostream& operator<<(std::ostream& COUT, const Airline& a);
	void displayWithoutPassengers(bool includeRevenue) const;
	friend void saveData(const Airline& airline, const std::string& filename);
};