#include "includes/card/Card.h"

namespace wallet{
    class wallet
    {
    private:
        card::Card* cards[10]{};
        int noOfCards = 0;
    public:
        wallet();
        void addCard(card::Card* card);
        int getNoOfCards();
        card::Card* getCard(int cardNumber);
        card::Card** getAllCards();
        ~wallet();
    };
    
}