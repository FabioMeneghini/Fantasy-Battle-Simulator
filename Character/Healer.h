#ifndef HEALER_H
#define HEALER_H

class Visitor;
#include "Hero.h"
#include "Visitor.h"

class Healer: public Hero {
private:
    static unsigned int _healer_base_power;

public:
    Healer* clone() const;
    Healer(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int level, const std::string& artwork_path);

    void action(Team& target_team) override;
    void accept(Visitor& visitor) const override;
};

#endif