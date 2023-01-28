#ifndef SKELETON_H
#define SKELETON_H

class Visitor;
#include "Monster.h"
#include "Visitor.h"

class Skeleton: public Monster {
public:
    Skeleton* clone() const;
    Skeleton(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int armor, const std::string& artwork_path);

    void action(Team& target_team) override;
    void accept(Visitor& visitor) const;
};

#endif