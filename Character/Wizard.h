#ifndef WIZARD_H
#define WIZARD_H

class Visitor;
#include "Hero.h"

class Wizard: public Hero {
private:
    static unsigned int _wizard_base_power;

public:
    Wizard* clone() const;
    Wizard(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int level, const std::string& artwork_path);

    void action(Team& target_team) override;
    void accept(Visitor& visitor) const;
};

#endif