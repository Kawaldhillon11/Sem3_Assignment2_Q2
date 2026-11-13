#include "includes/card/Card.h"

namespace card{
    Card::Card(account::Account* acc, std::string pinNumber)
    {
        cardNumber = cardCount;
        Card::setPin(pinNumber);
        linkedAccount = acc;
        cardCount++;
    }

    void Card::setPin(std::string pinNumber){
        if(pinNumber.empty() || pin.length() < 4)
            throw new std::invalid_argument("Please Enter a Valid Pin (4 digits)");

        pin = pinNumber;
    }

    bool Card::validatePin(std::string pinNumber){
        if(pinNumber.empty() || pin.length() < 4)
            throw new std::invalid_argument("Please Enter a Valid Pin (4 digits)");

        if(pin != pinNumber)
            return false;

        return true;
    }

    void Card::makePayment(double amount, std::string pin){
        if(!Card::validatePin(pin))
            throw new std::invalid_argument("Incorrect Pin Entered!");

        linkedAccount->withdraw(amount);
    }
    
    Card::~Card()
    {
    }
}