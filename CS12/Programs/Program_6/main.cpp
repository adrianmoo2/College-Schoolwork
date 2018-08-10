#include <iostream>
using namespace std;

/* Returns true if a solution was found and false if there is no solution.
   x and y will contain a solution if a solution was found. 
   This function will NOT output anything.
*/
bool diophantine(int a, int b, int c, int &x, int &y);

int gcd(int inNum1, int inNum2) {
	if(inNum2 == 0)
	{
	        return inNum1;
	}
	else
	{
		return gcd(inNum2, inNum1 % inNum2);
	}
}

bool diophantine(int a, int b, int c, int &x, int &y)
{
    if (c % gcd(a, b) != 0)
    {
        return false;
    }
    else if (a % b == 0)
    {
        x = 0;
        y = (c/b); 
        
        return true;
    }
    else
    {
        int q = (a/b);
        int r = (a%b);
        
        int u;
        int v;
        
        diophantine(b, r, c, u, v);
        
        x = v;
        y = u - q*x;
    }
    return true;
}

int main() {

    int a, b, c, x, y;

    cout << "Enter a b c" << endl;
    cin >> a >> b >> c;
    cout << endl;

    cout << "Result: ";
    if (diophantine(a, b, c, x, y)) {
        cout << x << " " << y << endl;
    } else {
        cout << "No solution!" << endl;
    }

    return 0;
}