#ifndef CREATE_TEAM_WIDGET_H
#define CREATE_TEAM_WIDGET_H

#include <QLineEdit>
#include <QSpinBox>
#include <QVector>
#include <QPushButton>
#include <QVBoxLayout>
#include "../Team/Team.h"
#include "CreateCharacterWidget.h"

class CreateTeamWidget: public QWidget {
Q_OBJECT
private:
    QVector<CreateCharacterWidget*> character_widget_vector;
    QPushButton* button;
    QVBoxLayout* vbox;
    bool is_enemy_team;

public:
    explicit CreateTeamWidget(bool enemy_team, QWidget* parent = 0);
    bool isvalid() const;
    void clear();
    QVector<CreateCharacterWidget*> getCharacterWidgetVector() const;

public slots:
    void addCharacter();
    void removeCharacter(CreateCharacterWidget*);
};

#endif