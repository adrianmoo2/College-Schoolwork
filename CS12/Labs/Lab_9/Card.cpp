#include "Card.h"
#include <cstdlib>

Card::Card()
{
    suit = 'c';
    rank = 2;
    
    return;
}

Card::Card(char c, int x)
{
    if (c == 'c' || c == 'C')
    {
        suit = 'c';
    }
    else if (c == 'd' || c == 'D')
    {
        suit = 'd';
    }
    else if (c == 'h' || c == 'H')
    {
        suit = 'h';
    }
    else if (c == 's' || c == 'S')
    {
        suit = 's';
    }
    
    if (x > 13 || x < 1)
    {
        rank = 2;
    }
    else
    {
        rank = x;
    }
    
    return;
}

char Card::getSuit() const
{
    return suit;
}

int Card::getRank() const
{
    return rank;
}

ostream& operator<<(ostream& stream, const Card& c)
{
    string suitOutput;
    
    vector<string> ranks;
    ranks.push_back("Ace");
    ranks.push_back("2");
    ranks.push_back("3");
    ranks.push_back("4");
    ranks.push_back("5");
    ranks.push_back("6");
    ranks.push_back("7");
    ranks.push_back("8");
    ranks.push_back("9");
    ranks.push_back("10");
    ranks.push_back("Jack");
    ranks.push_back("Queen");
    ranks.push_back("King");
    
    if (c.suit == 'c')
    {
        suitOutput = "Clubs";
    }
    else if (c.suit == 'd')
    {
        suitOutput = "Diamonds";
    }
    else if (c.suit == 'h')
    {
        suitOutput = "Hearts";
    }
    else if (c.suit == 's')
    {
        suitOutput = "Spades";
    }
    
    stream << ranks.at(c.rank-1) << " of " << suitOutput;
    
    return stream;
}












