#include "CreateTeamWidget.h"
#include "CreateCharacterWidget.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QVector>

CreateTeamWidget::CreateTeamWidget(bool enemy_team, QWidget* parent): QWidget(parent), button(new QPushButton("Aggiungi nuovo personaggio")),
                                                                      vbox(new QVBoxLayout(this)), is_enemy_team(enemy_team) {
    vbox->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    QLabel* title;
    if(is_enemy_team)
        title=new QLabel("Crea Team Nemici");
    else
        title=new QLabel("Crea Team Alleati");
    //title->setObjectName("title");
    title->setAlignment(Qt::AlignHCenter);
    vbox->addWidget(title);

    character_widget_vector.push_back(new CreateCharacterWidget(this));
    vbox->addWidget(character_widget_vector[0]);
    vbox->addWidget(button);
    connect(button, &QPushButton::pressed, this, &CreateTeamWidget::addCharacter);

    connect(character_widget_vector[0], &CreateCharacterWidget::remove, this, &CreateTeamWidget::removeCharacter);
}

bool CreateTeamWidget::isvalid() const {
    if(character_widget_vector.isEmpty())
        return false;
    for(auto it=character_widget_vector.begin(); it!=character_widget_vector.end(); ++it)
        if(!((*it)->isValid()))
            return false;
    return true;
}

QVector<CreateCharacterWidget*> CreateTeamWidget::getCharacterWidgetVector() const {
    return character_widget_vector;
}

void CreateTeamWidget::clear() {
    while(!character_widget_vector.isEmpty()) {
        vbox->removeWidget(character_widget_vector.last());
        delete character_widget_vector.last();
        character_widget_vector.removeLast();
    }
}

void CreateTeamWidget::addCharacter() {
    vbox->removeWidget(button);
    character_widget_vector.push_back(new CreateCharacterWidget(this));
    vbox->addWidget(character_widget_vector[character_widget_vector.size()-1]);
    vbox->addWidget(button);
    connect(character_widget_vector[character_widget_vector.size()-1], &CreateCharacterWidget::remove, this, &CreateTeamWidget::removeCharacter);
}

void CreateTeamWidget::removeCharacter(CreateCharacterWidget* target) {
    vbox->removeWidget(target);
    character_widget_vector.removeOne(target);
    delete target;
}