#pragma once
#include "../headers/Airline.h"
#include "../headers/Passenger.h"
#include "../headers/Ticket.h"
#include "../headers/Flight.h"
#include "../headers/Exceptions.h"
#include <iostream>
#include <fstream>
#include <string>

void populateData(Airline &company) {
    UI::Subtitle("DATA POPULATION");

    const std::string DATA_FILE = "data.txt";
    std::ifstream fin(DATA_FILE);

    if (!fin.is_open()) {
       errorMessage("Could not open file 'data.txt'");
       return;
    }

    int flightCount;
    fin >> flightCount;
    fin.ignore();

    for (int i = 0; i < flightCount; i++) {
       std::string flightCode, destination, gate;
       int maxCapacity;

       fin >> flightCode >> destination >> gate >> maxCapacity;
       fin.ignore();

       try {
          Flight flight(flightCode, destination, gate, maxCapacity);

          int passengerCount;
          fin >> passengerCount;
          fin.ignore();

          for (int j = 0; j < passengerCount; j++) {
             std::string name, email, seat, classType;
             double basePrice, discount;

             std::getline(fin, name);
             name = toUpperCase(name);
             std::getline(fin, email);
             fin >> seat >> classType >> basePrice >> discount;
             fin.ignore();

             try {
                Ticket* ticket = nullptr;
                if (classType == "Economy") {
                   ticket = new EconomyTicket(seat, basePrice, discount);
                } else if (classType == "Business") {
                   ticket = new BusinessTicket(seat, basePrice, discount);
                } else if (classType == "FirstClass") {
                   ticket = new FirstClassTicket(seat, basePrice, discount);
                } else {
                   std::cerr << "Unknown class: " << classType << ", using Economy\n";
                   ticket = new EconomyTicket(seat, basePrice, discount);
                }

                Passenger passenger(name, email, ticket);
                flight.addPassenger(passenger);
             }
             catch (const FlightException& e) {
                errorMessage("Passenger " + name + ": " + e.what());
             }
          }

          company.addFlight(flight);
       }
       catch (const FlightException& e) {
          errorMessage("Flight " + flightCode + ": " + e.what());
       }

       UI::progressBar(i + 1, flightCount);
    }

    UI::progressBar(flightCount, flightCount);
    std::cout << "\n";

    fin.close();
    successMessage("Data successfully loaded from file!");
}