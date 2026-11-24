
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
        int getCardNumber();
        bool validatePin(std::string pinNumber);
        virtual void makePayment(double amount, std::string pin);
        ~Card();
    };
     
}