#include "Team.h"
#include "TeamObserver.h"
#include <stdexcept>

//************************** ITERATOR

Team::Iterator::Iterator(Character** ptr): _ptr(ptr) {}

Team::Iterator::Iterator(): _ptr(nullptr) {}

Team::Iterator& Team::Iterator::operator++() {
    if(_ptr!=nullptr)
        _ptr=_ptr+1;
    return *this;
}

Team::Iterator Team::Iterator::operator++(int) {
    Iterator tmp=*this;
    if(_ptr!=nullptr)
        _ptr=_ptr+1;
    return tmp;
}

Team::Iterator& Team::Iterator::operator--() {
    if(_ptr!=nullptr)
        _ptr=_ptr-1;
    return *this;
}

Team::Iterator Team::Iterator::operator--(int) {
    Iterator tmp=*this;
    if(_ptr!=nullptr)
        _ptr=_ptr-1;
    return tmp;
}

Character*& Team::Iterator::operator*() const {
    return *_ptr;
}

Character** Team::Iterator::operator->() const {
    return _ptr;
}

bool Team::Iterator::operator==(const Iterator& it) const {
    return _ptr==it._ptr;
}

bool Team::Iterator::operator!=(const Iterator& it) const {
    return _ptr!=it._ptr;
}

//************************** TEAM

Team::Iterator Team::begin() const {
    return _size>0 ? Iterator(&_p[0]) : Iterator();
}

Team::Iterator Team::end() const {
    return _size>0 ? Iterator(&_p[_size]) : Iterator(); //_size è la prima posizione non valida nell'array _p
}

Team::Team(unsigned int capacity):
           _capacity(capacity), _size(0), _alive_count(capacity),
           _p(capacity>0 ? new Character*[capacity] : nullptr) {
    for(unsigned int i=0; i<_capacity; ++i)
        _p[i]=nullptr;
}

Team::~Team() {
    if(_p!=nullptr) {
        for(unsigned int i=0; i<_capacity; ++i)
            if(_p[i]!=nullptr)
                delete _p[i];
        delete[] _p;
    }
}

Team::Team(const Team& t): _capacity(t._capacity), _size(t._size), _alive_count(t._alive_count),
                           _p(t._capacity>0 && t._p!=nullptr ? new Character*[t._capacity] : nullptr) {
    if(t._p!=nullptr) {
        for(unsigned int i=0; i<t._capacity; ++i) {
            if(t._p[i]==nullptr)
                _p[i]=nullptr;
            else
                _p[i]=t._p[i]->clone();
        }
    }
}

Character*& Team::operator[](unsigned int i) const { //nessun controllo sulla validità della posizione
    return _p[i];
}

Team& Team::operator=(const Team& t) {
    if(this!=&t) {
        if(_p!=nullptr) { //prima cancella il vecchio contenuto dell'array dinamico _p
            for(unsigned int i=0; i<_capacity; ++i)
                if(_p[i]!=nullptr)
                    delete _p[i];
            delete[] _p;
        }
        _capacity=t._capacity;
        _size=t._size;
        _alive_count=t._alive_count;
        _p=t._capacity>0 && t._p!=nullptr ? new Character*[t._capacity] : nullptr;
        if(t._p!=nullptr) { //poi copio il contenuto di t._p in _p
            for(unsigned int i=0; i<t._capacity; ++i) {
                if(t._p[i]==nullptr)
                    _p[i]=nullptr;
                else
                    _p[i]=(t._p[i])->clone();
            }
        }
    }
    return *this;
}

void Team::insertBack(Character* pc) {
    if(_size<_capacity) {
        _p[_size]=pc;
        ++_size;
    }
    /*else
        throw std::logic_error("Errore: Il team è già al completo");*/
}

void Team::removeBack() {
    if(_size>0) {
        --_size;
        delete _p[_size];
    }
    /*else
        throw std::logic_error("Errore: Il team è già vuoto");*/
}

Character*& Team::search(unsigned int pos) const {
    return pos<_size ? (*this).operator[](pos) : (*this).operator[](_size-1);
    /*if(pos>=_size)
        throw std::logic_error("Errore: posizione non valida");
    else
        return (*this).operator[](pos);*/
}

void Team::leftShift(unsigned int from, unsigned int to) { //assumo che i membri del team deceduti stiano in coda
    if(_size<=0)
        throw std::logic_error("Errore: Il team è vuoto");
    else if(from>to || to>=_size)
        throw std::logic_error("Errore: Left shift non valido");
    else if(_alive_count<=0)
        throw std::logic_error("Errore: Nessun membro del team vivo");
    else if(from==to)
        return;
    else {
        Character* tmp=_p[from];
        for(unsigned int i=from; i<to; ++i)
            _p[i]=_p[i+1];
        _p[to]=tmp;
    }
    for(auto it=_observers.begin(); it!=_observers.end(); ++it)
        (*it)->notify(*this);
}

void Team::leftShiftAlive() {
    leftShift(0, _alive_count-1);
}

void Team::moveBack(Character*& target) {
    Character* tmp=_p[_alive_count-1];
    _p[_alive_count-1]=target;
    target=tmp;
    for(auto it=_observers.begin(); it!=_observers.end(); ++it)
        (*it)->notify(*this);
}

unsigned int Team::getCapacity() const {
    return _capacity;
}

unsigned int Team::getSize() const {
    return _size;
}

unsigned int Team::getAliveCount() const {
    return _alive_count;
}

void Team::setAliveCount(unsigned int amount) {
    if(amount<=_size)
        _alive_count=amount;
    /*else
        throw std::logic_error("Errore: valore amount non valido (amount>_size)");*/
}

void Team::registerObserver(TeamObserver* obs) {
    _observers.push_back(obs);
}
