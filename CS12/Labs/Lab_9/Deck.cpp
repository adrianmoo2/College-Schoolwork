#include "Deck.h"
#include <algorithm>

Deck::Deck()
{
    vector<char> suitVec;
    suitVec.push_back('c');
    suitVec.push_back('d');
    suitVec.push_back('h');
    suitVec.push_back('s');
    
    int rank;
    char suit;
    
    Card c;
    
    for (int i=3;i>=0;--i)
    {
        for (int j=13;j>=1;--j)
        {
            rank = j;
            suit = suitVec.at(i);
            
            c = Card(suit, rank);
            
            theDeck.push_back(c);
        }
    }
}

Card Deck::dealCard()
{
    Card c;
    
    c = theDeck.back();
    
    theDeck.pop_back();
    
    dealtCards.push_back(c);
    
    return c;
}

void Deck::shuffleDeck()
{
    Card c;
    
    int dealtCardsSize = dealtCards.size();
    
    for (int i=0;i<dealtCardsSize;++i)
    {
        c = dealtCards.at(i);
        
        theDeck.push_back(c);
    }
    dealtCards.clear();
    random_shuffle(theDeck.begin(), theDeck.end());
}

unsigned Deck::deckSize() const
{
    return theDeck.size();
}
