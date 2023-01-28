#include "JsonVisitor.h"
#include <QJsonObject>

QJsonObject JsonVisitor::getContent() const {
    return content;
}

void JsonVisitor::visit(const Warrior& warrior) {
    QJsonObject warrior_object;
    warrior_object.insert("type", QJsonValue::fromVariant("warrior"));
    warrior_object.insert("name", QJsonValue::fromVariant(warrior.getName().c_str()));
    warrior_object.insert("max_hp", QJsonValue::fromVariant(warrior.getMaxHp()));
    warrior_object.insert("power", QJsonValue::fromVariant(warrior.getPower()));
    warrior_object.insert("level", QJsonValue::fromVariant(warrior.getLevel()));
    content=warrior_object;
}

void JsonVisitor::visit(const Wizard& wizard) {
    QJsonObject wizard_object;
    wizard_object.insert("type", QJsonValue::fromVariant("wizard"));
    wizard_object.insert("name", QJsonValue::fromVariant(wizard.getName().c_str()));
    wizard_object.insert("max_hp", QJsonValue::fromVariant(wizard.getMaxHp()));
    wizard_object.insert("power", QJsonValue::fromVariant(wizard.getPower()));
    wizard_object.insert("level", QJsonValue::fromVariant(wizard.getLevel()));
    content=wizard_object;
}

void JsonVisitor::visit(const Healer& healer) {
    QJsonObject healer_object;
    healer_object.insert("type", QJsonValue::fromVariant("healer"));
    healer_object.insert("name", QJsonValue::fromVariant(healer.getName().c_str()));
    healer_object.insert("max_hp", QJsonValue::fromVariant(healer.getMaxHp()));
    healer_object.insert("power", QJsonValue::fromVariant(healer.getPower()));
    healer_object.insert("level", QJsonValue::fromVariant(healer.getLevel()));
    content=healer_object;
}

void JsonVisitor::visit(const Skeleton& skeleton) {
    QJsonObject skeleton_object;
    skeleton_object.insert("type", QJsonValue::fromVariant("skeleton"));
    skeleton_object.insert("name", QJsonValue::fromVariant(skeleton.getName().c_str()));
    skeleton_object.insert("max_hp", QJsonValue::fromVariant(skeleton.getMaxHp()));
    skeleton_object.insert("power", QJsonValue::fromVariant(skeleton.getPower()));
    skeleton_object.insert("armor", QJsonValue::fromVariant(skeleton.getArmor()));
    content=skeleton_object;
}

void JsonVisitor::visit(const Goblin& goblin) {
    QJsonObject goblin_object;
    goblin_object.insert("type", QJsonValue::fromVariant("goblin"));
    goblin_object.insert("name", QJsonValue::fromVariant(goblin.getName().c_str()));
    goblin_object.insert("max_hp", QJsonValue::fromVariant(goblin.getMaxHp()));
    goblin_object.insert("power", QJsonValue::fromVariant(goblin.getPower()));
    goblin_object.insert("armor", QJsonValue::fromVariant(goblin.getArmor()));
    content=goblin_object;
}