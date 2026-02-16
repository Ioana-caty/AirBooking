#include "headers/Ticket.h"
#include "headers/Passenger.h"
#include "headers/Flight.h"
#include "headers/Airline.h"
#include "headers/Baggage.h"
#include "headers/CheckIn.h"
#include "headers/Exceptions.h"
#include "headers/Repository.h"
#include "input/populateData.h"
#include "input/saveData.h"
#include "Pattern/TicketFactory.h"
#include "headers/Utils.h"

void addFlight(Airline& company) {
    UI::Subtitle("ADD FLIGHT");

    std::string number, destination, gate;
    int maxCapacity;
    std::cout << "Flight number: "; std::cin >> number;
    std::cout << "Destination: "; std::cin >> destination;
    std::cout << "Gate: "; std::cin >> gate;
    std::cout << "Capacity: "; std::cin >> maxCapacity;

    Flight flight(number, destination, gate, maxCapacity);
    if (flight.setGate(gate)) {
       company.addFlight(flight);
       successMessage("Flight added successfully!");
    }
}

void findFlight(Airline& company) {
    UI::Subtitle("FIND FLIGHT");

    std::string number;
    std::cout << "Flight number: "; std::cin >> number;

    const Flight* f = company.findFlightByNumber(number);
    if (f) {
       std::cout << "\n" << *f << "\n";
    } else {
       errorMessage("Flight not found!");
    }
}

bool addPassenger(Airline& company) {
    UI::Subtitle("ADD PASSENGER");

    std::string number, email, seat, classType, name;
    double price;
    int discount;

    std::cout << "Flight number: ";
    std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    std::cout << "Name: "; std::getline(std::cin, name);
    std::cout << "Email: "; std::cin >> email;

    f->displayOccupiedSeats();
    std::cout << "Seat: "; std::cin >> seat;
    std::cout << "Class type: "; std::cin >> classType;
    std::cout << "Price: "; std::cin >> price;
    std::cout << "Discount: "; std::cin >> discount;

    Ticket* ticket = TicketFactory::createTicket(classType, seat, price, discount);
    Passenger p(name, email, ticket);
    f->addPassenger(p);
    successMessage("Passenger added successfully!");
    return true;
}

bool findPassenger(Airline& company) {
    UI::Subtitle("FIND PASSENGER");

    std::string number, name;
    std::cout << "Flight number: "; std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }
    std::cout << "Name: "; std::getline(std::cin, name);
    const Passenger* p = f->findPassengerByName(name);
    if (p) {
       std::cout << "\n" << *p << "\n";
    } else {
       errorMessage("Passenger not found!");
    }
    return true;
}

bool modifyGate(Airline& company) {
    UI::Subtitle("MODIFY GATE");

    std::string number, gate;
    std::cout << "Flight number: "; std::cin >> number;

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    UI::Line(std::cout, '-', 40);
    std::cout << "Old gate: " << f->getGate() << "\n";
    std::cout << "New gate: "; std::cin >> gate;
    if (f->setGate(gate)) {
       successMessage("Gate changed successfully!");
    } else {
       infoMessage("Gate remains the same!");
    }
    return true;
}

bool modifyTicketSeat(Airline& company) {
    UI::Subtitle("MODIFY TICKET SEAT");

    std::string number, name, newSeat;
    std::cout << "Flight number: "; std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    std::cout << "Name: "; std::getline(std::cin, name);
    Passenger* p = f->findPassengerByName(name);
    if (!p) {
       errorMessage("Passenger not found!");
       return false;
    }

    if (!p->hasTicket()) {
       errorMessage("Passenger has no registered ticket!");
       return false;
    }

    UI::Line(std::cout, '-', 40);
    std::cout << "Current ticket:\n " << *p << "\n";
    std::cout << "New seat: "; std::cin >> newSeat;

    std::string seatUpper = toUpperCase(newSeat);
    if (f->isSeatOccupied(seatUpper, name)) {
       errorMessage("Seat " + seatUpper + " is already occupied by another passenger!");
       return false;
    }

    try {
       p->modifySeat(seatUpper);
       successMessage("Seat modified successfully!");
    }
    catch (const FlightException& e) {
       errorMessage(e.what());
    }
    return true;
}

bool calculateRevenue(Airline& company) {
    UI::Subtitle("CALCULATE REVENUE");

    std::string number;
    std::cout << "Flight number: "; std::cin >> number;

    const Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    std::cout << "Revenue: " << std::fixed << std::setprecision(2)
            << f->calculateTotalRevenue() << " EUR\n";
    return true;
}

bool checkWindowSeat(Airline& company) {
    UI::Subtitle("CHECK WINDOW SEAT");

    std::string number, name;
    std::cout << "Flight number: "; std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    std::cout << "Name: "; std::getline(std::cin, name);
    const Passenger* p = f->findPassengerByName(name);
    if (!p) {
       errorMessage("Passenger not found!");
       return false;
    }

    if (p->hasTicket()) {
       successMessage("YES, it is a window seat!");
    } else {
       infoMessage("NO, it is not a window seat!");
    }
    return true;
}

bool checkFlightFull(Airline& company) {
    UI::Subtitle("CHECK IF FLIGHT IS FULL");

    std::string number;
    std::cout << "Flight number: "; std::cin >> number;

    const Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    f->displayCapacityDetails();
    return true;
}

bool upgradeTicket(Airline& company) {
    UI::Subtitle("UPGRADE PASSENGER TICKET");

    std::string number, name;
    std::cout << "Flight number: "; std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }
    std::cout << "Passenger name: "; std::getline(std::cin, name);

    const Passenger* p = f->findPassengerByName(name);
    if (p && p->hasTicket()) {
       UI::PrintPasager(std::cout, *p, '-', 70);
    }

    char confirm;
    std::cout << "\nConfirm upgrade? (y/n): ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
       if (f->upgradePassengerTicket(name)) {
          successMessage("Upgrade completed successfully!");
          const Passenger* newP = f->findPassengerByName(name);
          if (newP && newP->hasTicket()) {
             std::cout << "\nUPDATED TICKET:\n";
             std::cout << *newP << "\n";
          }
       }
    } else {
       infoMessage("Upgrade cancelled.");
    }
    return true;
}

void sortFlights(Airline& company) {
    UI::Subtitle("SORT FLIGHTS");

    auto sortRev = std::make_shared<SortByRevenue>();
    auto sortOcc = std::make_shared<SortByOccupancy>();
    auto sortDest = std::make_shared<SortByDestination>();

    int subOption;
    while (true) {
       std::cout << "1. By revenue (descending)\n";
       std::cout << "2. By occupancy (descending)\n";
       std::cout << "3. By destination (alphabetical)\n";
       std::cout << "0. Main Menu\n";
       std::cout << "Option: ";

       std::cin >> subOption;
       switch (subOption) {
          case 0:
             return;
          case 1:
             company.setSortStrategy(sortRev);
             company.sortFlights();
             company.displayWithoutPassengers(true);
             break;
          case 2:
             company.setSortStrategy(sortOcc);
             company.sortFlights();
             company.displayWithoutPassengers(false);
             break;
          case 3:
             company.setSortStrategy(sortDest);
             company.sortFlights();
             company.displayWithoutPassengers(false);
             break;
          default:
             errorMessage("Invalid option!");
       }
    }
}

void filterFlights(Airline& company) {
    UI::Subtitle("FILTER FLIGHTS");

    while (true) {
       std::cout << "1. Full flights\n";
       std::cout << "2. Empty flights\n";
       std::cout << "3. Search by destination\n";
       std::cout << "0. Main Menu\n";
       std::cout << "Option: ";

       int subOption;
       std::cin >> subOption;

       if (subOption == 0) break;

       std::vector<Flight*> flights;

       if (subOption == 1) {
          flights = company.filterFullFlights();
       }
       else if (subOption == 2) {
          flights = company.filterEmptyFlights();
       }
       else if (subOption == 3) {
          std::string dest;
          std::cout << "Destination: ";
          std::cin >> dest;
          flights = company.findFlightsByDestination(dest);
       }

       if (flights.empty()) {
          infoMessage("No flights match the criteria.");
       } else {
          UI::Line(std::cout, '=', 90);
          for (const auto* f : flights) {
             f->displayWithoutPassengers(false);
          }
       }
    }
}

bool passengerCheckIn(Airline& company) {
    UI::Subtitle("PASSENGER CHECK-IN");

    std::string number, name;
    std::cout << "Flight number: ";
    std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    std::cout << "Passenger name: ";
    std::getline(std::cin, name);

    Passenger* p = f->findPassengerByName(name);
    if (!p) {
       errorMessage("Passenger not found!");
       return false;
    }

    if (!p->hasTicket()) {
       errorMessage("Passenger has no ticket!");
       return false;
    }

    p->performCheckIn(number);
    return true;
}

bool addBaggage(Airline& company) {
    UI::Subtitle("ADD BAGGAGE");

    std::string number, name;
    std::cout << "Flight number: ";
    std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    std::cout << "Passenger name: ";
    std::getline(std::cin, name);

    const Passenger* p = f->findPassengerByName(name);
    if (!p) {
       errorMessage("Passenger not found!");
       return false;
    }

    if (!p->hasCheckIn()) {
       errorMessage("Passenger has not checked in!");
       return false;
    }

    std::cout << "\nBaggage types:\n";
    std::cout << "1. Personal item (10kg, free)\n";
    std::cout << "2. Carry-on (10kg, 20 EUR)\n";
    std::cout << "3. Checked small (23kg, 35 EUR)\n";
    std::cout << "4. Checked large (32kg, 50 EUR)\n";

    int baggageTypeOption;
    double weight;

    std::cout << "Baggage type: ";
    std::cin >> baggageTypeOption;
    std::cout << "Weight (kg): ";
    std::cin >> weight;

    BaggageType type;
    switch (baggageTypeOption) {
       case 1: type = BaggageType::PERSONAL_ITEM; break;
       case 2: type = BaggageType::CARRY_ON; break;
       case 3: type = BaggageType::CHECKED_SMALL; break;
       case 4: type = BaggageType::CHECKED_LARGE; break;
       default:
          errorMessage("Invalid type!");
          return false;
    }

    Baggage baggage(type, weight);
    std::cout << "\n" << baggage << "\n";

    char confirm;
    std::cout << "\nAdd baggage? (y/n): ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
       p->getCheckIn()->addBaggage(baggage);
    } else {
       infoMessage("Baggage not added.");
    }
    return true;
}

bool displayCheckInDetails(Airline& company) {
    UI::Subtitle("CHECK-IN DETAILS");

    std::string number, name;
    std::cout << "Flight number: ";
    std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    std::cout << "Passenger name: ";
    std::getline(std::cin, name);

    const Passenger* p = f->findPassengerByName(name);
    if (!p) {
       errorMessage("Passenger not found!");
       return false;
    }

    if (!p->hasCheckIn()) {
       errorMessage("Passenger has not checked in!");
       return false;
    }

    std::cout << *(p->getCheckIn()) << "\n";
    return true;
}

void demoTemplates() {
    UI::titlu(std::cout, "Template Demo", '=', 70);
    UI::Subtitle("INSTANTIATION 1: Repository<Flight>");

    Repository<Flight> flightRepo;

    Flight f1("DEMO01", "Paris", "A1", 180);
    Flight f2("DEMO02", "London", "B2", 200);
    Flight f3("DEMO03", "Berlin", "C3", 150);

    flightRepo.add(f1);
    flightRepo.add(f2);
    flightRepo.add(f3);

    std::cout << "Total flights: " << flightRepo.size() << "\n";

    std::cout << "\nSearch flight 'DEMO02' by key:\n";
    const Flight* foundFlight = flightRepo.findByKey("DEMO02");
    if (foundFlight) {
       foundFlight->displayWithoutPassengers(false);
    }

    std::cout << "\nFilter flights with capacity > 160:\n";
    auto largeFlights = flightRepo.filter([](const Flight& f) {
       return f.getMaxCapacity() > 160;
    });
    for (const auto* f : largeFlights) {
       f->displayWithoutPassengers(false);
    }

    UI::Subtitle("INSTANTIATION 2: Repository<Passenger>");

    Repository<Passenger> passengerRepo;

    EconomyTicket* t1 = new EconomyTicket("10A", 100.0, 0);
    BusinessTicket* t2 = new BusinessTicket("1A", 250.0, 5);
    FirstClassTicket* t3 = new FirstClassTicket("2A", 400.0, 10);

    Passenger p1("JOHN DOE", "john@email.com", t1);
    Passenger p2("MARY SMITH", "mary@email.com", t2);
    Passenger p3("ANDREW WILSON", "andrew@email.com", t3);

    passengerRepo.add(p1);
    passengerRepo.add(p2);
    passengerRepo.add(p3);

    std::cout << "Total passengers: " << passengerRepo.size() << "\n";

    std::cout << "\nSearch passenger 'MARY SMITH' by key:\n";
    const Passenger* foundPassenger = passengerRepo.findByKey("MARY SMITH");
    if (foundPassenger) {
       std::cout << *foundPassenger << "\n";
    }

    UI::Subtitle("TEMPLATE FUNCTION:");

    std::cout << "Find first flight with capacity >= 180:\n";
    const Flight* firstLargeFlight = findFirstWhere<Flight>(flightRepo, [](const Flight& f) {
       return f.getMaxCapacity() >= 180;
    });
    if (firstLargeFlight) {
       firstLargeFlight->displayWithoutPassengers(false);
    }

    UI::Subtitle("TEMPLATE FUNCTION:");

    std::cout << "Find first passenger with Business or FirstClass ticket:\n";
    const Passenger* premiumPassenger = findFirstWhere<Passenger>(passengerRepo, [](const Passenger& p) {
       if (!p.hasTicket()) return false;
       std::string type = p.getTicket()->getClassType();
       return type == "Business" || type == "FirstClass";
    });
    if (premiumPassenger) {
       std::cout << *premiumPassenger << "\n";
    }

    size_t largeFlightCount = countWhere<Flight>(flightRepo, [](const Flight& f) {
       return f.getMaxCapacity() >= 180;
    });
    std::cout << "Number of flights with capacity >= 180: " << largeFlightCount << "\n";

    size_t businessPassengerCount = countWhere<Passenger>(passengerRepo, [](const Passenger& p) {
       return p.hasTicket() && p.getTicket()->getClassType() == "Business";
    });
    std::cout << "Number of passengers with Business ticket: " << businessPassengerCount << "\n";
}

void processLoungeAccess(const Ticket* ticket) {
    if (auto* loungeTicket = dynamic_cast<const ILoungeAccess*>(ticket)) {
       loungeTicket->enterLounge();
    } else {
       std::string info = "Class " + ticket->getClassType() + " does not include Lounge access.";
       infoMessage(info);
    }
}

bool checkLoungeAccess(Airline& company) {
    UI::Subtitle("CHECK LOUNGE ACCESS");

    std::string number, name;
    std::cout << "Flight number: "; std::cin >> number;
    std::cin.ignore();

    Flight* f = company.findFlightByNumber(number);
    if (!f) {
       errorMessage("Flight not found!");
       return false;
    }

    std::cout << "Passenger name: "; std::getline(std::cin, name);
    const Passenger* p = f->findPassengerByName(name);

    if (!p) {
       errorMessage("Passenger not found on this flight!");
       return false;
    }

    if (!p->hasTicket()) {
       errorMessage("Passenger does not have an issued ticket!");
       return false;
    }

    UI::Line(std::cout, '-', 50);
    std::cout << "Checking access for: " << name << "\n";
    processLoungeAccess(p->getTicket());

    return true;
}

void printMenu() {
    std::cout << "\n---MENU---\n";
    std::cout << "1. Display airline data\n";
    std::cout << "2. Add flight\n";
    std::cout << "3. Find flight\n";
    std::cout << "4. Add passenger\n";
    std::cout << "5. Find passenger (name)\n";
    std::cout << "6. Modify gate\n";
    std::cout << "7. Modify ticket seat\n";
    std::cout << "8. Calculate revenue\n";
    std::cout << "9. Check window seat\n";
    std::cout << "10. Check if flight is full\n";
    std::cout << "11. Upgrade passenger ticket\n";
    std::cout << "12. Sort flights\n";
    std::cout << "13. Filter flights\n";
    std::cout << "14. Passenger check-in\n";
    std::cout << "15. Add baggage at check-in\n";
    std::cout << "16. Display check-in details\n";
    std::cout << "17. Template Demo\n";
    std::cout << "18. Check Lounge access\n";
    std::cout << "0. Save and Exit\n";
}

int main() {
    Airline company("Wizz Air");
    UI::titlu(std::cout, "FLIGHT MANAGEMENT SYSTEM - WIZZ AIR", '=', 70);

    try {
       populateData(company);
    }
    catch (const FlightException& e) {
       errorMessage(std::string("During population: ") + e.what());
       return 0;
    }

    int option;
    while (true) {
       printMenu();

       std::cin >> option;
       if (option == 0) {
          UI::Subtitle("SAVING DATA");
          saveData(company, "data.txt");
          break;
       }

       try {
          switch (option) {
             case 1:
                std::cout << "\n" << company << "\n";
                break;
             case 2:
                addFlight(company);
                break;
             case 3:
                findFlight(company);
                break;
             case 4:
                addPassenger(company);
                break;
             case 5:
                findPassenger(company);
                break;
             case 6:
                modifyGate(company);
                break;
             case 7:
                modifyTicketSeat(company);
                break;
             case 8:
                calculateRevenue(company);
                break;
             case 9:
                checkWindowSeat(company);
                break;
             case 10:
                checkFlightFull(company);
                break;
             case 11:
                upgradeTicket(company);
                break;
             case 12:
                sortFlights(company);
                break;
             case 13:
                filterFlights(company);
                break;
             case 14:
                passengerCheckIn(company);
                break;
             case 15:
                addBaggage(company);
                break;
             case 16:
                displayCheckInDetails(company);
                break;
             case 17:
                demoTemplates();
                break;
             case 18:
                checkLoungeAccess(company);
                break;

             default:
                errorMessage("Invalid option!");
          }
       }
       catch (const FlightException& e) {
          errorMessage(e.what());
       }
    }
    infoMessage("Goodbye! Have a nice day!");

    return 0;
}
