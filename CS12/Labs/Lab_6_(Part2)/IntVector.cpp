#include "IntVector.h"
#include <stdexcept>

IntVector::IntVector() 
{
    sz = 0;
    cap = 0;
    data = 0;
    
    return;
}

IntVector::IntVector(unsigned size, int value)
{
    sz = size;
    cap = size; //Can size be zero?? How to initialize an array with size zero??
    
    if (sz == 0)
    {
        expand();
    }
    else
    {
        data = new int[size]; //Don't need to check for negative sizes <= 0 because of unsigned
    }
    
    for (unsigned int i=0;i<size;++i)
    {
        *(data+i) = value;
    }
    
    return;
}

IntVector::~IntVector()
{
    if (data != 0)
    {
        delete data;
    }
    
    return;
}

unsigned IntVector::size() const
{
    return sz;
}

unsigned IntVector::capacity() const
{
    return cap;
}

bool IntVector::empty() const
{
    return (sz==0);
}

const int& IntVector::at(unsigned index) const
{
    if (index >= sz)
    {
        throw out_of_range("IntVector::at_range_check");
    }
    else
    {
        return *(data+index);
    }
}

const int& IntVector::front() const
{
    return *(data);
}

const int& IntVector::back() const
{
    return *(data+sz-1);
}

int & IntVector::at(unsigned index)
{
    if (index >= sz)
    {
        throw out_of_range("IntVector::at_range_check");
    }
    else
    {
        return *(data+index);
    }
}

int & IntVector::front()
{
    return *(data);
}

int & IntVector::back()
{
    return *(data+sz-1);
}

void IntVector::expand()
{
    if (data == 0)
    {
        cap += 1;
        data = new int[cap];
    }
    else
    {
        int *temp = data;
        
        cap *= 2;
        
        //data = 0;
        //delete data;
        data = new int[cap];
        
        for (unsigned int i=0;i<sz;++i)
        {
            //cout << "data+i: " << *(data+i) << " ";
            //cout << "temp+i: " << *(temp+i) << endl;
            *(data+i) = *(temp+i);
        }
    }
    return;
}

void IntVector::pop_back()
{
    if (!empty())
    {
        int *temp = data;
    
        sz -= 1;
    
        //data = 0;
        //delete data;
        data = new int[sz];
        
        for (unsigned int i=0;i<sz;++i)
        {
            *(data+i) = *(temp+i);
            /*cout << "data+i: " << *(data+i) << " ";
            cout << "temp+i: " << *(temp+i) << endl;*/
        }
    }
    
    return;
}

void IntVector::push_back(int value)
{
    if (data == 0)
    {
        cap += 1;
        data = new int[cap];
    }
        int *temp = data;   
        
        if (sz+1 > cap)
        {
            expand();
        }
            
        /*cout << "Before: " << endl;
        for (int i=0;i<sz;++i)
        {
               cout << "*(data+i): " << *(data+i) << endl;
        }        
        cout << endl;*/
            
        sz += 1;
            
        //data = 0;
        //delete data;
        data = new int[sz];
            
        for (unsigned int i=0;i<sz;++i)
        {
            //cout << "data+i: " << *(data+i) << " ";
            //cout << "temp+i: " << *(temp+i) << endl;
            *(data+i) = *(temp+i);
        }
            
        *(data+sz-1) = value;
            
        /*cout << "After: " << endl;
        for (int i=0;i<sz;++i)
        {
            cout << "*(data+i): " << *(data+i) << endl;
        }
        cout << endl;*/
            
        //temp = 0;
        //delete temp;
    
    return;
}

void IntVector::expand(unsigned amount)
{
    if (data == 0)
    {
        cap += 1;
        data = new int[cap];
    }
    else
    {
        int *temp = data;
        cap += amount;
        
        //data = 0;
        //delete data;
        data = new int[cap];
        
        for (unsigned int i=0;i<sz;++i)
        {
            //cout << "data+i: " << *(data+i) << " ";
            //cout << "temp+i: " << *(temp+i) << endl;
            *(data+i) = *(temp+i);
        }
        
        //temp = 0;
        //delete temp;
    }
    
    return;
}

void IntVector::clear()
{
    sz = 0;
    
    //data = 0;
    //delete data;
    data = new int[sz];
    
    return;
    
    //Don't need to change capacity?
}

void IntVector::erase(unsigned index)
{
    /*cout << "Before: " << endl;
    for (int i=0;i<sz;++i)
    {
        cout << *(data+i) << " ";
    }
    cout << endl;*/
    
    if (index >= sz)
    {
        throw out_of_range("IntVector::erase_range_check");
    }
    else
    {
        for (unsigned int i=index;i<sz-1;++i)
        {
            *(data+i) = *(data+i+1);
        }
    }
    
    /*cout << "After: " << endl;
    for (int i=0;i<sz;++i)
    {
        cout << *(data+i) << " ";
    }
    cout << endl;*/
    
    pop_back();
    
    return;
}

void IntVector::insert(unsigned index, int value)
{
    if (index > sz)
    {
        throw out_of_range("IntVector::insert_range_check");
    }
    else
    {
        if (sz+1 > cap)
        {
            expand();
        }
        
        sz += 1;
        
        int* temp = data;
        
        //delete data;
        data = new int[sz];
        
        for (unsigned int i=0;i<index;++i)
        {
            *(data+i) = *(temp+i);
        }
        
        *(data+index) = value;
        
        for (unsigned int i=index;i<sz;++i)
        {
            *(data+i+1) = *(temp+i);
        }
        
        //temp = 0;
        //delete temp;
    }
    
    return;
}

void IntVector::resize(unsigned size, int value)
{
    if (data == 0)
    {
        cap += 1;
        data = new int[cap];
    }
    int *temp = data;
    
    reserve(size);
    
    if (size < sz)
    {
        sz = size;
        
        //delete data; //Don't need to change capacity?
        data = new int[sz];  
        
        for (unsigned int i=0;i<sz;++i)
        {
            *(data+i) = *(temp+i);
        }
    }
    else if (size > sz)
    {
        while (size > sz)
        {
            push_back(value);
            //cout << "sz: " << sz << endl;
        }
    }
    
    return;
}

void IntVector::assign(unsigned n, int value)
{
    if ((n < sz) || (n > sz))
    {
        resize(n, 0);
    }
    
    for (unsigned int i=0;i<sz;++i)
    {
        *(data+i) = value;
    }
    
    return;
}

void IntVector::reserve(unsigned n)
{
    if (n > cap)
    {
        if ((cap*2) > (n))
        {
            while (cap < n)
            {
                expand();
            }
        }
        else
        {
            while (cap < n)
            {
                expand(n-cap);
            }
        }
    }
}