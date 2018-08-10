#include "SortedSet.h"

SortedSet::SortedSet() : IntList()
{
    return;
}

SortedSet::SortedSet(const SortedSet &set) : IntList(set)
{
    remove_duplicates();
    selection_sort();
    
    return;
}

SortedSet::SortedSet(const IntList &list) : IntList(list)
{
    remove_duplicates();
    selection_sort();
    
    return;
}

SortedSet::~SortedSet()
{
    for (IntNode *cur = head; cur != 0; cur = cur->next)
    {
        IntList::pop_front();
    }
    
    return;
}

bool SortedSet::in(int data)
{
    for (IntNode *cur = head; cur != 0; cur = cur->next)
    {
        if (cur->data == data)
        {
            return true;
        }
    }
    
    return false;
}

const SortedSet SortedSet::operator|(const SortedSet &set) const
{
      SortedSet temp;
      
      for (IntNode *cur = head; cur != 0; cur = cur->next)
      {
          temp.add(cur->data);
      }
      
      for (IntNode *cur = set.head; cur != 0; cur = cur->next)
      {
          temp.add(cur->data);
      }
      
      temp.remove_duplicates();
      
      return temp;
  
}

const SortedSet SortedSet::operator&(const SortedSet &set) const
{
    SortedSet temp;
    
    for (IntNode *cur = head; cur != 0; cur = cur -> next)
    {
        for (IntNode *setCur = set.head; setCur != 0; setCur = setCur ->next)
        {
            if (cur->data == setCur->data)
            {
                temp.add(cur->data);
            }
        }
    }
    
    return temp;
}

void SortedSet::add(int data)
{
    if (!IntList::empty())
    {
        for (IntNode *cur = head; cur != 0; cur = cur->next)
        {
            if (data == cur->data)
            {
                return;
            }
            else if ((cur == head) && (data < head->data))
            {
                IntList::push_front(data);
                
                break;
            }
            else if ((cur->next == 0) && (data > cur->data))
            {
                IntList::push_back(data);
                
                break;
            }
            else
            {
                if ((data > cur->data) && (data < cur->next->data))
                {
                    IntNode *temp = new IntNode(data);
                    
                    temp->next = cur->next;
                    
                    cur->next = temp;
                    
                    break;
                    
                }
            }
        }
    }
    else
    {
        IntList::push_front(data);
        
        return;
    }
}

void SortedSet::push_front(int data)
{
    add(data);
}

void SortedSet::push_back(int data)
{
    add(data);
}

void SortedSet::insert_ordered(int data)
{
    add(data);
}

const SortedSet SortedSet::operator|=(const SortedSet &set)
{
      SortedSet temp;
      
      for (IntNode *cur = head; cur != 0; cur = cur->next)
      {
          temp.add(cur->data);
      }
      
      for (IntNode *cur = set.head; cur != 0; cur = cur->next)
      {
          temp.add(cur->data);
      }
      
      temp.remove_duplicates();
      
      *this = temp;
      
      return temp;
}

const SortedSet SortedSet::operator&=(const SortedSet &set)
{
    SortedSet temp;
    
    for (IntNode *cur = head; cur != 0; cur = cur -> next)
    {
        for (IntNode *setCur = set.head; setCur != 0; setCur = setCur ->next)
        {
            if (cur->data == setCur->data)
            {
                temp.add(cur->data);
            }
        }
    }
    
    *this = temp;
    
    return temp;
}