#include "Elf.h"

Elf::Elf(const string &name, double health, double attackStrength, string family)
{
    this->name = name;
    this->type = ELF;
    this->health = health;
    this->attackStrength = attackStrength;
    this->family = family;
}

void Elf::attack(Character &opponent)
{
    if (isAlive())
    {
        if (opponent.getType() == ELF)
        {
            Elf &opp = dynamic_cast<Elf &>(opponent);
            if (!(family == opp.getFamily()))
            {
                cout << "Elf " << name << " attacks " << opp.getName() << " --- TWANG!!!" << endl;
                cout << opp.getName() << " takes " << (health/100.0)*attackStrength << " damage." << endl;
                opponent.setHealth(opponent.getHealth() - ((health/100.0)*attackStrength));
            }
            else
            {
                cout << "Elf " << name << " does not attack Elf " << opp.getName() << "." << endl;
                cout << "They are both members of the " << family << " family." << endl;
            }
        }
        else
        {
                cout << "Elf " << name << " attacks " << opponent.getName() << " --- TWANG!!!" << endl;
                cout << opponent.getName() << " takes " << (health/100.0)*attackStrength << " damage." << endl;
                opponent.setHealth(opponent.getHealth() - ((health/100.0)*attackStrength));
        }
    }
}

string Elf::getFamily() const
{
    return family;
}

