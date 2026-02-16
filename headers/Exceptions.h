#pragma once
#include <exception>
#include <string>

class FlightException : public std::exception {
protected:
	std::string message;
public:
	explicit FlightException(const std::string& msg) : message(msg) {}
	const char* what() const noexcept {
		return message.c_str();
	}
};

class ValidationException : public FlightException {
public:
	explicit ValidationException(const std::string& msg) : FlightException(msg) {}
};

class CapacityException : public FlightException {
public:
	explicit CapacityException(const std::string& msg) : FlightException(msg) {}
};

class OperationException : public FlightException {
public:
	explicit OperationException(const std::string& msg) : FlightException(msg) {}
};