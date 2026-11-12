#ifndef CREDIT_ACCOUNT_H
#define CREDIT_ACCOUNT_H

#include <string>
#include "Account.h"

namespace account
{
    class CreditAccount : public Account
    {
    private:
        double limit;
        double balance;

    public:
        CreditAccount(std::string name, double cardLimit);

        void withdraw(double amount);

        ~CreditAccount();
    };

} // namespace account


#endif