#include "Deck.h"
#include <cstdlib>

//This is the function you implemented for PROGRAM 3
ostream & operator<<(ostream &, const vector<Card> &);

/* Sorts the contents of v into suit order,
   i.e., all clubs first (in numerically ascending order),
   then all diamonds (in ascending order),
   then all hearts (in ascending order),
   and finally all spades (in ascending order).
   Calls mergeSort recursive function to actually sort the vector.
*/
void sortBySuit(vector<Card> &v);

/* Uses the recursive merge sort algorithm to sort the contents
   of the vector from begin to end in suit order.
   (see above SortBySuit function for definition of suit order)
   Uses merge helper function to merge the two sorted
   halves.
*/
void mergeSort(vector<Card> &v, unsigned begin, unsigned end);

/* Assumes all values from begin to mid are in suit order,
   (see above SortBySuit function for definition of suit order)
   and all values from mid + 1 to end are in suit order.
   Merges the two halves so that all values from begin to end
   are in suit order.
*/

void merge(vector<Card> &v, unsigned begin, unsigned mid, unsigned end);

void fillHand(vector<Card> &hand, Deck &d, unsigned handSize) {
   hand.resize(handSize);
   for (unsigned i = 0; i < hand.size(); ++i) {
      hand.at(i) = d.dealCard();
   }
}

ostream & operator<<(ostream &stream, const vector<Card> &deck)
{
   if (deck.size() > 0)
   {
       for (unsigned int i=0;i<deck.size()-1;++i)
       {
           stream << deck.at(i) << ", ";
       }
       stream << deck.at(deck.size()-1);
       return stream;
   }
   else
   {
      return stream;
   }
}

void sortBySuit(vector<Card> &v)
{
   if (v.size() > 0)
   {
       mergeSort(v, 0, v.size()-1);   
   }
   return;
}

void merge(vector<Card> &v, unsigned begin, unsigned mid, unsigned end)
{
   unsigned int mergedSize = end - begin + 1;       // Size of merged partition
   vector<Card> mergedNumbers(v.size());    // Temporary array for merged numbers
   unsigned int mergePos = 0;                 // Position to insert merged number
   unsigned int leftPos = 0;                  // Position of elements in left partition
   unsigned int rightPos = 0;                 // Position of elements in right partition
   
   leftPos = begin;                      // Initialize left partition position
   rightPos = mid + 1;                 // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= mid && rightPos <= end) {
      if (v.at(leftPos).getSuit() < v.at(rightPos).getSuit())
      {
          mergedNumbers.at(mergePos) = v.at(leftPos);
         ++leftPos;
      }
      else if (v.at(leftPos).getSuit() > v.at(rightPos).getSuit())
      {
         mergedNumbers.at(mergePos) = v.at(rightPos);
         ++rightPos;
      }
      else
      {
         if (v.at(leftPos).getRank() < v.at(rightPos).getRank()) {
            mergedNumbers.at(mergePos) = v.at(leftPos);
            ++leftPos;
         }
         else {
            mergedNumbers.at(mergePos) = v.at(rightPos);
            ++rightPos;
            
         }
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= mid) {
      mergedNumbers.at(mergePos) = v.at(leftPos);
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= end) {
      mergedNumbers.at(mergePos) = v.at(rightPos);
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      v.at(begin + mergePos) = mergedNumbers.at(mergePos);
   }
}

void mergeSort(vector<Card> &v, unsigned begin, unsigned end)
{
   int j = 0;
   
   if (begin < end) {
      j = (begin + end) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      mergeSort(v, begin, j);
      mergeSort(v, j + 1, end);
      
      // Merge left and right partition in sorted order
      merge(v, begin, j, end);
   }
}

int main() {
   vector<Card> hand;
   Deck deck;
   int handSize;
   int seed;
   cout << "Enter seed value: ";
   cin >> seed;
   cout << endl;
   cout << "Enter hand size: ";
   cin >> handSize;
   cout << endl;

   srand(seed);
   deck.shuffleDeck();
   fillHand(hand, deck, handSize);
   cout << hand << endl;
   sortBySuit(hand);
   cout << hand << endl;
   return 0;
}