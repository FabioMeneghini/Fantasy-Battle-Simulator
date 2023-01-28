#include "CharacterInfoWidget.h"
#include "CharacterInfoVisitor.h"
#include <QVBoxLayout>

CharacterInfoWidget::CharacterInfoWidget(Character* c, QWidget* p): QWidget(p), character(c) {
    QVBoxLayout* layout=new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    name=new QLabel();
    layout->addWidget(name);
    hp=new QLabel();
    layout->addWidget(hp);
    power=new QLabel();
    layout->addWidget(power);
    level_armor=new QLabel();
    layout->addWidget(level_armor);
    action=new QLabel();
    layout->addWidget(action);

    character->registerObserver(this);
}

QLabel* CharacterInfoWidget::getNameWidget() const {
    return name;
}

QLabel* CharacterInfoWidget::getHpWidget() const {
    return hp;
}

QLabel* CharacterInfoWidget::getPowerWidget() const {
    return power;
}

QLabel* CharacterInfoWidget::getLevelArmorWidget() const {
    return level_armor;
}

QLabel* CharacterInfoWidget::getActionWidget() const {
    return action;
}

void CharacterInfoWidget::show() {
    hp->setText("HP: "+QString::number(character->getHp())+"/"+QString::number(character->getMaxHp()));
    power->setText("Potenza: "+QString::number(character->getPower()));
    CharacterInfoVisitor visitor(this);
    character->accept(visitor);
}

void CharacterInfoWidget::notify(Character& c) {
    hp->setText("HP: "+QString::number(c.getHp())+"/"+QString::number(c.getMaxHp()));
}