#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Passenger.h"

class Airline;

class Flight {
    std::string flightNumber;
    std::string destination;
    std::string gate;
    std::vector<Passenger> passengerList;
    size_t maxCapacity;

    bool isGateValid(const std::string& newGate) const;
    bool passengerExists(const std::string& name) const;

public:
    Flight();
    Flight(const std::string& number, const std::string& dest, const std::string& gate, int capacity);

    const std::string& getFlightNumber() const { return flightNumber; }
    int getOccupiedSeats() const { return passengerList.size(); }

    const std::string& getGate() const { return gate; }
    const std::vector<Passenger>& getPassengers() const { return passengerList; }
    const std::string& getDestination() const { return destination; }
    size_t getMaxCapacity() const { return maxCapacity; }

    const std::string& getKey() const { return flightNumber; }

    bool setGate(const std::string& newGate);
    bool addPassenger(const Passenger& p);
    bool isFull() const;
    bool upgradePassengerTicket(const std::string& name);
    bool isSeatOccupied(const std::string& seat, const std::string& nameToExclude) const;
    bool matchesNumber(const std::string& number) const;

    double calculateTotalRevenue() const;
    void displayOccupiedSeats() const;
    void displayCapacityDetails() const;

    Passenger* findPassengerByName(const std::string& name);

    ~Flight();

    friend std::ostream& operator<<(std::ostream& os, const Flight& f);
    void displayWithoutPassengers(bool showRevenue) const;
    friend void saveData(const Airline& airline, const std::string& filename);
};