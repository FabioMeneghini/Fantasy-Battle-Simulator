#ifndef CHARACTER_INFO_WIDGET_H
#define CHARACTER_INFO_WIDGET_H

#include <QWidget>
#include <QLabel>
#include "../Character/Character.h"
#include "../Character/CharacterObserver.h"

class CharacterInfoWidget: public QWidget, public CharacterObserver {
Q_OBJECT
private:
    Character* character;
    QLabel* name;
    QLabel* hp;
    QLabel* power;
    QLabel* level_armor;
    QLabel* action;

public:
    CharacterInfoWidget(Character* character, QWidget* parent=0);
    void show();
    void notify(Character& character) override;
    QLabel* getNameWidget() const;
    QLabel* getHpWidget() const;
    QLabel* getPowerWidget() const;
    QLabel* getLevelArmorWidget() const;
    QLabel* getActionWidget() const;
};

#endif