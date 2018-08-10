#include "Wizard.h"

Wizard::Wizard(const string &name, double health, double attackStrength, int rank)
{
    this->name = name;
    this->type = WIZARD;
    this->health = health;
    this->attackStrength = attackStrength;
    this->rank = rank;
}

void Wizard::attack(Character &opponent)
{
    if (isAlive())
    {
        if (opponent.getType() == WIZARD)
        {
            Wizard &opp = dynamic_cast<Wizard &>(opponent);
            double ratio = (static_cast<double>(rank))/opp.getRank();
            
            cout << "Wizard " << name << " attacks " << opp.getName() << " --- POOF!!!" << endl;
            cout << opp.getName() << " takes " << ratio*attackStrength << " damage." << endl;
            opponent.setHealth(opponent.getHealth() - ratio*attackStrength);
        }
        else
        {
            cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!!" << endl;
            cout << opponent.getName() << " takes " << attackStrength << " damage." << endl;
            opponent.setHealth(opponent.getHealth() - (attackStrength));
        }
    }
}

int Wizard::getRank() const
{
    return rank;
}

