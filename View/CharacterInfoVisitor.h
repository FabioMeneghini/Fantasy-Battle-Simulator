#ifndef CHARACTER_INFO_VISITOR_H
#define CHARACTER_INFO_VISITOR_H

#include "../Character/Visitor.h"
#include "../Character/Warrior.h"
#include "../Character/Wizard.h"
#include "../Character/Healer.h"
#include "../Character/Skeleton.h"
#include "../Character/Goblin.h"
#include "CharacterInfoWidget.h"

class CharacterInfoVisitor: public Visitor {
private:
    CharacterInfoWidget* widget;
public:
    CharacterInfoVisitor(CharacterInfoWidget* widget);
    void visit(const Warrior&);
    void visit(const Wizard&);
    void visit(const Healer&);
    void visit(const Skeleton&);
    void visit(const Goblin&);
};

#endif