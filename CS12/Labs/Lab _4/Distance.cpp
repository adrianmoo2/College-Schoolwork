#include "Distance.h"

Distance::Distance()
{
    feet = 0;
    inches = 0.0;
}

Distance::Distance(unsigned ft, double in)
{
    feet = ft;
    inches = in;
    init();
}

Distance::Distance(double in)
{
    feet = 0;
    inches = in;
    init();
}

unsigned Distance::getFeet() const
{ 
    return feet;
}

double Distance::getInches() const
{
    return inches;
}

double Distance::distanceInInches() const
{
    double result = 0.0;
    if (feet > 0)
    {
        result += (feet * 12.0);
    }
    result += inches;
    
    return result;
}

double Distance::distanceInFeet() const
{
    double result = 0.0;
    result += feet;
    result += (inches/12.0);
    
    return result;
}

double Distance::distanceInMeters() const
{
    double result = 0.0;
    result += (feet*(12.0*0.0254));
    result += (inches*0.0254);
    
    return result;
}

const Distance Distance::operator+(const Distance& rhs) const
{
    Distance temp;
    
    temp.feet = (feet + rhs.feet);
    temp.inches = (inches + rhs.inches);
    
    if (temp.inches >= 12)
    {
        temp.feet += static_cast<int>(temp.inches)/12;
        temp.inches = fmod(temp.inches, 12.0);
    }
    
    return temp;
}

const Distance Distance::operator-(const Distance& rhs) const
{
    Distance temp;
    Distance temp2;
    
    temp.inches = (inches + (feet*12));
    
    temp2.inches = (rhs.inches + (rhs.feet*12));
    
    temp.inches = (temp.inches - temp2.inches);
    
    if (temp.inches < 0)
    {
        temp.inches = fabs(temp.inches);
    }
    if (temp.inches >= 12)
    {
        temp.feet = static_cast<int>(temp.inches)/12;
        temp.inches = fmod(temp.inches, 12.0);
    }
    
    
    return temp;
}

ostream& operator<<(ostream &out, const Distance &rhs)
{
    out << rhs.feet << "' " << rhs.inches <<"\"";
    return out;
}

void Distance::init()
{
    if (inches < 0)
    {
        inches = fabs(inches);
    }
    if (inches >= 12)
    {
        feet += static_cast<int>(inches)/12;
        inches = fmod(inches, 12.0);
    }
}