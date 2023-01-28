#include "AllyTeamPanelWidget.h"
#include "CharacterInfoWidget.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>
#include <QString>
#include <QVector>
#include <QLabel>

AllyTeamPanelWidget::AllyTeamPanelWidget(Team& t, QWidget* p): QWidget(p), team(t) {
    layout=new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QGridLayout* buttons=new QGridLayout();
    layout->addLayout(buttons);

    QPushButton* attack=new QPushButton("Azione");
    attack->setFixedHeight(50);
    buttons->addWidget(attack, 0, 0, 1, 2);
    QPushButton* _switch=new QPushButton("Cambia personaggio");
    _switch->setFixedHeight(50);
    buttons->addWidget(_switch, 1, 0, 1, 1);
    QPushButton* close=new QPushButton("Arrenditi");
    close->setFixedHeight(50);
    buttons->addWidget(close, 1, 1, 1, 1);

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

    //segnali
    connect(attack, &QPushButton::pressed, this, &AllyTeamPanelWidget::attack);
    connect(_switch, &QPushButton::pressed, this, &AllyTeamPanelWidget::switchCharacter);
    connect(close, &QPushButton::pressed, this, &AllyTeamPanelWidget::close);

    team.registerObserver(this);
}

void AllyTeamPanelWidget::notify(Team& team) {
    team.search(team.getAliveCount()-1)->removeObserver(info); //rimuove l'Observer info dal Character che è appena stato spostato in ultima posizione
    layout->removeWidget(info);
    delete info;
    info=new CharacterInfoWidget(team.search(0));
    info->show();
    layout->addWidget(info);

    for(auto it=artwork_vector.begin(); it!=artwork_vector.end(); ++it) {
        layout->removeWidget(*it);
        delete *it;
    }
    artwork_vector.resize(0);
    
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