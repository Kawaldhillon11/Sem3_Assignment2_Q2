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
        double cashBackEarned = 0;

    public:
        CreditAccount(std::string name, double cardLimit);

        double getLimit();
        double getBalance();
        double getCashBackEarned();
        void withdraw(double amount);
        void setCashBackEarned(double cashBack);

        ~CreditAccount();
    };

} // namespace account


#endif