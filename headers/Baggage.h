#pragma once
#include <string>
#include <iostream>

enum class BaggageType {
	PERSONAL_ITEM,
	CARRY_ON,
	CHECKED_SMALL,
	CHECKED_LARGE
};

class Baggage {
	BaggageType type;
	double weight;

public:
	Baggage();
	Baggage(BaggageType type, double weight);

	double getWeight() const { return weight; }

	bool isOverweight() const;
	double getBaggageFee() const;
	double getExtraFee() const;
	std::string getTypeString() const;

	friend std::ostream& operator<<(std::ostream& os, const Baggage& b);
};