#include "IntVector.h"

int main()
{
    IntVector intVec;
    
    cout << "Size: " << intVec.size() << endl;
    cout << "Cap: " << intVec.capacity() << endl;
    cout << "Empty: " << intVec.empty() << endl;
    cout << "At Front: " << intVec.front() << endl;
    cout << "At Back: " << intVec.back() << endl << endl;
    
    /*intVec.pop_back();
    
    cout << "Size and capacity after pop back: " << endl;
    cout << "Size: " << intVec.size() << endl; 
    cout << "Capacity: " << intVec.capacity() << endl;*/
    
   /*intVec.push_back(6);
    intVec.push_back(7);
    intVec.push_back(6);
    intVec.push_back(7);
    intVec.push_back(6);
    intVec.push_back(7);   
    intVec.push_back(6);
    intVec.push_back(7);
    
    
    cout << "Size and capacity after push back: " << endl;
    cout << "Size: " << intVec.size() << endl;
    cout << "Capacity: " << intVec.capacity() << endl << endl;*/
    
    /*intVec.clear();
    
    cout << "Size and capacity after clear: " << endl;
    cout << "Size: " << intVec.size() << endl;
    cout << "Capacity: " << intVec.capacity() << endl << endl;
    
    intVec.erase(0);
    
    cout << "Size and capacity after erase: " << endl;
    cout << "Size: " << intVec.size() << endl;
    cout << "Capacity: " << intVec.capacity() << endl<< endl;*/
    
    /*intVec.insert(0, 1);
    
    cout << "Size and capacity after insert: " << endl;
    cout << "Size: " << intVec.size() << endl;
    cout << "Capacity: " << intVec.capacity() << endl << endl;*/
    
    intVec.resize(10);
    
    cout << "Size and capacity after resize: " << endl;
    cout << "Size: " << intVec.size() << endl;
    cout << "Capacity: " << intVec.capacity() << endl;
    cout << "At Front: " << intVec.front() << endl;
    cout << "At Back: " << intVec.back() << endl << endl;
    
    /*intVec.assign(41, 6);
    
    cout << "Size and capacity after resize: " << endl;
    cout << "Size: " << intVec.size() << endl;
    cout << "Capacity: " << intVec.capacity() << endl;
    cout << "At Front: " << intVec.front() << endl;
    cout << "At Back: " << intVec.back() << endl << endl;*/
    
    /*intVec.reserve(20);
    
    cout << "Size and capacity after reserve: " << endl;
    cout << "Size: " << intVec.size() << endl;
    cout << "Capacity: " << intVec.capacity() << endl;*/
    
    return 0;
}