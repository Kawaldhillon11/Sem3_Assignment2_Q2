
#include "includes/account/Account.h"
#include "includes/account/CreditAccount.h"

namespace account{
    CreditAccount::CreditAccount(std::string name, double cardLimit) :
    Account::Account(name)
    {
        limit = cardLimit;
        balance = 0;
    }

    void CreditAccount::withdraw(double amount){
        if(amount < 1)
            throw new std::invalid_argument("Widthdrawal Amount cannot be less than $1");
        
        float newBalance = balance + amount;
        
        if(newBalance > limit)
            throw new std::invalid_argument("Insufficient Funds, Cannot widthdraw");
        
        balance = newBalance;
    }
    
    CreditAccount::~CreditAccount()
    {
    }
}