#include <iostream>
using namespace std;

struct IntNode {
    int data;
    IntNode *next;
    IntNode(int data) : data(data), next(0) {}
};

class IntList {
    private:
        IntNode *head;
        IntNode *tail;
    public:
        IntList();
        ~IntList();
        void display() const;
        void push_front(int value);
        void pop_front();
        bool empty() const;
        
        IntList(const IntList &cpy);
        IntList & operator=(const IntList &rhs);
        void push_back(int value);
        void clear();
        void selection_sort();
        void insert_ordered(int value);
        void remove_duplicates();
        bool isDuplicate();
        friend ostream & operator<<(ostream &out, const IntList &rhs);
};