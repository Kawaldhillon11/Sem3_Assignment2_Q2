#include "includes/card/Card.h"
#include "includes/card/DebitCard.h"

namespace card{
    DebitCard::DebitCard(account::DebitAccount* acc, std::string pin, int month, int year):
    Card::Card(acc, pin, month, year)
    {
    }

    void DebitCard::makePayment(double amount, std::string pin){
        Card::makePayment(amount, pin);
    }

    
    DebitCard::~DebitCard()
    {
    }
}