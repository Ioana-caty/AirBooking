#pragma once
#include <string>
#include <iostream>

class AirlineCompany;

class ILoungeAccess {
public:
    virtual void enterLounge() const = 0;
    virtual ~ILoungeAccess() = default;
};

class Ticket {
protected:
    int ticketID;
    std::string seat;
    double basePrice;
    int discountPercentage;

    static int counterID;
    const static double AIRPORT_FEE;

    static bool isSeatValid(const std::string& seat);

public:
    Ticket();
    Ticket(const std::string& seat, double basePrice, int discountPercentage);

    Ticket(const Ticket& other);
    Ticket& operator=(const Ticket& other);

    bool setSeat(const std::string& newSeat);
    const std::string& getSeat() const { return seat; }
    double getBasePrice() const { return basePrice; }
    int getDiscountPercentage() const { return discountPercentage; }

    void addBaggageFee(const double fee) { basePrice += fee; }

    virtual double getFinalPrice() const = 0;
    virtual std::string getClassType() const = 0;
    virtual Ticket* clone() const = 0;
    virtual Ticket* createUpgrade() const = 0;

    virtual ~Ticket();

    friend std::ostream& operator<<(std::ostream& COUT, const Ticket& t);
    friend void saveData(const AirlineCompany& company, const std::string& fileName);
};

class EconomyTicket : public Ticket {
    static const double EXTRA_FEE;
public:
    EconomyTicket();
    EconomyTicket(const std::string& seat, double basePrice, int discountPercentage);

    double getFinalPrice() const override;
    std::string getClassType() const override;
    Ticket* clone() const override;
    Ticket* createUpgrade() const override;

    ~EconomyTicket() override;
};

class BusinessTicket : public Ticket, public ILoungeAccess {
    static const double COMFORT_FEE;
    bool loungeAccess;
public:
    BusinessTicket();
    BusinessTicket(const std::string& seat, double basePrice, int discountPercentage, bool loungeAccess = true);

    double getFinalPrice() const override;
    std::string getClassType() const override;
    Ticket* clone() const override;
    Ticket* createUpgrade() const override;

    void enterLounge() const override;
    ~BusinessTicket() override;
};

class FirstClassTicket : public Ticket, public ILoungeAccess {
    static const double LUXURY_FEE;
    bool mealService;
    bool priorityBoarding;
public:
    FirstClassTicket();
    FirstClassTicket(const std::string& seat, double basePrice, int discountPercentage,
                bool mealService = true, bool priorityBoarding = true);

    double getFinalPrice() const override;
    std::string getClassType() const override;
    Ticket* clone() const override;
    Ticket* createUpgrade() const override;

    void enterLounge() const override;
    ~FirstClassTicket() override;
};

class PremiumTicket : public Ticket {
    static const double PREMIUM_FEE;
    bool drink;
    bool priority;

public:
    PremiumTicket();
    PremiumTicket(const std::string& seat, double basePrice, int discountPercentage,
              bool drink = true, bool priority = true);

    double getFinalPrice() const override;
    std::string getClassType() const override;
    Ticket* clone() const override;
    Ticket* createUpgrade() const override;

    ~PremiumTicket() override;
};