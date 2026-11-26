#include <string>

#include "includes/card/Card.h"
#include "includes/account/CreditAccount.h"

namespace card{
    class CreditCard: public Card
    {
        private:
            double cashbackPercent;
        public:
            CreditCard(double cashbackPer, account::CreditAccount* acc, std::string pin, int month, int year);
            void setCashBackPer(double per);
            double getCashBackPer();
            void makePayment(double amount, std::string pin);
            ~CreditCard();
    };
    
}
