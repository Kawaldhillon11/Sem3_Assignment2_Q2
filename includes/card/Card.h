#ifndef CARD_H
#define CARD_H

#include <stdexcept>
#include "includes/account/Account.h"

namespace card{
    class Card
    {
    private:
        int cardNumber;
        std::string pin;
        int expiryMonth;
        int expiryYear;

        inline static int cardCount = 1;
    protected:
        account::Account* linkedAccount;
    public:
        Card(account::Account* acc, std::string pinNumber, int month, int year);
        void setPin(std::string pinNumber);
        void setExpiryDate(int month, int year);
        std::string getExpiryDate();
        int getCardNumber();
        account::Account* getLinkedAccount();
        bool validatePin(std::string pinNumber);
        virtual void makePayment(double amount, std::string pin);
        ~Card();
    };
     
}

#endif