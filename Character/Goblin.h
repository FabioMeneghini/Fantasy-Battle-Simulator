#ifndef GOBLIN_H
#define GOBLIN_H

class Visitor;
#include "Monster.h"
#include "Visitor.h"

class Goblin: public Monster {
public:
    Goblin* clone() const;
    Goblin(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int armor, const std::string& artwork_path);

    void action(Team& target_team) override;
    void accept(Visitor& visitor) const override;
};

#endif