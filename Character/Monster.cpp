#include "Monster.h"

Monster::Monster(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int armor, const std::string& artwork_path):
                 Character(name, max_hp, power, artwork_path), _armor(armor) {}

unsigned int Monster::getArmor() const {
    return _armor;
}

void Monster::takeDamage(unsigned int amount) {
    if(_is_alive && amount>_armor) {
        if(_hp+_armor>amount)
            _hp=_hp-amount+_armor;
        else {
            _hp=0;
            _is_alive=false;
        }
        for(auto it=_observers.begin(); it!=_observers.end(); ++it)
            (*it)->notify(*this);
    }
}