#include "Character.h"
#include <string>

Character::Character(const std::string& name, unsigned int max_hp, unsigned int power, const std::string& artwork_path):
                     _name(name), _max_hp(max_hp), _power(power), _artwork_path(artwork_path), _hp(max_hp), _is_alive(true) {}

const std::string& Character::getName() const {
    return _name;
}

unsigned int Character::getMaxHp() const {
    return _max_hp;
}

unsigned int Character::getHp() const {
    return _hp;
}

unsigned int Character::getPower() const {
    return _power;
}

const std::string& Character::getArtworkPath() const {
    return _artwork_path;
}

bool Character::isAlive() const {
    return _is_alive;
}

void Character::heal(unsigned int amount) {
    if(_is_alive)
        _hp=_hp+amount>=_max_hp ? _max_hp : _hp+amount;
    for(auto it=_observers.begin(); it!=_observers.end(); ++it)
        (*it)->notify(*this);
}

void Character::hit(Team& target_team, Character*& target, unsigned int amount) const { //PRE: target è contenuto in target_team
    if(target->isAlive()) {
        target->takeDamage(amount);
        if(!(target->isAlive())) {
            target_team.moveBack(target);
            target_team.setAliveCount(target_team.getAliveCount()-1);
        }
    }
}

void Character::registerObserver(CharacterObserver* obs) {
    _observers.push_back(obs);
}

void Character::removeObserver(CharacterObserver* obs) {
    for(auto it=_observers.begin(); it!=_observers.end(); ++it)
        if(obs==*it) {
            _observers.erase(it);
            return;
        }
}
