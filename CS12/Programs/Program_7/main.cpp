#include "SortedSet.h"

int main()
{
    SortedSet set;
    SortedSet set2;
    
    set.add(5);
    set.push_front(6);
    set.push_back(8);
    
    set2.add(10);
    set2.add(11);
    set2.add(5);
    set2.add(6);
    
    set.display();
    
    cout << endl;
    
    set2.display();
    
    cout << endl;

    cout << set.in(5) << endl;
    cout << set.in(0) << endl;
    
    SortedSet set3 = set &= set2;
    
    set.display();
    
    cout << endl;
    set3.display();
    
    set.pop_front();
    set.pop_front();
    set.pop_front();
    
    set2.pop_front();
    set2.pop_front();
    set2.pop_front();
    set2.pop_front();
    
}