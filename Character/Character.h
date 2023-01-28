#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "CharacterObserver.h"
#include "../Team/Team.h"
#include "Visitor.h"

class Team;
class Visitor;
class CharacterObserver;

class Character {
private:
    std::string _name;
    unsigned int _max_hp;
    unsigned int _power;
    std::string _artwork_path;
protected:
    unsigned int _hp; //campi dati protetti perché possono essere modificati dalle sue due classi derivate
    bool _is_alive;
    std::vector<CharacterObserver*> _observers;
    Character(const std::string& name, unsigned int max_hp, unsigned int power, const std::string& artwork_path);

public:
    virtual ~Character()=default;
    virtual Character* clone() const=0;

    const std::string& getName() const;
    unsigned int getMaxHp() const;
    unsigned int getHp() const;
    unsigned int getPower() const;
    const std::string& getArtworkPath() const;
    bool isAlive() const;

    void heal(unsigned int amount);
    void hit(Team& target_team, Character*& target, unsigned int amount) const;
    virtual void takeDamage(unsigned int amount)=0;
    virtual void action(Team& target_team)=0; //può fare side effect sull'oggetto di invocazione e sul target_team

    virtual void accept(Visitor& visitor) const=0;
    void registerObserver(CharacterObserver* obs);
    void removeObserver(CharacterObserver* obs);
};

#endif