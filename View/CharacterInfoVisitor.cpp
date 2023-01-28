#include "CharacterInfoVisitor.h"
#include "../Character/Warrior.h"
#include "../Character/Wizard.h"
#include "../Character/Healer.h"
#include "../Character/Skeleton.h"
#include "../Character/Goblin.h"
#include <QLabel>

CharacterInfoVisitor::CharacterInfoVisitor(CharacterInfoWidget* w): widget(w) {}

void CharacterInfoVisitor::visit(const Warrior& warrior) {
    QLabel* name=widget->getNameWidget();
    name->setText(QString::fromStdString(warrior.getName())+" (Guerriero)");
    QLabel* level=widget->getLevelArmorWidget();
    level->setText("Livello: "+QString::number(warrior.getLevel()));
    QLabel* action=widget->getActionWidget();
    action->setText("Azione: attacca il primo avversario");
}

void CharacterInfoVisitor::visit(const Wizard& wizard) {
    QLabel* name=widget->getNameWidget();
    name->setText(QString::fromStdString(wizard.getName())+" (Stregone)");
    QLabel* level=widget->getLevelArmorWidget();
    level->setText("Livello: "+QString::number(wizard.getLevel()));
    QLabel* action=widget->getActionWidget();
    action->setText("Azione: attacca tutti gli avversari");
}

void CharacterInfoVisitor::visit(const Healer& healer) {
    QLabel* name=widget->getNameWidget();
    name->setText(QString::fromStdString(healer.getName())+" (Guaritore)");
    QLabel* level=widget->getLevelArmorWidget();
    level->setText("Livello: "+QString::number(healer.getLevel()));
    QLabel* action=widget->getActionWidget();
    action->setText("Azione: cura tutti gli alleati\nnon mostri");
}

void CharacterInfoVisitor::visit(const Skeleton& skeleton) {
    QLabel* name=widget->getNameWidget();
    name->setText(QString::fromStdString(skeleton.getName())+" (Scheletro)");
    QLabel* armor=widget->getLevelArmorWidget();
    armor->setText("Armatura: "+QString::number(skeleton.getArmor()));
    QLabel* action=widget->getActionWidget();
    action->setText("Azione: attacca tutti gli avversari");
}

void CharacterInfoVisitor::visit(const Goblin& goblin) {
    QLabel* name=widget->getNameWidget();
    name->setText(QString::fromStdString(goblin.getName())+" (Goblin)");
    QLabel* armor=widget->getLevelArmorWidget();
    armor->setText("Armatura: "+QString::number(goblin.getArmor()));
    QLabel* action=widget->getActionWidget();
    action->setText("Azione: attacca il primo avversario");
}