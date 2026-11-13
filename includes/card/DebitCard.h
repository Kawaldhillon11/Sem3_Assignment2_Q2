#include "includes/card/Card.h"
#include "includes/account/DebitAccount.h"

namespace card{
    class DebitCard: public Card
    {
    private:
    public:
        DebitCard(account::DebitAccount* acc, std::string pin);
        void makePayment(double amount, std::string pin);
        ~DebitCard();
    };
    
}

