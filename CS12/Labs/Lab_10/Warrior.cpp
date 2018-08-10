#include "Warrior.h"

Warrior::Warrior(const string &name, double health, double attackStrength, string allegiance)
{
    this->name = name;
    this->type = WARRIOR;
    this->health = health;
    this->attackStrength = attackStrength;
    this->allegiance = allegiance;
}

void Warrior::attack(Character &opponent)
{
    if (isAlive())
    {
        if (opponent.getType() == WARRIOR)
        {
            Warrior &opp = dynamic_cast<Warrior &>(opponent);
            if (!(allegiance == opp.getAllegiance()))
            {
                cout << "Warrior " << name << " attacks " << opp.getName() << " --- SLASH!!!" << endl;
                cout << opp.getName() << " takes " << (health/100.0)*attackStrength << " damage." << endl;
                opponent.setHealth(opponent.getHealth() - ((health/100.0)*attackStrength));
            }
            else
            {
                cout << "Warrior " << name << " does not attack Warrior " << opp.getName() << "." << endl;
                cout << "They share an allegiance with " << allegiance << "." << endl;
            }
        }
        else
        {
            cout << "Warrior " << name << " attacks " << opponent.getName() << " --- SLASH!!!" << endl;
            cout << opponent.getName() << " takes " << (health/100.0)*attackStrength << " damage." << endl;
            opponent.setHealth(opponent.getHealth() - ((health/100.0)*attackStrength));
        }
    }
}

string Warrior::getAllegiance() const
{
    return allegiance;
}
