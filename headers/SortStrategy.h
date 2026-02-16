#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Flight.h"
#include "Utils.h"

class SortStrategy {
public:
	virtual void sort(std::vector<Flight>& flights) const = 0;
	virtual std::string getName() const = 0;
	virtual ~SortStrategy() = default;
};

class SortByDestination : public SortStrategy {
public:
	void sort(std::vector<Flight>& flights) const override {
		std::sort(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
		   return toUpperCase(a.getDestination()) < toUpperCase(b.getDestination());
		});
	}
	std::string getName() const override {
		return "Sorting by destination (alphabetical)";
	}
};

class SortByOccupancy : public SortStrategy {
public:
	void sort(std::vector<Flight>& flights) const override {
		std::sort(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
		   double rateA = static_cast<double>(a.getOccupiedSeats()) / a.getMaxCapacity();
		   double rateB = static_cast<double>(b.getOccupiedSeats()) / b.getMaxCapacity();
		   return rateA > rateB;
		});
	}
	std::string getName() const override {
		return "Sorting by occupancy rate (descending)";
	}
};

class SortByRevenue : public SortStrategy {
public:
	void sort(std::vector<Flight>& flights) const override {
		std::sort(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
		   return a.calculateTotalRevenue() > b.calculateTotalRevenue();
		});
	}
	std::string getName() const override {
		return "Sorting by revenue (descending)";
	}
};