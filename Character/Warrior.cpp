#include "Warrior.h"

unsigned int Warrior::_warrior_base_power=8;

Warrior* Warrior::clone() const {
    return new Warrior(*this);
}

Warrior::Warrior(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int level, const std::string& artwork_path):
                 Hero(name, max_hp, power, level, artwork_path) {}

void Warrior::action(Team& target_team) { //attacca il primo personaggio del team target_team
    unsigned int damage=((getLevel()+_warrior_base_power)*getPower()*(rand()%21+80))/100;
    hit(target_team, target_team.search(0), damage);
}

void Warrior::accept(Visitor& visitor) const {
    visitor.visit(*this);
}