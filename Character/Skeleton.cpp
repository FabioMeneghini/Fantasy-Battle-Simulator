#include "Skeleton.h"
#include "Visitor.h"

Skeleton* Skeleton::clone() const {
    return new Skeleton(*this);
}

Skeleton::Skeleton(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int armor, const std::string& artwork_path):
               Monster(name, max_hp, power, armor, artwork_path) {}

void Skeleton::action(Team& target_team) { //colpisce tutti i membri del team target_team
    unsigned int damage;
    Character* tmp;
    for(Team::Iterator it=target_team.begin(); it!=target_team.end() && (*it)->isAlive(); ++it) {
        tmp=*it;
        damage=getPower()*(rand()%11+90)/4;
        hit(target_team, *it, damage);
        if(!(tmp->isAlive())) //per motivi di semplicità, quando viene sconfitto un Character si esce dalla funzione
            return;
    }
}

void Skeleton::accept(Visitor& visitor) const {
    visitor.visit(*this);
}