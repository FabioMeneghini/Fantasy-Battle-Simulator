#ifndef MONSTER_H
#define MONSTER_H

class Character;
#include "Character.h"

class Monster: public Character {
private:
    unsigned int _armor; //indica la resistenza ai danni
protected:
    Monster(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int armor, const std::string& artwork_path);

public:
    unsigned int getArmor() const;
    void takeDamage(unsigned int amount);
};

#endif