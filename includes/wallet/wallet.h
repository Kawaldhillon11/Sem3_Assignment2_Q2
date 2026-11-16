#include <stdexcept>
#include "includes/card/Card.h"

namespace wallet{
    class wallet
    {
    private:
        card::Card* cards[10]{};
        int noOfCards = 0;
    public:
        wallet(/* args */);
        void addCard(card::Card* card);
        int getNoOfCards();
        card::Card* getCard(int cardNumber);
        card::Card** getAllCards();
        ~wallet();
    };
    
    wallet::wallet(/* args */)
    {
    }

    void wallet::addCard(card::Card* card){
        if(noOfCards == 10)
            throw new std::invalid_argument("Wallet cannot hold more than 10 cards");
        
        cards[noOfCards] = card;
        noOfCards++;
    
    }

    int wallet::getNoOfCards(){
        return noOfCards;
    }

    card::Card* wallet::getCard(int cardNumber){
        if(!cardNumber)
            return nullptr;

        for (int i = 0; i < noOfCards; i++)
        {
            if(cards[i]->getCardNumber() == cardNumber)
                return cards[i];
        }
        return nullptr;
    }

    card::Card** wallet::getAllCards(){
        if(noOfCards == 0)
            return nullptr;

        return cards;
    }
    
    wallet::~wallet()
    {
    }
    
}