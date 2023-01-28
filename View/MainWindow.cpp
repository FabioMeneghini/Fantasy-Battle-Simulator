#include "MainWindow.h"
#include "../Team/Team.h"
#include "../Character/Warrior.h"
#include "../Character/Wizard.h"
#include "../Character/Healer.h"
#include "../Character/Skeleton.h"
#include "../Character/Goblin.h"
#include "JsonVisitor.h"
#include "CharacterWidgetVisitor.h"
#include "Json.h"
#include "BattleWidget.h"
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QSplitter>
#include <QStatusBar>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QVector>
#include <QFileDialog>

MainWindow::MainWindow(Team& team1, Team& team2, QWidget* parent): QMainWindow(parent), can_save(true), battle(false), ally_team(team1), enemy_team(team2) {
    //actions
    QAction* nuovo = new QAction(QIcon(QPixmap(":/Assets/new.svg")), "Nuovo team");
    nuovo->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    QAction* apri = new QAction(QIcon(QPixmap(":/Assets/open.svg")), "Apri team");
    apri->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
    QAction* salva = new QAction(QIcon(QPixmap(":/Assets/save.svg")), "Salva");
    salva->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    QAction* nuova_battaglia = new QAction(QIcon(QPixmap(":/Assets/battle.svg")), "Nuova battaglia");
    nuova_battaglia->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_B));
    QAction* termina_battaglia = new QAction(QIcon(QPixmap(":/Assets/close.svg")), "Termina battaglia");
    termina_battaglia->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
    QAction* chiudi = new QAction(QIcon(QPixmap(":/Assets/close.svg")), "Chiudi");
    chiudi->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    //menu bar
    QMenu* file = menuBar()->addMenu("&File");
    file->addAction(nuovo);
    file->addAction(apri);
    file->addAction(salva);
    file->addSeparator();
    file->addAction(chiudi);
    QMenu* battaglia = menuBar()->addMenu("&Battaglia");
    battaglia->addAction(nuova_battaglia);
    battaglia->addAction(termina_battaglia);

    //main widgets
    stacked_widget=new QStackedWidget(this);
    setCentralWidget(stacked_widget);

    //team creation
    QSplitter* splitter=new QSplitter(this);
    stacked_widget->addWidget(splitter);

    ally_team_widget=new CreateTeamWidget(false, this);
    splitter->addWidget(ally_team_widget);
    enemy_team_widget=new CreateTeamWidget(true, this);
    splitter->addWidget(enemy_team_widget);

    splitter->setSizes(QList<int>() << 2000 << 2000);

    //segnali
    connect(nuovo, &QAction::triggered, this, &MainWindow::newTeam);
    connect(apri, &QAction::triggered, this, &MainWindow::openTeam);
    connect(salva, &QAction::triggered, this, &MainWindow::saveTeam);
    connect(nuova_battaglia, &QAction::triggered, this, &MainWindow::newBattle);
    connect(termina_battaglia, &QAction::triggered, this, &MainWindow::closeBattle);
    connect(chiudi, &QAction::triggered, this, &MainWindow::close);

    showStatus("Pronto");
}

void MainWindow::clearStack() {
    QWidget* widget=stacked_widget->widget(1);
    while(widget) {
        stacked_widget->removeWidget(widget);
        delete widget;
        widget=stacked_widget->widget(1);
    }
}

void MainWindow::newTeam() {
    if(battle) {
        QMessageBox::StandardButton confirmation;
        confirmation=QMessageBox::question(this, "Creare nuovi team?", "La battaglia in corso verrà chiusa. Continuare?", QMessageBox::Yes | QMessageBox::No);
        if(confirmation==QMessageBox::No)
            return;
    }
    can_save=false;
    battle=false;
    ally_team_widget->clear();
    enemy_team_widget->clear();
    clearStack();
    can_save=true;
    showStatus("Crea nuovi team");
}

void MainWindow::openTeam() {
    if(battle) {
        showStatus("Impossibile aprire team in questo momento");
        QMessageBox::warning(this, "Errore", "Impossibile aprire team in questo momento", QMessageBox::Ok);
        return;
    }
    can_save=false;
    QString path = QFileDialog::getOpenFileName(this, "Scegli il file", "./", "JSON files *.json");
    if(path.isEmpty()) {
        showStatus("Percorso non valido");
        can_save=true;
        return;
    }
    Json::load(path, ally_team, enemy_team);

    ally_team_widget->clear();
    enemy_team_widget->clear();

    for(auto it=ally_team.begin(); it!=ally_team.end(); ++it) {
        ally_team_widget->addCharacter();
        CharacterWidgetVisitor visitor(ally_team_widget->getCharacterWidgetVector().last());
        (*it)->accept(visitor);
    }
    for(auto it=enemy_team.begin(); it!=enemy_team.end(); ++it) {
        enemy_team_widget->addCharacter();
        CharacterWidgetVisitor visitor(enemy_team_widget->getCharacterWidgetVector().last());
        (*it)->accept(visitor);
    }

    can_save=true;
    showStatus("Apri team");
}

void MainWindow::updateTeam(CreateTeamWidget* team_widget, Team& team) {
    QVector<CreateCharacterWidget*> team_widget_vector=team_widget->getCharacterWidgetVector();
    team=Team(team_widget_vector.size());
    Character* character;
    for(auto it=team_widget_vector.begin(); it!=team_widget_vector.end(); ++it) {
        if((*it)->getTypeText()=="Guerriero") {
            character=new Warrior((*it)->getNameText().toStdString(),
                                  static_cast<unsigned int>((*it)->getMaxHpValue()),
                                  static_cast<unsigned int>((*it)->getPowerValue()),
                                  static_cast<unsigned int>((*it)->getLevelArmorValue()),
                                  ":Assets/warrior.png");
        }
        else if((*it)->getTypeText()=="Stregone") {
            character=new Wizard((*it)->getNameText().toStdString(),
                                 static_cast<unsigned int>((*it)->getMaxHpValue()),
                                 static_cast<unsigned int>((*it)->getPowerValue()),
                                 static_cast<unsigned int>((*it)->getLevelArmorValue()),
                                 ":Assets/wizard.png");
        }
        else if((*it)->getTypeText()=="Guaritore") {
            character=new Healer((*it)->getNameText().toStdString(),
                                 static_cast<unsigned int>((*it)->getMaxHpValue()),
                                 static_cast<unsigned int>((*it)->getPowerValue()),
                                 static_cast<unsigned int>((*it)->getLevelArmorValue()),
                                 ":Assets/healer.png");
        }
        else if((*it)->getTypeText()=="Scheletro") {
            character=new Skeleton((*it)->getNameText().toStdString(),
                                   static_cast<unsigned int>((*it)->getMaxHpValue()),
                                   static_cast<unsigned int>((*it)->getPowerValue()),
                                   static_cast<unsigned int>((*it)->getLevelArmorValue()),
                                   ":Assets/skeleton.png");
        }
        //else if((*it)->getTypeText()=="Goblin")
        else {
            character=new Goblin((*it)->getNameText().toStdString(),
                                 static_cast<unsigned int>((*it)->getMaxHpValue()),
                                 static_cast<unsigned int>((*it)->getPowerValue()),
                                 static_cast<unsigned int>((*it)->getLevelArmorValue()),
                                 ":Assets/goblin.png");
        }
        team.insertBack(character);
    }
}

void MainWindow::saveTeam() {
    if(!can_save) {
        showStatus("Impossibile salvare in questo momento");
        QMessageBox::warning(this, "Errore", "Impossibile salvare in questo momento", QMessageBox::Ok);
        return;
    }
    if(!(ally_team_widget->isvalid() && enemy_team_widget->isvalid())) {
        showStatus("Team non validi, riempire tutti i campi");
        QMessageBox::warning(this, "Errore", "Team non validi, riempire tutti i campi", QMessageBox::Ok);
        return;
    }
    QString path = QFileDialog::getSaveFileName(this, "Salva team", "./", "JSON files *.json");
    if(path.isEmpty()) {
        showStatus("Percorso non valido");
        return;
    }
    updateTeam(ally_team_widget, ally_team);
    updateTeam(enemy_team_widget, enemy_team);
    Json::save(path, ally_team, enemy_team);
    showStatus("Team salvato");
}

void MainWindow::newBattle() {
    if(!(ally_team_widget->isvalid() && enemy_team_widget->isvalid())) {
        showStatus("Team non validi, riempire tutti i campi");
        QMessageBox::warning(this, "Errore", "Team non validi, riempire tutti i campi", QMessageBox::Ok);
        return;
    }
    if(battle) {
        showStatus("Impossibile iniziare una nuova battaglia in questo momento");
        QMessageBox::warning(this, "Errore", "Impossibile iniziare una nuova battaglia in questo momento", QMessageBox::Ok);
        return;
    }
    updateTeam(ally_team_widget, ally_team);
    updateTeam(enemy_team_widget, enemy_team);
    can_save=false;
    battle=true;
    battle_widget=new BattleWidget(ally_team, enemy_team, this);
    stacked_widget->addWidget(battle_widget);
    stacked_widget->setCurrentIndex(1);

    connect(battle_widget, &BattleWidget::close, this, &MainWindow::closeBattle);
    connect(battle_widget, &BattleWidget::endBattle, this, &MainWindow::endBattle);
    
    showStatus("Nuova battaglia iniziata");
}

void MainWindow::closeBattle() {
    if(!battle) {
        showStatus("Nessuna battaglia in corso");
        QMessageBox::warning(this, "Errore", "Nessuna battaglia in corso", QMessageBox::Ok);
        return;
    }
    else {
        QMessageBox::StandardButton confirmation;
        confirmation=QMessageBox::question(this, "Terminare la battaglia?", "La battaglia in corso verrà chiusa. Continuare?", QMessageBox::Yes | QMessageBox::No);
        if(confirmation==QMessageBox::No)
            return;
    }
    clearStack();
    can_save=true;
    battle=false;
    showStatus("Battaglia terminata");
}

void MainWindow::close() {
    QMessageBox::StandardButton confirmation;
    confirmation=QMessageBox::question(this, "Esci?", "Sei sicuro di voler uscire?", QMessageBox::Yes | QMessageBox::No);
    if(confirmation==QMessageBox::Yes)
        QApplication::quit();
}

void MainWindow::showStatus(QString message) {
    statusBar()->showMessage(message);
}

void MainWindow::endBattle(bool win) {
    QMessageBox::StandardButton confirmation;
    if(win) {
        showStatus("Hai vinto");
        confirmation=QMessageBox::question(this, "Vittoria", "Hai vinto!\nVuoi tornare alla schermata di creazione dei team?\n(No=chiudi)", QMessageBox::Yes | QMessageBox::No);
    }
    else {
        showStatus("Hai perso");
        confirmation=QMessageBox::question(this, "Sconfitta", "Hai perso!\nVuoi tornare alla schermata di creazione dei team?\n(No=chiudi)", QMessageBox::Yes | QMessageBox::No);
    }
    if(confirmation==QMessageBox::Yes) {
        clearStack();
        can_save=true;
        battle=false;
    }
    else
        QApplication::quit();
}
