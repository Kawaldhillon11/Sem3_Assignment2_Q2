#include "includes/card/Card.h"
#include "includes/card/CreditCard.h"

namespace card{
   CreditCard::CreditCard(double cashbackPer, account::CreditAccount* acc, std::string pin) :
    Card::Card(acc, pin)
    {
        setCashBackPer(cashbackPer);
    }

    void CreditCard::setCashBackPer(double per){
        if(per <= 0)
            throw new std::invalid_argument("Cashback Percentage cannot Zero or less than Zero");
        
        cashbackPercent = per;
    }

    void CreditCard::makePayment(double amount, std::string pin){
        Card::makePayment(amount, pin);
        static_cast<account::CreditAccount*>(Card::linkedAccount)->setCashBackEarned(amount*cashbackPercent);    
    }


    CreditCard::~CreditCard()
    {
    }
     
}