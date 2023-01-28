#ifndef JSON_VISITOR_H
#define JSON_VISITOR_H

#include <QJsonObject>
#include "../Character/Visitor.h"
#include "../Character/Warrior.h"
#include "../Character/Wizard.h"
#include "../Character/Healer.h"
#include "../Character/Skeleton.h"
#include "../Character/Goblin.h"

class JsonVisitor: public Visitor {
private:
    QJsonObject content;
public:
    QJsonObject getContent() const;
    void visit(const Warrior&);
    void visit(const Wizard&);
    void visit(const Healer&);
    void visit(const Skeleton&);
    void visit(const Goblin&);
};

#endif