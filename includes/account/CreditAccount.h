#ifndef CREDIT_ACCOUNT_H
#define CREDIT_ACCOUNT_H

#include <string>
#include "Account.h"

namespace account
{
    class CreditAccount : public Account
    {
    private:
        float limit;
        float balance;

    public:
        CreditAccount(std::string name, float cardLimit);

        void withdraw(float amount);

        ~CreditAccount();
    };
    
    CreditAccount::CreditAccount(std::string name, float cardLimit) :
    Account::Account(name)
    {
        limit = cardLimit;
        balance = 0;
    }

    void CreditAccount::withdraw(float amount){
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
    
} // namespace account


#endif