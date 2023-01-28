#ifndef ENEMY_TEAM_PANEL_WIDGET_H
#define ENEMY_TEAM_PANEL_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QHBoxLayout>
#include "CharacterInfoWidget.h"
#include "../Team/TeamObserver.h"
#include "../Team/Team.h"

class EnemyTeamPanelWidget: public QWidget, public TeamObserver {
Q_OBJECT
private:
    Team& team;
    QVector<QLabel*> artwork_vector;
    CharacterInfoWidget* info;
    QHBoxLayout* layout;
public:
    explicit EnemyTeamPanelWidget(Team& team, QWidget* parent=0);
    void notify(Team& team) override;
};

#endif