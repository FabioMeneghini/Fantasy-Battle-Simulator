#include "Goblin.h"
#include "Visitor.h"

Goblin* Goblin::clone() const {
    return new Goblin(*this);
}

Goblin::Goblin(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int armor, const std::string& artwork_path):
               Monster(name, max_hp, power, armor, artwork_path) {}

void Goblin::action(Team& target_team) { //colpisce il primo membro del team target_team
    unsigned int damage=getPower()*(rand()%11+90)/4;
    hit(target_team, target_team.search(0), damage);
}

void Goblin::accept(Visitor& visitor) const {
    visitor.visit(*this);
}