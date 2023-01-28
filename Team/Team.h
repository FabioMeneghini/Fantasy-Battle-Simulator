#ifndef TEAM_H
#define TEAM_H

class Character;
#include "../Character/Character.h"
#include "TeamObserver.h"
#include <vector>

class Team {
private:
    unsigned int _capacity; //dimensione massima del team, serve per non riallocarlo ad ogni inserimento
    unsigned int _size; //indica quanti membri del team sono stati effettivamente inseriti
    unsigned int _alive_count; //indica quanti membri del team sono ancora vivi
    Character** _p; //array dinamico di puntatori a Character
    std::vector<TeamObserver*> _observers;
    void leftShift(unsigned int from, unsigned int to); //[from, to]

public:
    class Iterator {
    friend class Team;
    private:
        Character** _ptr;
        Iterator(Character** ptr);
    public:
        Iterator();
        Iterator& operator++(); //prefisso
        Iterator operator++(int); //postfisso
        Iterator& operator--(); //prefisso
        Iterator operator--(int); //postfisso
        Character*& operator*() const;
        Character** operator->() const;
        bool operator==(const Iterator& it) const;
        bool operator!=(const Iterator& it) const;
    };
    Iterator begin() const;
    Iterator end() const;

    explicit Team(unsigned int capacity=0);
    ~Team(); //distruttore profondo
    Team(const Team& t); //copia profonda

    void insertBack(Character* pc);
    void removeBack();
    Character*& search(unsigned int pos) const;
    void leftShiftAlive(); //left shift tra i membri del team non ancora deceduti
    void moveBack(Character*& target); //quando un membro del team viene sconfitto viene messo alla fine

    Character*& operator[](unsigned int i) const;
    Team& operator=(const Team& t); //assegnazione profonda

    unsigned int getCapacity() const;
    unsigned int getSize() const;
    unsigned int getAliveCount() const;
    void setAliveCount(unsigned int amount);

    void registerObserver(TeamObserver* obs);
};

#endif