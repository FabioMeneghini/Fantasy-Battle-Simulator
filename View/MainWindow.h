#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "CreateTeamWidget.h"
#include "BattleWidget.h"
#include "../Team/Team.h"
#include <QMainWindow>
#include <QWidget>
#include <QToolBar>
#include <QSplitter>
#include <QStackedWidget>
#include <QString>

class MainWindow: public QMainWindow {
Q_OBJECT
private:
    bool can_save;
    bool battle;
    Team& ally_team;
    Team& enemy_team;
    QStackedWidget* stacked_widget;
    BattleWidget* battle_widget;
    CreateTeamWidget* enemy_team_widget;
    CreateTeamWidget* ally_team_widget;

    void updateTeam(CreateTeamWidget* team_widget, Team& team);
    void clearStack();

public:
    MainWindow(Team& ally_team, Team& enemy_team, QWidget* parent=0);

public slots:
    void newTeam();
    void openTeam();
    void saveTeam();
    void newBattle();
    void closeBattle();
    void close();
    void showStatus(QString message);
    void endBattle(bool);
};

#endif