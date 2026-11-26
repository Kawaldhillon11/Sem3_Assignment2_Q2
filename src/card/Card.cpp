#include "includes/card/Card.h"

namespace card{
    Card::Card(account::Account* acc, std::string pinNumber, int month, int year)
    {
        cardNumber = cardCount;
        Card::setPin(pinNumber);
        linkedAccount = acc;
        Card::setExpiryDate(month, year);
        cardCount++;
    }

    void Card::setPin(std::string pinNumber){
        if(pinNumber.empty() || pinNumber.length() < 4)
            throw std::invalid_argument("Please Enter a Valid Pin (4 digits)");

        pin = pinNumber;
    }

    void Card::setExpiryDate(int month, int year){
        if(month < 1 || month > 12)
            throw std::invalid_argument("Please Enter a Month between 1 and 12");
        
        // hardcode year check, could have gotten date from system and extraced year
        if(year < 2026 || year > 2036)
            throw std::invalid_argument("Please Enter a year between 2026 and 2036");

        expiryMonth = month;
        expiryYear = year;
    }

    std::string Card::getExpiryDate(){
        return std::to_string(this->expiryMonth) + "/" +std::to_string(this->expiryYear);
    }


    int Card::getCardNumber(){
        return cardNumber;
    }

    account::Account* Card::getLinkedAccount(){
        return linkedAccount;
    }

    bool Card::validatePin(std::string pinNumber){
        if(pinNumber.empty() || pinNumber.length() < 4)
            throw std::invalid_argument("Please Enter a Valid Pin (4 digits)");

        if(pin != pinNumber)
            return false;

        return true;
    }

    void Card::makePayment(double amount, std::string pin){
        if(!Card::validatePin(pin))
            throw std::invalid_argument("Incorrect Pin Entered!");

        linkedAccount->withdraw(amount);
    }
    
    Card::~Card()
    {
    }
}