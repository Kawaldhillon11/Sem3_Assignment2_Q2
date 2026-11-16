#include <stdexcept>

#include "includes/wallet/wallet.h"

namespace wallet
{
    wallet::wallet()
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
    
} // namespace wallet
