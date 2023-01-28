#ifndef BATTLE_WIDGET_H
#define BATTLE_WIDGET_H

#include <QWidget>
#include "../Team/Team.h"
#include "AllyTeamPanelWidget.h"
#include "EnemyTeamPanelWidget.h"

class BattleWidget: public QWidget {
Q_OBJECT
private:
    Team ally_team;
    Team enemy_team;
    AllyTeamPanelWidget* ally_team_panel;
    EnemyTeamPanelWidget* enemy_team_panel;
public:
    BattleWidget(Team& ally_team, Team& enemy_team, QWidget* parent=0);
public slots:
    void playerAttacks();
    void switchCharacter();
signals:
    void close();
    void endBattle(bool);
};

#endif