
#include "includes/account/Account.h"
#include "includes/account/DebitAccount.h"

namespace account{
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
    
}