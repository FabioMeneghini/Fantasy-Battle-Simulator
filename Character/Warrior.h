#ifndef WARRIOR_H
#define WARRIOR_H

class Visitor;
#include "Hero.h"
#include "Visitor.h"

class Warrior: public Hero {
private:
    static unsigned int _warrior_base_power;

public:
    Warrior* clone() const;
    Warrior(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int level, const std::string& artwork_path);
    
    void action(Team& target_team) override;
    void accept(Visitor& visitor) const override;
};

#endif