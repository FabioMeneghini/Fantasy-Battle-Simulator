#include "CreateCharacterWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QFrame>
#include <QPushButton>

CreateCharacterWidget::CreateCharacterWidget(QWidget* parent): QFrame(parent) {
    QHBoxLayout* hbox=new QHBoxLayout(this);

    QVBoxLayout* vbox=new QVBoxLayout();
    vbox->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    QFormLayout* form=new QFormLayout();
    form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    vbox->addLayout(form);
    hbox->addLayout(vbox);
    
    //type
    type=new QComboBox();
    type->setObjectName("type");
    type->addItem("Guerriero");
    type->addItem("Stregone");
    type->addItem("Guaritore");
    type->addItem("Scheletro");
    type->addItem("Goblin");
    form->addRow("Tipo", type);

    //name
    name=new QLineEdit();
    form->addRow("Nome", name);

    //max hp
    max_hp=new QSpinBox();
    max_hp->setMinimum(1);
    max_hp->setMaximum(1000);
    max_hp->setSingleStep(5);
    max_hp->setValue(100);
    form->addRow("Max HP", max_hp);

    //power
    power=new QSpinBox();
    power->setMinimum(1);
    power->setMaximum(50);
    power->setSingleStep(1);
    power->setValue(10);
    form->addRow("Potenza", power);

    //level / armor
    level_armor=new QSpinBox();
    level_armor->setMinimum(1);
    level_armor->setMaximum(50);
    level_armor->setSingleStep(1);
    level_armor->setValue(5);
    form->addRow("Livello / Armatura", level_armor);

    QPushButton* button=new QPushButton("Rimuovi");
    hbox->addWidget(button);

    connect(button, &QPushButton::pressed, this, &CreateCharacterWidget::removeCharacter);

    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    setLineWidth(2);
}

void CreateCharacterWidget::removeCharacter() {
    emit remove(this);
}

bool CreateCharacterWidget::isValid() const {
    return name->text()!="";
}

QString CreateCharacterWidget::getTypeText() const {
    return type->itemText(type->currentIndex());
}

QString CreateCharacterWidget::getNameText() const {
    return name->text();
}

int CreateCharacterWidget::getMaxHpValue() const {
    return max_hp->value();
}

int CreateCharacterWidget::getPowerValue() const {
    return power->value();
}

int CreateCharacterWidget::getLevelArmorValue() const {
    return level_armor->value();
}

QComboBox* CreateCharacterWidget::getTypeWidget() const {
    return type;
}

QLineEdit* CreateCharacterWidget::getNameWidget() const {
    return name;
}

QSpinBox* CreateCharacterWidget::getMaxHpWidget() const {
    return max_hp;
}

QSpinBox* CreateCharacterWidget::getPowerWidget() const {
    return power;
}

QSpinBox* CreateCharacterWidget::getLevelArmorWidget() const {
    return level_armor;
}