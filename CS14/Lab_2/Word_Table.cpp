#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

class TableItem {
    string w; //holds the word associated with class, initialized by constructor
    vector<int> positions; //need to increment position by 1 at the end
  public:
    TableItem(string word);
    void setWord(string newWord); //sets value of w=newWord if not already initialized in const.
    string word(); //returns w
    void newPos(int p); //appends p to end of vector v
    int atPos(int p);
    int posSize(); //returns value of v.size
};

void insertInListExisting(list<TableItem> &wordList, string word, int pos);
void printList(list<TableItem> wordList);
void insertInList(list<TableItem> &list, string word, int pos);
bool existsInList(list<TableItem> list, string word);
string makeLower(string word);
ofstream myOutput;


TableItem::TableItem(string word)
{
    w = word;
}
void TableItem::setWord(string newWord)
{
    w = newWord;
}
string TableItem::word()
{
    return w;
}
void TableItem::newPos(int p)
{
    positions.push_back(p);
}
int TableItem::atPos(int p)
{
    return positions.at(p);
}
int TableItem::posSize()
{
    return positions.size();
}

// -----------------Main Function---------------

int main(int argc, char* argv[])
{
    string file = "table_";
    string def = "raw.txt";
    string randomName = "aki.txt";
    string input = "";
    string myInput = "";
    int x = 0;
    int l = 0;
    
    if (argc > 1)
    {
        input = argv[1];
        file += input;
        myOutput.open(file.c_str());
    }
    else
    {
        file += randomName;
        myOutput.open(file.c_str());
    }
    
    list<TableItem> lul;
    
    ifstream myfile(input.c_str());
    
    char tempChar;
    string word = "";
    int position = 0;
    
    int firstMost = 0;
    int firstMostFrequency = 0;
    int secondMost = 0;
    vector<string> firstFrequent;
    vector<string> secondFrequent;
    
    
    if (argc > 1)
    {
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                while (myfile.get(tempChar) && isalpha(tempChar))
                {
                    word += (tolower(tempChar));
                }
                if (word != "")
                {
                    ++position;
                    //cout << "exi: " << existsInList(lul, word) << " ";
                    //cout << "Word " << position << ": " << word;
            
                    //word = makeLower(word);
                    if (!existsInList(lul, word))
                    {
                        insertInList(lul, word, position);
                    }
                else
                    {
                        insertInListExisting(lul, word, position);
                    }
                    word = "";
                }
            }
        }
        else
        {
            throw "file didn't open";
        }
        
        myfile.close();
        
        printList(lul);
        
        for (list<TableItem>::iterator it = lul.begin(); it != lul.end();++it)
        {
            if (it->posSize() > firstMost)
            {
                firstMost = it->posSize();
                
        }
        else
        {
            if (it->posSize() > secondMost && it->posSize() < firstMost)
            {
                secondMost = it->posSize();
            }
        }
    }
    
    for (list<TableItem>::iterator it = lul.begin(); it != lul.end(); ++it)
    {
        if (it->posSize() == firstMost)
        {
            ++firstMostFrequency;
        }
    }
    
    for (list<TableItem>::iterator it = lul.begin(); it != lul.end(); ++it)
    {
        if (it->posSize() == firstMost)
        {
            firstFrequent.push_back(it->word());
        }
        else if (it->posSize() == secondMost)
        {
            secondFrequent.push_back(it->word());
        }
    }
    
    if (firstMostFrequency >= 2)
    {
        myOutput << "These most-frequent words appear " << firstMost << " times: ";
        for (int i=0;i<firstFrequent.size()-1;++i)
        {
            myOutput << firstFrequent.at(i) << ", ";
        }
        myOutput << firstFrequent.at(firstFrequent.size()-1);
    }
    else
    {
        myOutput << "This single most-frequent word appears " << firstMost << " times: ";
        myOutput << firstFrequent.at(0) << endl;
        myOutput << "These second most-frequent word(s) appear " << secondMost << " times: ";
        for (int i=0;i<secondFrequent.size()-1;++i)
        {
            myOutput << secondFrequent.at(i) << ", ";
        }
        myOutput << secondFrequent.at(secondFrequent.size()-1);
    }
    }
    else
    {
            cin >> myInput;
            for (int i=x;i < myInput.length();++i)
            {
                tempChar = myInput.at(i);
                if (isalpha(tempChar))
                {
                    word += (tolower(tempChar));
                }
                l = i;
                
            }
            x = l;
            if (word != "")
            {
                ++position;
                //cout << "exi: " << existsInList(lul, word) << " ";
                //cout << "Word " << position << ": " << word;
        
                //word = makeLower(word);
                if (!existsInList(lul, word))
                {
                    insertInList(lul, word, position);
                }
                else
                {
                    insertInListExisting(lul, word, position);
                }
                word = "";
            }
    
    printList(lul);
    
    for (list<TableItem>::iterator it = lul.begin(); it != lul.end();++it)
    {
        if (it->posSize() > firstMost)
        {
            firstMost = it->posSize();
            
        }
        else
        {
            if (it->posSize() > secondMost && it->posSize() < firstMost)
            {
                secondMost = it->posSize();
            }
        }
    }
    
    for (list<TableItem>::iterator it = lul.begin(); it != lul.end(); ++it)
    {
        if (it->posSize() == firstMost)
        {
            ++firstMostFrequency;
        }
    }
    
    for (list<TableItem>::iterator it = lul.begin(); it != lul.end(); ++it)
    {
        if (it->posSize() == firstMost)
        {
            firstFrequent.push_back(it->word());
        }
        else if (it->posSize() == secondMost)
        {
            secondFrequent.push_back(it->word());
        }
    }
    
    if (firstMostFrequency >= 2)
    {
        myOutput << "These most-frequent words appear " << firstMost << " times: ";
        for (int i=0;i<firstFrequent.size()-1;++i)
        {
            myOutput << firstFrequent.at(i) << ", ";
        }
        myOutput << firstFrequent.at(firstFrequent.size()-1);
    }
    else
    {
        myOutput << "This single most-frequent word appears " << firstMost << " times: ";
        myOutput << firstFrequent.at(0) << endl;
        myOutput << "These second most-frequent word(s) appear " << secondMost << " times: ";
        for (int i=0;i<secondFrequent.size()-1;++i)
        {
            myOutput << secondFrequent.at(i) << ", ";
        }
        myOutput << secondFrequent.at(secondFrequent.size()-1);
    }
    }
    
    return 0;
}

/*//-------String to lower Function------------ May not need later
string makeLower(string word)
{
    string tempWord = "";
    for (int i=0;i<word.size()-1;++i)
    {
        tempWord += ""+tolower(word.at(i));
    }
    return tempWord;
}*/

//---------------Check if word exists function---------

bool existsInList(list<TableItem> wordList, string word)
{
    if (!wordList.empty())
    {
        for (list<TableItem>::iterator it = wordList.begin(); it != wordList.end(); ++it)
        {
            if (it->word() == word)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}

//-------------Insert in List function -------------

void insertInList(list<TableItem> &wordList, string word, int pos)
{
    TableItem temp(word);
    if (!wordList.empty())
    {
        for (list<TableItem>::iterator it = wordList.begin(); it != wordList.end(); ++it)
        {
            if (it->word() > word)
            {
                //cout << " Inserted into position "  << pos << endl;
                wordList.insert(it, temp);
                --it;
                it->newPos(pos);
                break;
            }
        }
        
        if (!existsInList(wordList, word)) //previous loop does not check for > last element
        {
            //cout << " Push Backed Special at position" << pos << endl;
            wordList.push_back(temp);
            for (list<TableItem>::iterator it = wordList.begin(); it != wordList.end();++it)
            {
                if (it->word() == word)
                {
                    it->newPos(pos);
                }
            }
        }
    }
    else
    {
        //cout << " Push Backed Empty at position " << pos << endl;
        wordList.push_back(temp);
        for (list<TableItem>::iterator it = wordList.begin(); it != wordList.end();++it)
        {
            if (it->word() == word)
            {
                it->newPos(pos);
            }
        }
    }
}

//-------Function to add position into existing TableItem for relevant word-----

void insertInListExisting(list<TableItem> &wordList, string word, int pos)
{
    //cout << " Inserted into existing with position " << pos << endl;
    for (list<TableItem>::iterator it = wordList.begin(); it != wordList.end(); ++it)
    {
        if (it->word() == word)
        {
            it->newPos(pos);
        }
    }
}

//-------Print List Function (For testing only)---------

void printList(list<TableItem> wordList)
{
    for (list<TableItem>::iterator it = wordList.begin(); it != wordList.end(); ++it)
    {
        myOutput << it->word() << ": ";
        for (int i=0;i<it->posSize()-1;++i)
        {
            myOutput << it->atPos(i) << ", ";
        }
        myOutput << it->atPos(it->posSize()-1) << endl;
        
    }
}




