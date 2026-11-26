
#include "includes/account/Account.h"
#include "includes/account/DebitAccount.h"

namespace account{
    DebitAccount::DebitAccount(std::string name) :
    Account::Account(name)
    {
        balance = 0;
    }

    double DebitAccount::getBalance(){
        return balance;
    }

    void DebitAccount::deposit(double amount){
        if(amount <= 0)
            throw std::invalid_argument("Deposit amount must be greater than $0");

        balance += amount;
    }

    void DebitAccount::withdraw(double amount){
        if(amount < 1)
            throw std::invalid_argument("Widthdrawal Amount cannot be less than $1");
        
        if(amount > balance)
            throw std::invalid_argument("Insufficient Funds, Cannot widthdraw");
        
        balance -= amount;
    }
    
    DebitAccount::~DebitAccount()
    {
    }
    
}