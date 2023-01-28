#ifndef CHARACTER_WIDGET_VISITOR_H
#define CHARACTER_WIDGET_VISITOR_H

#include "../Character/Visitor.h"
#include "../Character/Warrior.h"
#include "../Character/Wizard.h"
#include "../Character/Healer.h"
#include "../Character/Skeleton.h"
#include "../Character/Goblin.h"
#include "CreateCharacterWidget.h"

class CharacterWidgetVisitor: public Visitor {
private:
    CreateCharacterWidget* widget;
public:
    CharacterWidgetVisitor(CreateCharacterWidget* widget);
    void visit(const Warrior&);
    void visit(const Wizard&);
    void visit(const Healer&);
    void visit(const Skeleton&);
    void visit(const Goblin&);
};

#endif