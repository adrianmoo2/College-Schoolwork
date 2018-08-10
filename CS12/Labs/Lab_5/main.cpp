#include <iostream>
#include <climits>
using namespace std;

double mean(const double array[], int arraySize);
void remove(double array[], int arraySize, int index);
void display(const double array[], int arraySize);

int main()
{
    double array[10];
    double temp = 0.0;
    double meanNum = 0.0;
    int index = 0;
    int counter = 0;

    cout << "Enter 10 values:" << endl;
    
    while (counter != 10)
    {
        cin >> temp;
        array[counter] = temp;
        ++counter;
    }
    
    cout << endl;
    
    meanNum = mean(array, 10);
    cout << "Mean: " << meanNum << endl << endl;
    
    cout << "Enter index of value to be removed: ";
    cin >> index;
    cout << endl;
    
    cout << "Before removing value: ";
    display(array, 10);
    cout << endl;
    
    remove (array, 10, index);
    cout << "After removing value: ";
    display(array, 10);
    cout << endl;
    
    
    
    return 0;
}

double mean(const double array[], int arraySize)
{
    double result = 0.0;
    for (int i=0;i<arraySize;++i)
    {
        result += array[i];
    }
    
    return (result/arraySize);
}

void remove(double array[], int arraySize, int index)
{
    for (int i=index;i<arraySize-1;++i)
    {
        array[i] = array[i+1];
    }
    if (index != arraySize-1)
    {
        array[arraySize-1] = INT_MAX;
    }
    
    return;
}

void display(const double array[], int arraySize)
{
    if (array[arraySize-1] != INT_MAX)
    {
        for (int i=0;i<arraySize-1;++i)
        {
            cout << array[i] << ", ";
        }
        cout << array[arraySize-1];
    }
    else
    {
        for (int i=0;i<arraySize-2;++i)
        {
            cout << array[i] << ", ";
        }
        cout << array[arraySize-2];
    }
    
    return;
}