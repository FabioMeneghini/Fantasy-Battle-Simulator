#include "Healer.h"
#include "Monster.h"
#include "Visitor.h"

unsigned int Healer::_healer_base_power=4;

Healer* Healer::clone() const {
    return new Healer(*this);
}

Healer::Healer(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int level, const std::string& artwork_path):
               Hero(name, max_hp, power, level, artwork_path) {}

void Healer::action(Team& target_team) { //cura tutti i membri del team target_team che non sono sottotipi di Monster
    unsigned int amount;
    for(Team::Iterator it=target_team.begin(); it!=target_team.end(); ++it) {
        if(!dynamic_cast<Monster*>(*it)) {
            amount=((getLevel()+_healer_base_power)*getPower()*(rand()%21+30))/100;
            (*it)->heal(amount);
        }
    }
}

void Healer::accept(Visitor& visitor) const {
    visitor.visit(*this);
}