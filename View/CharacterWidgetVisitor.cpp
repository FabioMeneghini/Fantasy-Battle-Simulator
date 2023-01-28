#include "CharacterWidgetVisitor.h"
#include "../Character/Warrior.h"
#include "../Character/Wizard.h"
#include "../Character/Healer.h"
#include "../Character/Skeleton.h"
#include "../Character/Goblin.h"

CharacterWidgetVisitor::CharacterWidgetVisitor(CreateCharacterWidget* w): widget(w) {}

void CharacterWidgetVisitor::visit(const Warrior& warrior) {
    widget->getTypeWidget()->setCurrentText("Guerriero");
    widget->getNameWidget()->setText(QString::fromStdString(warrior.getName()));
    widget->getMaxHpWidget()->setValue(warrior.getMaxHp());
    widget->getPowerWidget()->setValue(warrior.getPower());
    widget->getLevelArmorWidget()->setValue(warrior.getLevel());
}

void CharacterWidgetVisitor::visit(const Wizard& wizard) {
    widget->getTypeWidget()->setCurrentText("Stregone");
    widget->getNameWidget()->setText(QString::fromStdString(wizard.getName()));
    widget->getMaxHpWidget()->setValue(wizard.getMaxHp());
    widget->getPowerWidget()->setValue(wizard.getPower());
    widget->getLevelArmorWidget()->setValue(wizard.getLevel());
}

void CharacterWidgetVisitor::visit(const Healer& healer) {
    widget->getTypeWidget()->setCurrentText("Guaritore");
    widget->getNameWidget()->setText(QString::fromStdString(healer.getName()));
    widget->getMaxHpWidget()->setValue(healer.getMaxHp());
    widget->getPowerWidget()->setValue(healer.getPower());
    widget->getLevelArmorWidget()->setValue(healer.getLevel());
}

void CharacterWidgetVisitor::visit(const Skeleton& skeleton) {
    widget->getTypeWidget()->setCurrentText("Scheletro");
    widget->getNameWidget()->setText(QString::fromStdString(skeleton.getName()));
    widget->getMaxHpWidget()->setValue(skeleton.getMaxHp());
    widget->getPowerWidget()->setValue(skeleton.getPower());
    widget->getLevelArmorWidget()->setValue(skeleton.getArmor());
}

void CharacterWidgetVisitor::visit(const Goblin& goblin) {
    widget->getTypeWidget()->setCurrentText("Goblin");
    widget->getNameWidget()->setText(QString::fromStdString(goblin.getName()));
    widget->getMaxHpWidget()->setValue(goblin.getMaxHp());
    widget->getPowerWidget()->setValue(goblin.getPower());
    widget->getLevelArmorWidget()->setValue(goblin.getArmor());
}