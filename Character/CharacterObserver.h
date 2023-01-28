#ifndef CHARACTER_OBSERVER_H
#define CHARACTER_OBSERVER_H

#include "Character.h"
class Character;

class CharacterObserver {
public:
    virtual ~CharacterObserver()=default;
    virtual void notify(Character& character)=0;
};

#endif