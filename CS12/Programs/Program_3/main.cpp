#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Deck.h"

bool hasPair(const vector<Card> &vec);
ostream & operator<<(ostream &, const vector<Card> &);

int main()
{
    srand(2222);
    
    string fileYesNo;
    string fileName;
    ofstream myFile;
    int cardsPerHand;
    int simulations;
    vector<Card> dealtCards;
    double probability;
    
    
    cout << "Do you want to output all hands to a file?(Yes/No) ";
    cin >> fileYesNo;
    cout << endl;
    
    if (fileYesNo == "Yes")
    {
        cout << "Enter name of output file: ";
        cin >> fileName;
        
        myFile.open(fileName.c_str());
        
        cout << endl;
    }
    
    cout << "Enter number of cards per hand: ";
    cin >> cardsPerHand;
    cout << endl;
    
    cout << "Enter number of deals (simulations): ";
    cin >> simulations;
    cout << endl;
    
    Deck d;
    d.shuffleDeck();
    
    Card c;
    
    for (int i=0;i<simulations;++i)
    {
        for (int j=0;j<cardsPerHand;++j)
        {
            c = d.dealCard();
            dealtCards.push_back(c);
        }
        if (hasPair(dealtCards))
        {
            if (fileYesNo == "Yes")
            {
                ++probability;
                myFile << "Found Pair!! ";
                myFile << dealtCards;
            }
            else if (fileYesNo == "No")
            {
                ++probability;
            }
        }
        else if (!hasPair(dealtCards))
        {
            if (fileYesNo == "Yes")
            {
                myFile << "             ";
                myFile << dealtCards;
            }
        }
        d.shuffleDeck();
        dealtCards.clear();
    }
    
    cout << "Chances of receiving a pair in a hand of " << cardsPerHand << " cards is: " << setprecision(4) << (probability/simulations)*100 << "%" << endl;
       
    return 0;
}

ostream & operator<<(ostream &stream, const vector<Card> &deck)
{
    for (unsigned int i=0;i<deck.size()-1;++i)
    {
        stream << deck.at(i) << ", ";
    }
    stream << deck.at(deck.size()-1);
    stream << endl;
    return stream;
}

bool hasPair(const vector<Card> &deck)
{
    for (unsigned int i=0;i<deck.size()-1;++i)
    {
        for (unsigned int j=i+1;j<deck.size();++j)
        {
            if (deck.at(i).getRank() == deck.at(j).getRank())
            {
                return true;
            }
        }
    }
    return false;
}