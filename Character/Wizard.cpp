#include "Wizard.h"
#include "Visitor.h"

unsigned int Wizard::_wizard_base_power=4;

Wizard* Wizard::clone() const {
    return new Wizard(*this);
}

Wizard::Wizard(const std::string& name, unsigned int max_hp,  unsigned int power, unsigned int level, const std::string& artwork_path):
               Hero(name, max_hp, power, level, artwork_path) {}

void Wizard::action(Team& target_team) { //colpisce tutti i membri del team target_team
    unsigned int damage;
    Character* tmp;
    for(Team::Iterator it=target_team.begin(); it!=target_team.end() && (*it)->isAlive(); ++it) {
        tmp=*it;
        damage=((getLevel()+_wizard_base_power)*getPower()*(rand()%31+40))/100;
        hit(target_team, *it, damage);
        if(!(tmp->isAlive())) //per motivi di semplicità, quando viene sconfitto un Character si esce dalla funzione
            return;
    }
}

void Wizard::accept(Visitor& visitor) const {
    visitor.visit(*this);
}