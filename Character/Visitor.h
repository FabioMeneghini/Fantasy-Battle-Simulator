#ifndef VISITOR_H
#define VISITOR_H

class Warrior;
class Wizard;
class Healer;
class Skeleton;
class Goblin;

class Visitor {
public:
    virtual ~Visitor()=default;
    virtual void visit(const Warrior&)=0;
    virtual void visit(const Wizard&)=0;
    virtual void visit(const Healer&)=0;
    virtual void visit(const Skeleton&)=0;
    virtual void visit(const Goblin&)=0;
};

#endif