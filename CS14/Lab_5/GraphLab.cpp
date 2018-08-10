#include <vector>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <utility>
#include <limits>
#include <queue>
#include <math.h>
#include <cmath>
#include <iostream>
using namespace std;   

struct room {
    vector<string> longStory;
    string shortStory;
    vector<int> Next;
    int Edge;
};

struct Edge {
    int Start;
    int End;
    double W;
};

vector<double> shortestpaths(vector< vector< pair<int, double> > > adj, int v);
int findNum(string s);
int startingRoomNum(string &s);
int endingRoomNum(string &s);
int maximumWeight(string &s, vector<int> w);

// now store target node and weight
vector<double> shortestpaths(vector< vector< pair<int, double> > > adj, int v) {
    vector<double> ret(adj.size(),-1);
    
    priority_queue< pair<int,double> > q;
    q.push(make_pair(v,0));
    while(!q.empty()) {
        pair<int,double> s = q.top();
        q.pop();
        if (ret[s.first]==-1) {
            ret[s.first] = s.second;
            for(pair<int, double> j : adj[s.first]) {
                q.push(make_pair(j.first,s.second+j.second));
            }
        }
    }
    return ret;
}


int startingRoomNum(string &s)
{
    int commaStop = 0;
    int startingNum = 0;
    string temp = "";
    
    for (unsigned int i=0;i<s.length();++i)
    {
        if (s.at(i) == ',')
        {
            commaStop = i;
            break;
        }
    }
    
    temp = s.substr(0, commaStop);
    istringstream buffer(temp);
    buffer >> startingNum;
    
    s = s.substr(commaStop+1, s.length()-commaStop);
    
    return startingNum;
}

int endingRoomNum(string &s)
{
    int commaStop = 0;
    int endingNum = 0;
    string temp = "";
    
    for (unsigned int i=0;i<s.length();++i) {
        if (s.at(i) == ',')
        {
            commaStop = i;
            break;
        }
    }
    
    temp = s.substr(0, commaStop);
    istringstream buffer(temp);
    buffer >> endingNum;
    
    s = s.substr(commaStop+1, s.length()-commaStop);
    
    return endingNum;
}

int maximumWeight(string &s, vector<int> w)
{
    int commaStop = -1;
    int tempWeight = -1;
    int maxWeight = -1;
    string temp = "";
    string fillerString = "";
    //cout << "s: " << s << endl;
    
    if (s.empty())
    {
        //cout << "w: ";
        for (int i=0;i<w.size();++i) {
            //cout << w.at(i) << ", ";
            if (w.at(i) > maxWeight) {
               maxWeight = w.at(i);
            }
        }
        return maxWeight;
    } else {
        for (unsigned int i=0;i<s.length();++i)
        {
            if (s.at(i) == ',')
            {
                commaStop = i;
                break;
            }
        }
        if (commaStop == -1) {
            temp = s.substr(0, s.length());
            istringstream buffer(temp);
            buffer >> tempWeight;
            w.push_back(tempWeight);
            
            return maximumWeight(fillerString, w);
        } else {
            temp = s.substr(0, commaStop);
            istringstream buffer(temp);
            buffer >> tempWeight;
            w.push_back(tempWeight);
            
            s = s.substr(commaStop+1, s.length()-commaStop);
            return maximumWeight(s, w);
        }
    }
    
    
}

int findNum(string s)
{
    
    int commaStop = 0;
    int finalNum = 0;
    string temp = "";
    
    for (unsigned int i=0;i<s.length();++i)
    {
        if (s.at(i) == ',')
        {
            commaStop = i;
            break;
        }
    }
    
    temp = s.substr(0, commaStop);
    istringstream buffer(temp);
    buffer >> finalNum;
    return finalNum;
}

int main()
{
    string dummyString = "dummy";
    int dummyInt = -500;
    vector<int> dummyIntVector;
    vector<string> dummyStringVector;
    
    room dummyRoom;
    
    dummyRoom.longStory = dummyStringVector;
    dummyRoom.shortStory = dummyString;
    dummyRoom.Next = dummyIntVector;
    dummyRoom.Edge = dummyInt;
    
    vector<int> vertices;
    vector<room> roomVector;
    vector<Edge> edgeVector;
    
    roomVector.push_back(dummyRoom);
    
    
    //-------------------------Start reading in the data from file code-------------
    
    string line = "";
    string inputChecker = "";
    int roomNum = 0;
    int roomNumLength = 0;
    ifstream infile("Text.txt");
    
    while (getline(infile, line) && line != "4")
    {
        if (line != "-1,END" && line != "-1")
        {
            roomNum = findNum(line);
            stringstream ss;
            ss << roomNum;
            roomNumLength = ss.str().length();
        }
        
        if (inputChecker == "first" && line != "-1,END" && line != "2") {
            
            if (roomNum > roomVector.size() - 1) {
                room tempRoom;
                tempRoom.longStory.push_back(line.substr(roomNumLength+1, line.length()-roomNumLength));
                roomVector.push_back(tempRoom);
            }
            else {
                roomVector.at(roomNum).longStory.push_back(line.substr(roomNumLength+1, line.length()-roomNumLength));
            }
        } else if (inputChecker == "second" && line != "-1" && line != "3") {
            roomVector.at(roomNum).shortStory = line.substr(roomNumLength+1, line.length()-roomNumLength);
        } else if (inputChecker == "third" && line != "-1" && line != "4") {
            Edge tempEdge;
            vector<int> dummyVector;
            string tempLine = line;
            
            int startingRoom = startingRoomNum(tempLine);
            int endingRoom = endingRoomNum(tempLine);
            int weight = maximumWeight(tempLine, dummyVector);
            
            if (endingRoom < 300) {
            
                roomVector.at(startingRoom).Next.push_back(endingRoom);
                
                tempEdge.Start = startingRoom;
                tempEdge.End = endingRoom;
                tempEdge.W = weight;
                
                edgeVector.push_back(tempEdge);
            } else if (endingRoom == 303)
            {
                if (startingRoom == 117)
                {
                    tempEdge.Start = startingRoom;
                    tempEdge.End = 122;
                    tempEdge.W = 100;
                    
                    roomVector.at(startingRoom).Next.push_back(tempEdge.End);
                    edgeVector.push_back(tempEdge);
                } else if (startingRoom == 122) {
                    tempEdge.Start = startingRoom;
                    tempEdge.End = 117;
                    tempEdge.W = 100;
                    
                    roomVector.at(startingRoom).Next.push_back(tempEdge.End);
                    edgeVector.push_back(tempEdge);
                }
            }
            
        }
        
        if (line == "1") {
            inputChecker = "first";
        }
        else if (line == "2") {
            inputChecker = "second";
        }
        else if (line == "3") {
            inputChecker = "third";
        }
        
    }
    
    //---------------------Prompt the user to enter three vertices--------------------
    int userVertexInput = -500;
    string userInput = "";
    
    while (userInput != "no") {
    cout << "Please enter your first vertex between 1 and " << roomVector.size()-1 << ": ";
    cin >> userVertexInput;
        if (cin.fail() || userVertexInput > roomVector.size()-1) {
            cout << "We ran into an error. Your vertex is not an integer, or is greater than the maximum number of rooms. Please restart the program and try again. ";
            return 0;
        }
        else {
            cout << "Your first vertex is: " << userVertexInput << endl;
            cout << "With a longstory of ------ ";
            for (int i=0;i<roomVector.at(userVertexInput).longStory.size();++i)
            {
                cout << roomVector.at(userVertexInput).longStory.at(i) << " ";
            }
        }
        cout << endl;
        cout << "Would you like to select a new vertex? (yes/no) - CASE SENSITIVE: ";
        cin >> userInput;
        cout << endl;
    }
    
    userInput = "";
    vertices.push_back(userVertexInput);
    
    while (userInput != "no") {
        cout << "Please enter your second vertex between 1 and " << roomVector.size()-1 << " excluding " << vertices.at(0) << ": ";
        cin >> userVertexInput;
        
        if (cin.fail() || userVertexInput > roomVector.size()-1) {
            cout << "We ran into an error. Your vertex is not an integer, or is greater than the maximum number of rooms. Please restart the program and try again. ";
        }
        else if (userVertexInput == vertices.at(0)){
                cout << "Your vertices are not distinct. Please restart the program and try again. ";
                return 0;
        }
        else {
            cout << "Your second vertex is: " << userVertexInput << endl;
            cout << "With a longstory of ------ ";
            for (int i=0;i<roomVector.at(userVertexInput).longStory.size();++i)
            {
                cout << roomVector.at(userVertexInput).longStory.at(i) << " ";
            }
        }
        cout << endl;
        cout << "Would you like to select a new vertex? (yes/no) - CASE SENSITIVE: ";
        cin >> userInput;
        cout << endl;
    }
    
    vertices.push_back(userVertexInput);
    userInput = "";
    
    while (userInput != "no") {
        cout << "Please enter your third vertex between 1 and " << roomVector.size()-1 << " excluding " << vertices.at(0) << " and " << vertices.at(1) << ": ";
        cin >> userVertexInput;
        
        if (cin.fail() || userVertexInput > roomVector.size()-1){
            cout << "We ran into an error. Your vertex is not an integer, or is greater than the maximum number of rooms. Please restart the program and try again. ";
            return 0;
        }
        else if (userVertexInput == vertices.at(0) || userVertexInput == vertices.at(1)) {
            cout << "Your vertices are not distinct. Please restart the program and try again. ";
            return 0;
        }
        else {
            cout << "Your third vertex is: " << userVertexInput << endl;
            cout << "With a longstory of ------ ";
            for (int i=0;i<roomVector.at(userVertexInput).longStory.size();++i)
            {
                cout << roomVector.at(userVertexInput).longStory.at(i) << " ";
            }
        }
        cout << endl;
        cout << "Would you like to select a new vertex? (yes/no) - CASE SENSITIVE: ";
        cin >> userInput;
        cout << endl;
    }
    
    //-------------------------End of vertices input code------------------
    
    vector< vector< pair<int, double> > > howToPopulate;
    vector< vector< pair<int, double> > > howToPopulate2;
    vector< vector< pair<int, double> > > howToPopulate3;
    
    for (int i=0;i<roomVector.at(vertices.at(0)).Next.size();++i)
    {
        vector<pair<int, double>> tempVec;
        for (int j=0;j<edgeVector.size();++j)
        {
            if (roomVector.at(vertices.at(0)).Next.at(i) == edgeVector.at(j).End && vertices.at(0) == edgeVector.at(j).Start) 
            {
                pair<int, double> tempPair;
                tempPair.first = edgeVector.at(j).End;
                tempPair.second = edgeVector.at(j).W;
                tempVec.push_back(tempPair);
            }
        }
        howToPopulate.push_back(tempVec);
    }
    
    for (int i=0;i<roomVector.at(vertices.at(1)).Next.size();++i)
    {
        vector<pair<int, double>> tempVec;
        for (int j=0;j<edgeVector.size();++j)
        {
            if (roomVector.at(vertices.at(1)).Next.at(i) == edgeVector.at(j).End && vertices.at(1) == edgeVector.at(j).Start) 
            {
                pair<int, double> tempPair;
                tempPair.first = edgeVector.at(j).End;
                tempPair.second = edgeVector.at(j).W;
                tempVec.push_back(tempPair);
            }
        }
        howToPopulate2.push_back(tempVec);
    }
    
    for (int i=0;i<roomVector.at(vertices.at(2)).Next.size();++i)
    {
        vector<pair<int, double>> tempVec;
        for (int j=0;j<edgeVector.size();++j)
        {
            if (roomVector.at(vertices.at(2)).Next.at(i) == edgeVector.at(j).End && vertices.at(2) == edgeVector.at(j).Start) 
            {
                pair<int, double> tempPair;
                tempPair.first = edgeVector.at(j).End;
                tempPair.second = edgeVector.at(j).W;
                tempVec.push_back(tempPair);
            }
        }
        howToPopulate3.push_back(tempVec);
    }
    
    vector<double> shortestPaths1 = shortestpaths(howToPopulate, vertices.at(0));
    vector<double> shortestPaths2 = shortestpaths(howToPopulate, vertices.at(1));
    vector<double> shortestPaths3 = shortestpaths(howToPopulate, vertices.at(2));
    

    return 0;
}