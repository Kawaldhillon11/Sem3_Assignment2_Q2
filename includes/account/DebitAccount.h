#ifndef DEBIT_ACCOUNT_H
#define DEBIT_ACCOUNT_H

#include <string>
#include <stdexcept>

#include "Account.h"

namespace account
{
    class DebitAccount : public Account 
    {
        private:
            float balance;
        public:
            DebitAccount(std::string name);

            void withdraw(float amount);

            ~DebitAccount();
    };
    
    DebitAccount::DebitAccount(std::string name) :
    Account::Account(name)
    {
        balance = 0;
    }

    void DebitAccount::withdraw(float amount){
        if(amount < 1)
            throw new std::invalid_argument("Widthdrawal Amount cannot be less than $1");
        
        if(amount > balance)
            throw new std::invalid_argument("Insufficient Funds, Cannot widthdraw");
        
        balance -= amount;
    }
    
    DebitAccount::~DebitAccount()
    {
    }
    
    
} // namespace account


#endif