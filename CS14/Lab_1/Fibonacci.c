#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

int totalAdds = 0;
int totalCalls = 1;
int totalMoves = 0;

void GenRec2(int n, int k, double initial[], double weight[], double back[])
{
    ++totalCalls;
    double sum = 0.0;
    for (int i=k;i>0;--i)
    {
        ++totalAdds;
        sum += back[(k-i+static_cast<int>(initial[0]))%k]*weight[k-i];
        cout << back[(k-i+static_cast<int>(initial[0]))%k] << " * " << weight[k-i] << endl;
    }
    
    ++totalMoves;
    back[static_cast<int>(initial[0])%k] = sum;
    cout << sum << endl;

    --n;
        
    if (n<k)
    {
        ++totalMoves;
        back[k-1] = sum;
        return;
    }
        
    initial[0] = initial[0] + 1.0;
        
    GenRec2(n, k, initial, weight, back);
    
}

double GenLoop(int n, int k, double initial[], double weight[])
{
    ++totalCalls;
    if (n<k)
    {
        return initial[n];
    }
    
    double array[n+1];
    
    for (int i=0;i<k;++i)
    {
        array[i] = initial[i];
        //cout << "array[" << i << "]: " << array[i] << endl;
    }
    
    for (int i = k;i<=n;++i)
    {
        double sum = 0.0;
        for (int count=k;count>0;--count)
        {
            ++totalAdds;
            array[i]+=array[i-count]*weight[k-count];   
        }
        ++totalMoves;
        //cout << "array[" << i << "]: " << array[i] << endl;
    }
    
    return array[n];
}

double GenRec(int n, int k, double initial[], double weight[])
{
    ++totalCalls;
    if (n<k)
    {
        return initial[n];
    }
    
    double back[k];
    for (int i=0;i<k;++i)
    {
        back[i] = initial[i];
    }
    
    initial[0] = 0.0;
    
    GenRec2(n, k, initial, weight, back);
    
    return back[k-1];
}

void FibRec2 (int n, double &oneBack, double &twoBack)
{
    ++totalCalls;
    if (n == 1 || n == 0)
    {
        return;
    }
    else
    {
            double sum = oneBack + twoBack;
            ++totalAdds;
            twoBack = oneBack;
            oneBack = sum;
            ++totalMoves;
            FibRec2(n-1, oneBack, twoBack);
    }
}

int FibRec(int n)
{
    ++totalCalls;
     if (n == 1 || n == 0)
    {
        return n;
    }
    else
    {
        ++totalAdds;
        return FibRec(n-1)+FibRec(n-2);
    }
}

int FibRecFast(int n)
{
    ++totalCalls;
    double firstBack = 1.0;
    double secondBack = 0.0;
    if (n == 1 || n == 0)
    {
        return n;
    }
    else
    {
        FibRec2(n, firstBack, secondBack);
    }
    return firstBack;
}

int FibLoop(int n)
{
    ++totalCalls;
    int array[n+1];
    
    array[0] = 0;
    array[1] = 1;
    
    if (n==1 || n==0)
    {
        return n;
    }
    
    for (int i=2;i<n+1;++i)
    {
        array[i] = array[i-1] + array[i-2];
        ++totalAdds;
    }
    
    return array[n];
}

class Series {
    int k;
    vector<double> weights;
    vector<double> values;
    int biggest_known;
  public:
    Series();
    void set_k();
    void set_weights();
    void set_weights(double w[]);
    void set_initial();
    void set_initial(double i[]);
    double get_val(int n);
};

Series::Series()
{
    k = 3;
    biggest_known = -1;
}

void Series::set_k()
{
    cout << "Enter a number between 0-9 for value k: ";
    cin >> k;
    biggest_known = k-1;
}

void Series::set_weights()
{
    weights.resize(k);
    for (int i=0;i<k;++i)
    {
        double x = 0.0;
        cout << "Input a weight: ";
        cin >> x;
        weights.at(i) = x;
    }
    
}

void Series::set_initial()
{
    values.resize(k);
    for (int i=0;i<k;++i)
    {
        double x = 0.0;
        cout << "Input a value: ";
        cin >> x;
        values.at(i) = x;
    }
}

double Series::get_val(int n)
{
    ++totalCalls;
    if (n>biggest_known)
    {
        if (n < k)
        {
            return values.at(n);
        }
        biggest_known = n;
        
        for (int i = k;i<=n;++i)
        {
            double sum = 0.0;
            for (int j=0;j<k;++j)
            {
                //cout << values.at(i-k+j) << " * " << weights.at(j) << endl;
                ++totalAdds;
                sum += values.at(i-k+j)*weights.at(j);   
            }
            ++totalMoves;
            values.push_back(sum);
        }
    
        return values.at(n);
        
    }
    else
    {
        return values.at(n);
    }
    
}

int main(int argc, char* argv[])
{
    ofstream myfile;
    
    if (argc <= 1)
    {

    myfile.open("test1.csv");
    
    for (int n = 0;n<=30;++n)
    {
        myfile << n << ", ";
        FibLoop(n);
        myfile << totalAdds << ", " << totalCalls << ", ";
        
        totalAdds = 0;
        totalMoves = 0;
        totalCalls = 1;
        
        FibRec(n);
        
        myfile << totalAdds << ", " << totalCalls << endl;
        
        totalMoves = 0;
        totalAdds = 0;
        totalCalls = 1;
    }
    
    myfile.close();
    myfile.open("test2.csv");    
  
    for (int n = 0;n<=30;++n)
    {
        myfile << n << ", ";
        FibLoop(n);
        myfile << totalAdds << ", " << totalCalls << ", " << totalMoves << ", ";
        
        totalAdds = 0;
        totalMoves = 0;
        totalCalls = 1;
        
        FibRecFast(n);
        
        myfile << totalAdds << ", " << totalCalls << totalMoves << endl;
        
        totalMoves = 0;
        totalAdds = 0;
        totalCalls = 1;
    }
    
    myfile.close();
    myfile.open("test3.csv");
    
    double initial[2] = {0.0, 1.0};
    double weights[2] = {1.0, 1.0};
    int k = 2;
    
    for (int n = 0;n<=30;++n)
    {
        myfile << n << ", ";
        GenLoop(n, k, initial, weights);
        myfile << totalAdds << ", " << totalCalls << ", " << totalMoves << ", ";
        
        totalAdds = 0;
        totalMoves = 0;
        totalCalls = 1;
        
        FibRecFast(n);
        
        myfile << totalAdds << ", " << totalCalls << ", " << totalMoves << endl;
        
        totalMoves = 0;
        totalAdds = 0;
        totalCalls = 1;
    }
    
    myfile.close();
    myfile.open("test4.csv");
    
    double initial2[3] = {2, -3, 1};
    double weights2[3] = {1.1, -0.15, -0.9};
    k = 3;
    
    myfile << k << ", ";
    for (int i=0;i<k;++i)
    {
        myfile << initial2[i] << ", ";
    }
    
    for (int i=0;i<k;++i)
    {
        myfile << weights2[i] << ", ";  
    }
    
    myfile << endl;
    
    
    for (int i=0;i<20;++i)
    {
        myfile << i << ": " << GenLoop(i, k, initial2, weights2) << endl;
    }
    myfile << "20: ";
    myfile << GenLoop(20, k, initial2, weights2) << endl << endl;
    
    double initial3[4] = {1.0, 2.0, 3.0, 4.0};
    double weights3[4] = {0.5, -1.0, 1.5, -2.0};
    k=4;
    
    myfile << k << ", ";
    for (int i=0;i<k;++i)
    {
        myfile << initial3[i] << ", ";
    }
    
    for (int i=0;i<k;++i)
    {
        myfile << weights3[i] << ", ";  
    }
    myfile << weights[k-1];
    
    myfile << endl;
    
    for (int i=0;i<20;++i)
    {
        myfile << i << ": " << GenLoop(i, k, initial2, weights2) << endl;
    }
    myfile << "20: ";
    myfile << GenLoop(20, k, initial2, weights2) << endl << endl;
    
    myfile.close();
    myfile.open("test5.csv");
    
    
    Series sample;
    sample.set_k();
    sample.set_initial();
    sample.set_weights();
    
    
    for (int i=0;i<=3;++i)
    {
        totalMoves = 0;
        totalAdds = 0;
        totalCalls = 1;
        sample.get_val(i);
        myfile << i << ", " << totalAdds << ", " << totalCalls << ", " << totalMoves << endl;
    }
    
    }
    else
    {
        string filename = argv[1];
        string period = ".";
        string out = ".out";
        
        ifstream myfile2;
        myfile2.open(filename.c_str());
        
        
        int startPos = filename.find(period);
        if (startPos == string::npos)
        {
            return 0;
        }
        filename.replace(startPos, filename.length(), out);
        
        myfile2.close();
        
        ofstream myfile3;
        myfile3.open(filename.c_str());
        
            
        }
    
    
    /*
    myfile << "value of n: " << n << endl;
    
    cout << "FibLoop of 5: " << FibLoop(n) << endl;
    
    myfile << "totalAdds after FibLoop: " << totalAdds << endl;
    myfile << "totalCalls after FibLoop: " << totalCalls << endl;
    myfile << "totalMoves after FibLoop: " << totalMoves << endl << endl;
    
    
    n = 5;
    totalAdds = 0;
    totalCalls = 1;
    totalMoves = 0;
    
    cout << "FibRec of 5: " << FibRec(n) << endl;
    
    myfile << "totalAdds after FibRec: " << totalAdds << endl;
    myfile << "totalCalls after FibRec: " << totalCalls << endl;
    myfile << "totalMoves after FibRec: " << totalMoves << endl << endl;
    
    int n = 3;
    int k = 3;
    double initial[3] = {2, -3, 1};
    double weight[3] = {1.1, -0.15, -0.9};
    totalAdds = 0;
    totalCalls = 1;
    totalMoves = 0;
    
    cout << "GenLoop of 5: " << GenLoop(n, k , initial, weight) << endl;/*
    
    
    /*n = 15;
    k = 2;
    
    double initial2[] = {0.0, 1.0};
    double weight2[] = {1.0, 1.0};
    totalAdds = 0;
    totalCalls = 1;
    totalMoves = 0;
    
    cout << "GenRec of 5: " << GenRec(n, k, initial2, weight2) << endl;
    
    myfile << "totalAdds after GenRec: " << totalAdds << endl;
    myfile << "totalCalls after GenRec: " << totalCalls << endl;
    myfile << "totalMoves after GenRec: " << totalMoves << endl;
    
    ifstream in("I_hate_this_lab.txt");
    
    Series x;
    x.set_k();
    x.set_initial(ifstream in);
    x.set_weights(ifstream in);
    
    myfile.close();*/
    
    return 0;
}
