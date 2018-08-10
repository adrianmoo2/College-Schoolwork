#include "IntList.h"

IntList::IntList()
{
    head = 0;
    tail = 0;
    
    return;
}

IntList::IntList(const IntList &cpy)
{
    head = 0;
    tail = 0;
    for (IntNode *cur = cpy.head; cur != 0; cur = cur->next)
    {
        push_back(cur->data);
    }
    
    return;
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
    
    return;
}

IntList& IntList::operator=(const IntList &rhs)
{
    if (this != &rhs)
    {
        clear();
        
        head = 0;
        tail = 0;
        for (IntNode *cur = rhs.head; cur != 0; cur = cur->next)
        {
            push_back(cur->data);
        }
    
    }
    
    return *this;
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

void IntList::push_back(int value)
{
    if (!empty())
    {
        for (IntNode *cur = head; cur != 0; cur = cur->next)
        {
            if (cur->next == 0)
            {
                IntNode *temp;
                temp = new IntNode(value);
                
                cur->next = temp;
                temp->next = 0;
                
                tail = temp->next;
                
                break;
            }
        }
    }
    else
    {
        IntNode *temp;
        temp = new IntNode(value);
        
        head = temp;

        tail = 0;
    }
    return;
}

void IntList::selection_sort()
{
    if (!empty())
    {
        for (IntNode *cur = head; (cur->next != 0) && (cur != 0); cur = cur->next)
        {
            int min = cur->data;
            int j = min;
            int temp;
            
            for (IntNode *kur = cur->next; kur != 0; kur = kur->next)
            {
                if (kur->data < j)
                {
                    j = kur->data;
                }
            }
            
            for (IntNode* kur = cur->next; kur != 0; kur = kur->next)
            {
                if (j == kur->data)
                {
                    temp = min;
                    cur->data = j;
                    kur->data = temp;
                    break;
                }
            }
        }
    }
    return;
}

ostream& operator<<(ostream &out, const IntList &rhs)
{
    for (IntNode *cur = rhs.head; cur != 0; cur = cur->next)
    {
        out << cur->data;
        if (cur->next != 0)
        {
            out << " ";
        }
    }
    return out;
}

bool IntList::isDuplicate()
{
    if (!empty())
    {
        for (IntNode *cur = head; (cur != 0) && (cur->next != 0); cur = cur->next)
        {
            for (IntNode *nexNode = cur; (nexNode != 0) && (nexNode->next != 0); nexNode = nexNode->next)
            {
                if (cur->data == (nexNode->next)->data)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void IntList::remove_duplicates()
{
    if (!empty())
    {
        while (isDuplicate())
        {
            for (IntNode *cur = head; (cur != 0) && (cur->next != 0); cur = cur->next)
            {
                for (IntNode *nexNode = cur; (nexNode != 0) && (nexNode->next != 0); nexNode = nexNode->next)
                {
                    if (cur->data == (nexNode->next)->data)
                    {
                        IntNode *temp;
                        temp = nexNode->next;
                        
                        delete nexNode->next;
                        
                        nexNode->next = temp->next;
                    }
                }
                
            }
        }
    }
}

void IntList::insert_ordered(int value)
{
    if (!empty())
    {
        for (IntNode *cur = head; cur != 0; cur = cur->next)
        {
            if ((cur == head) && (value <= head->data))
            {
                push_front(value);
                
                break;
            }
            else if ((cur->next == 0) && (value >= cur->data))
            {
                push_back(value);
                
                break;
            }
            else
            {
                if ((value >= cur->data) && (value <= cur->next->data))
                {
                    IntNode *temp = new IntNode(value);
                    
                    temp->next = cur->next;
                    
                    cur->next = temp;
                    
                    break;
                    
                }
            }
        }
    }
    else
    {
        push_front(value);
    }
}

void IntList::clear()
{
    for (IntNode *cur = head; cur != 0; cur = cur-> next)
    {
        pop_front();
    }
    return;
}

void IntList::pop_front()
{
    if (!empty())
    {
        IntNode *temp = head;
        delete head;
        
        head = temp->next;
    }
    return;
}

bool IntList::empty() const
{
    return ((head == 0) && (tail == 0));
}