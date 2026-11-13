#include <string>
#include "includes/account/Account.h"

namespace bank{
    class Bank
    {
        private:
            std::string name;
            account::Account* accounts[10]{};
            int noOfAccounts = 0;
            void setInstituteName(std::string instituteName);
        public:
            Bank(std::string instituteName);
            void addAccount(account::Account* acc);
            int getNoOfAccounts();
            account::Account* getAccount(int acountNumber);
            account::Account** getALLAccounts();
            ~Bank();
    };
    
}