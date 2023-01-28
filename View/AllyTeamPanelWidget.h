#ifndef ALLY_TEAM_PANEL_WIDGET_H
#define ALLY_TEAM_PANEL_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QHBoxLayout>
#include "CharacterInfoWidget.h"
#include "../Team/Team.h"
#include "../Team/TeamObserver.h"

class AllyTeamPanelWidget: public QWidget, public TeamObserver {
Q_OBJECT
private:
    Team& team;
    QVector<QLabel*> artwork_vector;
    CharacterInfoWidget* info;
    QHBoxLayout* layout;
public:
    explicit AllyTeamPanelWidget(Team& team, QWidget* parent=0);
    void notify(Team& team) override;
signals:
    void attack();
    void switchCharacter();
    void close();
};

#endif