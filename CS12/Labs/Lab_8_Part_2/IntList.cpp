#include "IntList.h"

IntList::IntList()
{
    head = 0;
    
    return;
}

void IntList::push_front(int value)
{
    IntNode *temp = new IntNode(value);
    IntNode *temp2 = head;
    
    temp->next = temp2;
    
    head = temp;
    
    return;
}

bool IntList::exists(int value) const
{
    return exists(head, value);
}

bool IntList::exists(IntNode *node, int value) const
{
    if (head != 0)
    {
        if (node->data == value)
        {
            return true;
        }
        else
        {
            if (node->next == 0)
            {
                return false;
            }
            return exists(node->next, value);
        }
    }
    return false;
}

ostream& operator<<(ostream &out, const IntList &rhs)
{
    return (out << rhs.head);
}

ostream& operator<<(ostream &out, IntNode *node)
{
    if (node == 0)
    {
        return out;
    }
    else
    {
        out << node->data;
        if (node->next != 0)
        {
            out << " ";
        }
        node = node->next;
        
        return (out << node);
    }
}