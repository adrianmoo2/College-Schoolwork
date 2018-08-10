#include <iostream>

using namespace std;

#include "IntList.h"


int main() {

  //tests constructor, destructor, push_front, pop_front, display

    IntList list;
    
    list.push_front(5);
    list.push_front(6);
    list.push_front(7);
    
    list.display();
    
    list.push_back(100);
    
    list.display();

   return 0;
}