#include "IntList.h"

IntList::IntList()
{
    head = 0;
    tail = 0;
}

IntList::~IntList()
{
    if (head != 0)
    {
        delete head;
    }
    if (tail != 0)
    {
        delete tail;
    }
}

void IntList::display() const
{
    if (!empty())
    {
        for (IntNode *cur=head; cur!=0; cur = cur->next)
        {
            cout << cur->data;
            if (cur->next != 0)
            {
                cout << " ";
            }
        }
    }
}

void IntList::push_front(int value)
{
    IntNode *temp = new IntNode(value);
    IntNode *temp2 = head;
    
    temp->next = temp2;
    
    head = temp;
}

void IntList::pop_front()
{
    if (!empty())
    {
        IntNode *temp = head;
        delete head;
        
        head = temp->next;
    }
}

bool IntList::empty() const
{
    return ((head == 0) && (tail == 0));
}