#include "Hero.h"

Hero::Hero(const std::string& name, unsigned int max_hp, unsigned int power, unsigned int level, const std::string& artwork_path):
           Character(name, max_hp, power, artwork_path), _level(level) {}

void Hero::takeDamage(unsigned int amount) {
    if(_is_alive) {
        if(_hp>amount)
            _hp-=amount;
        else {
            _hp=0;
            _is_alive=false;
        }
        //if(_observers.size()>0)
        for(auto it=_observers.begin(); it!=_observers.end(); ++it)
            (*it)->notify(*this);
    }
}

unsigned int Hero::getLevel() const {
    return _level;
}