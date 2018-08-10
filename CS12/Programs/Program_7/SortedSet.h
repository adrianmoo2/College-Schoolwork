#include "IntList.h"

class SortedSet : public IntList {
  public:
    SortedSet();
    SortedSet(const SortedSet &set);
    SortedSet(const IntList &list);
    ~SortedSet();
    
    bool in(int data);
    const SortedSet operator|(const SortedSet &set) const;
    const SortedSet operator&(const SortedSet &set) const;
    
    void add(int data);
    void push_front(int data);
    void push_back(int data);
    void insert_ordered(int data);
    
    const SortedSet operator|=(const SortedSet &set);
    const SortedSet operator&=(const SortedSet &set);
    
    
};