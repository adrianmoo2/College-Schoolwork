#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <limits>
#include <math.h>

using namespace std;

//------------------------------------Fraction Stuff-------------------------------

class Fraction
{
    int gcd(int a, int b) {return b==0 ? a : gcd(b,a%b); }
    int n, d;
 public:
    Fraction(int n, int d = 1) : n(n/gcd(n,d)), d(d/gcd(n,d)) {}
    int num() const { return n; }
    int den() const { return d; }
    Fraction& operator*=(const Fraction& rhs) {
        int new_n = n*rhs.n / gcd(n*rhs.n, d*rhs.d);
        d = d*rhs.d / gcd(n*rhs.n, d*rhs.d);
        n = new_n;
        return *this;
    }
};
std::ostream& operator<<(std::ostream& out, const Fraction& f){
   return out << f.num() << '/' << f.den() ;
}
bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return ((lhs.num() * rhs.den()) == (rhs.num() * lhs.den()));
}
bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() < rhs.num() * lhs.den());
}
bool operator>(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() > rhs.num() * lhs.den());
}
Fraction operator*(Fraction lhs, const Fraction& rhs)
{
    return lhs *= rhs;
}

//--------------------------------Global functions start here----------------------------------------------
void regularReadToVector(string s, vector<int> &vec);
void fractionReadToVector(string s, vector<Fraction> &vec);
template<typename Type>
void squareSort(vector<Type> &vec);

template<typename Type>
void selectionSort(vector<Type> &vec, vector<int> indices, int sizeOfBlock, int sizeOfLastBlock);

template<typename Type>
void reverseInsertion(vector<Type> &vec, typename vector<Type>::iterator starting, typename vector<Type>::iterator ending);

template<typename Type>
void insertRight(vector<Type> &vec, vector<int>::iterator starting, vector<int>::iterator ending);


int main(int argc, char* argv[])
{
    // --------------------------------Reads in the file and makes the output file----------------------
    
    string origFileName;
    string outAppend = ".out";
    int index = 0;
    ofstream myOutput;
    ifstream myfile;
    string modifiedFileName;
    string inputtedFromFile;
    vector<int> inputsFromFileInt;
    vector<Fraction> inputsFromFileFraction;
    bool isFraction = false;
    
    
    if (argc > 1)
    {
        origFileName = argv[1];
        //cout << origFileName;
        ifstream myfile(origFileName.c_str());
        
        for (int i=0;i<origFileName.length();++i)
        {
            if (origFileName.at(i) == '.')
            {
                index = i;
            }
        }
    
        modifiedFileName = origFileName;
        modifiedFileName.replace(index, modifiedFileName.length()-index, outAppend);
        
        myOutput.open(modifiedFileName.c_str());
        
        while (getline(myfile, inputtedFromFile))
        {
            inputsFromFileInt.clear(); //clearing the vector for each different test case
            inputsFromFileFraction.clear();
            if (inputtedFromFile == "i")
            {
                isFraction = false;
            }
            else if (inputtedFromFile == "f")
            {
                isFraction = true;
            }
            else if (isFraction)   //Test case reading the data
            {
                fractionReadToVector(inputtedFromFile, inputsFromFileFraction);
                /*cout << "Fractions: " << endl;    //Code to test output of reading to fraction vector function
                for (int i=0;i<inputsFromFileFraction.size();++i)
                {
                    cout << inputsFromFileFraction.at(i) << " ";
                }*/
            }
            else
            {
                regularReadToVector(inputtedFromFile, inputsFromFileInt); //reads the input to a vector
                squareSort(inputsFromFileInt);
                cout << endl; // Code to test output of reading to vector function
                cout << "Integers: " << endl;
                for (int i=0;i<inputsFromFileInt.size();++i)
                {
                    cout << inputsFromFileInt.at(i) << " ";
                }
                cout << endl;
            }
        }
    }
    else
    {
        // What to read from without an input file?
        cout << "You did not enter an input file. Please enter one and try again";
        return 0;
    }
    
    
    
    
    return 0;
}

//-------------Custom function implementation starts here----------------

void regularReadToVector(string s, vector<int> &vec)
{
    string temp = "";
    int tempInt;
    
    for (int i=0;i<s.length();++i)
    {
        if (i == s.length()-1 && s.at(i) != ' ')
        {
            temp += s.at(i);
        }
        if (s.at(i) == ' ' || i == s.length()-1)
        {
            istringstream buffer(temp);
            buffer >> tempInt;
            
            vec.push_back(tempInt);
            temp = "";
        }
        temp += s.at(i);
    }
}

void fractionReadToVector(string s, vector<Fraction> &vec)
{
    int numerator = numeric_limits<int>::min();
    int denominator = numeric_limits<int>::min();
    string temp = "";
    int tempInt;
    
    for (int i=0;i<s.length();++i)
    {
        if (i == s.length()-1 && s.at(i) != ' ')
        {
            temp += s.at(i);
        }
        if ((s.at(i) == ' ' || i == s.length()-1) && numerator == numeric_limits<int>::min())
        {
            istringstream buffer(temp);
            buffer >> tempInt;
            
            numerator = tempInt;
            temp = "";
        }
        else if ((s.at(i) == ' ' || i == s.length()-1) && denominator == numeric_limits<int>::min() && numerator != numeric_limits<int>::min())
        {
            istringstream buffer(temp);
            buffer >> tempInt;
            
            denominator = tempInt;
            
            Fraction f(numerator, denominator);
            
            vec.push_back(f);
            numerator = numeric_limits<int>::min();
            denominator = numeric_limits<int>::min();
            temp = "";
        }
        temp += s.at(i);
    }
    
}

//------------------Sort functions start here--------------------

template<typename Type>
void squareSort(vector<Type> &vec)
{
    vector<int> left;
    int blocks = static_cast<int>(sqrt(vec.size()));
    int sizeOfBlocks = static_cast<int>(vec.size()/blocks);
    int sizeOfLastBlock = 0;
    
    if (vec.size() - blocks*sizeOfBlocks != 0)
    {
        sizeOfLastBlock = vec.size() - sizeOfBlocks*(blocks-1);
    }
    else
    {
        sizeOfLastBlock = sizeOfBlocks;
    }
    
    
    for (int i=0;i<vec.size();++i)
    {
        if (sizeOfBlocks == sizeOfLastBlock)
        {
            if (i%sizeOfBlocks == 0)
            {
                left.push_back(i);
            }
        }
        else if (i == vec.size()-sizeOfLastBlock)
        {
            left.push_back(i);
        }
        else if (i < vec.size()-sizeOfLastBlock && i%sizeOfBlocks == 0)
        {
            left.push_back(i);
        }
        
        /*else
        {
            if (if ())
            {
                left.push_back(i+1);    //Last element would be one past the last index of the vector
            }
        }*/
    }
    left.push_back(vec.size());
    
    cout << "blocks: " << blocks << endl;
    cout << "size of blocks: " << sizeOfBlocks << endl;
    cout << "sizeOfLastBlock: " << sizeOfLastBlock << endl;
    
    for (int i=0;i<left.size();++i)
    {
        cout << "left: " << left.at(i) << endl;
    }
    
    for (vector<int>::iterator it = left.begin(); it != left.end()-1; ++it)
    {
        insertRight(vec,  it, it+1);
    }
    
    cout << "Integers: " << endl;
    
    for (int i=0;i<vec.size(); ++i)
    {
        cout << vec.at(i) << " ";
    }
    
    cout << endl;
    
    selectionSort(vec, left, sizeOfBlocks, sizeOfLastBlock);
    
}

template<typename Type>
void selectionSort(vector<Type> &vec, vector<int> indices, int sizeOfBlocks, int sizeOfLastBlock)
{
    vector<int>::iterator tempIterator;
    vector<int> tempVec = indices;
    
    for (int i=0;i<vec.size();++i)
    {
        Type min = vec.at(i);
        
        for (vector<int>::iterator it = indices.begin(); it != indices.end(); ++it)
        {
            if (*it < vec.size() && vec.at(*it) < min)
            {
                min = vec.at(*it);
                tempIterator = it;
            }
        }
        
        cout << "min is: " << min << " from index: " << *tempIterator << endl;
        vec.at(*tempIterator) = vec.at(i);
        vec.at(i) = min;

        
        
        if (vec.size()-sizeOfLastBlock == *tempIterator)
        {
            cout << "shifting the element " << vec.at(*tempIterator) << " to " << *(indices.begin()+indices.size()-1) << endl;
            insertRight(vec, tempIterator, indices.begin()+indices.size()-1);
        }
        else
        {
            cout << "shifting the element " << vec.at(*tempIterator) << " into the block: " << *tempIterator << " to " << *(tempIterator+1) << endl;
            insertRight(vec, tempIterator, tempIterator+1);
        }
        if (indices.size() > 1 && indices.at(0) == indices.at(1))
        {
            cout << "erasing " << indices.at(0) << endl;
            indices.erase(indices.begin());
            indices.at(0) += 1;
        }
        else {
                indices.at(0) += 1;
        }
        
        
        cout << "vector is now: ";
        for (int i = 0;i<vec.size();++i)
        {
            cout << vec.at(i) << " ";
        }
        cout << endl << endl;
    }
    
}

template<typename Type>
void insertRight(vector<Type> &vec, vector<int>::iterator starting, vector<int>::iterator ending)
{
        for (int i = (*ending)-1; i >= (*starting)+1; --i)
        {
            for (int j = i-1; j >= *starting; --j)
            {
                cout << "Comparing index i: " << i << " to index j: " << j << endl;
                cout << "Which are i: " << vec.at(i) << " and j: " << vec.at(j) << endl;
                if (vec.at(j) > vec.at(i))
                {
                    Type temp = vec.at(i);
                    vec.at(i) = vec.at(j);
                    vec.at(j) = temp;
                }
            }
        }
}

/*template<typename Type>
void insertRight(vector<Type> &vec, int startingIndex, int endingIndex)
{
    Type temp;
    /*cout << "starting startingIndex: " << startingIndex << endl;
    cout << "starting endingIndex: " << endingIndex << endl;
    cout << "vec at startingIndex: " << vec.at(startingIndex) << endl;
    cout << "vec at endingIndex: " << vec.at(endingIndex) << endl << endl;
    
    for (int i = startingIndex;i < endingIndex-1; ++i)
    {
        for (int j = i+1; j < endingIndex; ++j)
        {
            if (vec.at(i) > vec.at(j))
            {
                cout << "vec.at(i): " << vec.at(i) << endl;
                cout << "vec.at(j): " << vec.at(j) << endl;
                temp = vec.at(j);
                vec.at(j) = vec.at(i);
                vec.at(i) = temp;
            }
        }
    }
    cout << endl;
}
*/