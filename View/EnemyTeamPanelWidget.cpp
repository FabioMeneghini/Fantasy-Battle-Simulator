#include "EnemyTeamPanelWidget.h"
#include "CharacterInfoWidget.h"
#include "../Team/TeamObserver.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QString>
#include <QVector>
#include <QLabel>
#include <iostream>

EnemyTeamPanelWidget::EnemyTeamPanelWidget(Team& t, QWidget* p): QWidget(p), team(t) {
    layout=new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    info=new CharacterInfoWidget(t.search(0));
    info->show();
    layout->addWidget(info);

    for(auto it=t.begin(); it!=t.end(); ++it) {
        QPixmap image(QString::fromStdString((*it)->getArtworkPath()));
        QLabel* artwork=new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        artwork_vector.push_back(artwork);
        layout->addWidget(artwork);
    }

    team.registerObserver(this);
}

void EnemyTeamPanelWidget::notify(Team& team) {
    team.search(team.getAliveCount()-1)->removeObserver(info); //rimuove l'Observer info dal Character che è appena stato spostato in ultima posizione
    layout->removeWidget(info);
    delete info;

    for(auto it=artwork_vector.begin(); it!=artwork_vector.end(); ++it) {
        layout->removeWidget(*it);
        delete *it;
    }
    artwork_vector.resize(0);

    info=new CharacterInfoWidget(team.search(0));
    info->show();
    layout->addWidget(info);
    
    for(auto it=team.begin(); it!=team.end(); ++it) {
        QString path;
        if((*it)->isAlive())
            path=QString::fromStdString((*it)->getArtworkPath());
        else
            path=":Assets/skull.png";
        QPixmap image(path);
        QLabel* artwork=new QLabel();
        artwork->setPixmap(image.scaledToHeight(256));
        artwork_vector.push_back(artwork);
        layout->addWidget(artwork);
    }
}