#pragma once
#include <iostream>
#include "../headers/Ticket.h"
#include "../headers/Utils.h"

class TicketFactory {
public:
	static Ticket* createTicket(const std::string& classType, const std::string& seat, double basePrice, int discountPercentage) {
		std::string type = toLowerCase(classType);
		if (type == "economic" || type == "economy") {
			return new EconomyTicket(seat, basePrice, discountPercentage);
		} else if (type == "business") {
			bool loungeAccess = false;
			std::cout << "Lounge access (1-YES/0-NO): ";
			std::cin >> loungeAccess;
			return new BusinessTicket(seat, basePrice, discountPercentage, loungeAccess);
		} else if (type == "firstclass") {
			bool mealService, priority;
			std::cout << "Meal service (1-YES/0-NO): ";
			std::cin >> mealService;
			std::cout << "Boarding priority (1-YES/0-NO): ";
			std::cin >> priority;
			return new FirstClassTicket(seat, basePrice, discountPercentage, mealService, priority);
		} else if (type == "premium") {
			bool freeDrink, priority;
			std::cout << "Free drink (1-YES/0-NO): ";
			std::cin >> freeDrink;
			std::cout << "Boarding priority (1-YES/0-NO): ";
			std::cin >> priority;
			return new PremiumTicket(seat, basePrice, discountPercentage, freeDrink, priority);
		} else {
			std::cerr << "Unknown class: " << classType << ", using Economy instead\n";
			return new EconomyTicket(seat, basePrice, discountPercentage);
		}
	}
};