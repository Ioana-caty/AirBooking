#include "../headers/Passenger.h"
#include "../headers/Airline.h"
#include "../headers/Exceptions.h"
#include "../headers/Utils.h"
#include "../headers/CheckIn.h"

int Passenger::counterID = 0;

Passenger::Passenger(const std::string &nume, const std::string &Email, Ticket *biletNou)
	: name(toUpperCase(nume)), email(Email), passengerID(counterID++), ticket(biletNou), checkIn(nullptr) {
}

Passenger::Passenger()
	: name("not_specified"), email("none@gmail.com"), passengerID(counterID++), ticket(nullptr), checkIn(nullptr) {
}

Passenger::Passenger(const Passenger &other)
	: name(other.name), email(other.email), passengerID(other.passengerID), checkIn(nullptr) {
	if (other.ticket != nullptr) {
		ticket = other.ticket->clone();
	} else {
		ticket = nullptr;
	}
}

Passenger &Passenger::operator=(const Passenger &other) {
	if (this == &other) {
		return *this;
	}

	this->name = other.name;
	this->email = other.email;
	this->passengerID = other.passengerID;

	delete this->ticket;
	this->ticket = nullptr;

	delete this->checkIn;
	this->checkIn = nullptr;

	if (other.ticket != nullptr) {
		this->ticket = other.ticket->clone();
	}

	return *this;
}

bool Passenger::matchesName(const std::string& numeVerificat) const {
	return toUpperCase(name) == toUpperCase(numeVerificat);
}

void Passenger::modifySeat(const std::string& locNou) {
	if (ticket == nullptr) {
		throw OperationException("Pasagerul nu are bilet!");
	}

	Ticket* biletNou = ticket->clone();
	if (!biletNou->setSeat(locNou)) {
		delete biletNou;
		throw ValidationException("Format loc invalid: "+ locNou);
	}
	delete this->ticket;
	this->ticket = biletNou;
}

void Passenger::updateTicket(const Ticket *biletNou) {
	delete this->ticket;
	if (biletNou != nullptr) {
		this->ticket = biletNou->clone();
	} else {
		this->ticket = nullptr;
	}
}

void Passenger::getRevenue(double& total) const {
	if (ticket != nullptr) {
		total += ticket->getFinalPrice();
	}
}

void Passenger::performCheckIn(const std::string& numarZbor) {
	if (ticket == nullptr) {
		errorMessage("Pasagerul nu are bilet! Nu se poate face check-in.");
		return;
	}

	if (checkIn != nullptr) {
		infoMessage("Check-in deja efectuat pentru acest pasager!");
		return;
	}

	checkIn = new CheckIn(name, numarZbor, ticket->getSeat(), ticket);
}

Passenger::~Passenger(){
	delete ticket;
	ticket = nullptr;

	delete checkIn;
	checkIn = nullptr;
}

std::ostream &operator<<(std::ostream &COUT, const Passenger &p) {
	COUT << "Pasager [ID: " << p.passengerID
			<< ", Nume: " << p.name
			<< ", Email: " << p.email << "]"
			<< std::endl;
	if (p.ticket != nullptr) {
		COUT << *(p.ticket);
	} else {
		COUT << "Bilet: N/A\n";
	}
	return COUT;
}