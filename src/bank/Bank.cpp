#include <string>
#include <stdexcept>

#include "includes/bank/Bank.h"
#include "includes/account/Account.h"

namespace bank{
    Bank::Bank(std::string instituteName)
    {
       setInstituteName(instituteName);
    }

    void Bank::setInstituteName(std::string instituteName){
        if(instituteName.empty())
            throw new std::invalid_argument("Institute's Name cannot be empty");

        name = instituteName;
    }

    int Bank::getNoOfAccounts(){
        return noOfAccounts;
    }

    void Bank::addAccount(account::Account* acc){
        if(noOfAccounts == 10 )
            throw new std::invalid_argument("Maximum no of accounts reached");
        
        accounts[noOfAccounts] = acc;
    }

    account::Account* Bank::getAccount(int accountNumber){
        if(!accountNumber)
            return nullptr;

        for (int i = 0; i < noOfAccounts; i++)
        {
            if(accounts[i]->getAccountNumber() == accountNumber)
                return accounts[i];
        }
        return nullptr;
        
    }

    account::Account** Bank::getALLAccounts(){
        if(noOfAccounts == 0)
            return nullptr;

        return accounts;
    }

    Bank::~Bank()
    {
    }
    
}