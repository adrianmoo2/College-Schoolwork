#include <iostream>
#include <cstring>
using namespace std;

void flipString(string &s);

int main() {
   string line;
   cout << "Enter a sentence:" << endl;
   getline(cin, line);
   cout << endl;
   cout << line << endl;
   flipString(line);
   cout << line << endl;

   return 0;
}

void flipString(string &s)
{
    if (s.length() <= 1)
    {
        return;
    }
    else
    {
        string temp = s.substr(1);
        cout << "temp: " << temp << endl;
        flipString(temp);
        s = temp + s.at(0);
    }
}