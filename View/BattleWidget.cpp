#include "BattleWidget.h"
#include "../Character/Healer.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>

BattleWidget::BattleWidget(Team& at, Team& et, QWidget* p): QWidget(p), ally_team(at), enemy_team(et) {
    QVBoxLayout* layout=new QVBoxLayout(this);

    enemy_team_panel=new EnemyTeamPanelWidget(enemy_team);
    layout->addWidget(enemy_team_panel);

    layout->addStretch();

    ally_team_panel=new AllyTeamPanelWidget(ally_team);
    layout->addWidget(ally_team_panel);

    connect(ally_team_panel, &AllyTeamPanelWidget::attack, this, &BattleWidget::playerAttacks);
    connect(ally_team_panel, &AllyTeamPanelWidget::switchCharacter, this, &BattleWidget::switchCharacter);
    connect(ally_team_panel, &AllyTeamPanelWidget::close, this, &BattleWidget::close);
}

void BattleWidget::playerAttacks() {
    bool closed=false;
    if(enemy_team.getAliveCount()>0) {
        if(dynamic_cast<Healer*>(ally_team.search(0)))
            (ally_team.search(0))->action(ally_team);
        else
            (ally_team.search(0))->action(enemy_team);
        if(enemy_team.getAliveCount()<=0) {
            emit endBattle(true);
            closed=true;
        }
    }

    if(!closed && ally_team.getAliveCount()>0) {
        if(dynamic_cast<Healer*>(enemy_team.search(0)))
            (enemy_team.search(0))->action(enemy_team);
        else
            (enemy_team.search(0))->action(ally_team);
        if(ally_team.getAliveCount()<=0) 
            emit endBattle(false);
    }
}

void BattleWidget::switchCharacter() {
    ally_team.leftShiftAlive();
}