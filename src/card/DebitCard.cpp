#include "includes/card/Card.h"
#include "includes/card/DebitCard.h"

namespace card{
    DebitCard::DebitCard(account::DebitAccount* acc, std::string pin):
    Card::Card(acc,pin)
    {
    }

    void DebitCard::makePayment(double amount, std::string pin){
        Card::makePayment(amount, pin);
    }

    
    DebitCard::~DebitCard()
    {
    }
}