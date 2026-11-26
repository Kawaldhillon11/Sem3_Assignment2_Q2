
#include "includes/account/Account.h"
#include "includes/account/CreditAccount.h"

namespace account{
    CreditAccount::CreditAccount(std::string name, double cardLimit) :
    Account::Account(name)
    {
        limit = cardLimit;
        balance = 0;
    }

    double CreditAccount::getLimit(){
        return limit;
    }

    double CreditAccount::getBalance(){
        return balance;
    }

    double CreditAccount::getCashBackEarned(){
        return cashBackEarned;
    }

    void CreditAccount::withdraw(double amount){
        if(amount < 1)
            throw std::invalid_argument("Widthdrawal Amount cannot be less than $1");
        
        float newBalance = balance + amount;
        
        if(newBalance > limit)
            throw std::invalid_argument("Insufficient Funds, Cannot widthdraw");
        
        balance = newBalance;
    }

    void CreditAccount::setCashBackEarned(double cashBack){
        if(cashBack < 0)
            throw std::invalid_argument("Cannot accept negative values");
        cashBackEarned += cashBack;
    }
    
    CreditAccount::~CreditAccount()
    {
    }
}