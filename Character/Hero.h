#ifndef HERO_H
#define HERO_H

class Character;
#include "Character.h"

class Hero: public Character {
private:
    unsigned int _level;
protected:
    Hero(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int level, const std::string& artwork_path);

public:
    unsigned int getLevel() const;
    void takeDamage(unsigned int amount);
};

#endif