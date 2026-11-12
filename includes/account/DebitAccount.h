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
            double balance;
        public:
            DebitAccount(std::string name);

            void withdraw(double amount);

            ~DebitAccount();
    };
    
} // namespace account


#endif