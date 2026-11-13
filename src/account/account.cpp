#include "includes/account/Account.h"

namespace account {
    
    Account::Account(std::string name)
    {
        accountNumber = accountCount;
        setHolderName(name);
        accountCount++;
    }

    int Account::getAccountNumber(){
        return accountNumber;
    }


    void Account::setHolderName(std::string name){
        if(name.empty())
            throw new std::invalid_argument("Account Holder Name cannot be Empty");
        if(name.length() > 50)
            throw new std::invalid_argument("Account Holder name too long");

        accountHolder = name;
        
    };

    void Account::withdraw(double amount){
        
    }
    
    Account::~Account()
    {
    }
}

