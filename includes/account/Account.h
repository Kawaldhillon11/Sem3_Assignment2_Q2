
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <stdexcept>

namespace account
{

    class Account
    {
        private:

            int accountNumber;
            std::string accountHolder;
            inline static int accountCount = 1;

            void setHolderName(std::string);

        public:
            Account(std::string name);

            void virtual withdraw(double amount);

            ~Account();
    };
    
    
} // namespace account


#endif