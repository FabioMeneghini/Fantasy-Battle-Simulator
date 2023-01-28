#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QJsonValue>
#include "JsonVisitor.h"
#include "Json.h"
#include "../Team/Team.h"
#include "../Character/Warrior.h"
#include "../Character/Wizard.h"
#include "../Character/Healer.h"
#include "../Character/Skeleton.h"
#include "../Character/Goblin.h"

void Json::save(const QString& path, const Team& ally_team, const Team& enemy_team) {
    QJsonArray json_items;
    QJsonArray json_ally_team;
    QJsonArray json_enemy_team;
    JsonVisitor json_visitor;
    //salva sullo stesso file json prima il team degli alleati e poi quello dei nemici, su due QJsonArray differenti
    for(auto it=ally_team.begin(); it!=ally_team.end(); ++it) {
        (*it)->accept(json_visitor);
        json_ally_team.push_back(json_visitor.getContent());
    }
    for(auto it=enemy_team.begin(); it!=enemy_team.end(); ++it) {
        (*it)->accept(json_visitor);
        json_enemy_team.push_back(json_visitor.getContent());
    }
    json_items.push_back(json_ally_team);
    json_items.push_back(json_enemy_team);
    if(!path.isEmpty()) {
        QJsonDocument document(json_items);
        QFile json_file(path);
        json_file.open(QFile::WriteOnly);
        json_file.write(document.toJson());
        json_file.close();
    }
}

void Json::loadTeam(Team& team, const QJsonArray& json_team) {
    Character* character;
    for(auto it=json_team.begin(); it!=json_team.end(); ++it) {
        QJsonObject object=it->toObject();
        if(object.value("type").toString().compare("warrior")==0) {
            character=new Warrior(object.value("name").toString().toStdString(),
                                  static_cast<unsigned int>(object.value("max_hp").toInt()),
                                  static_cast<unsigned int>(object.value("power").toInt()),
                                  static_cast<unsigned int>(object.value("level").toInt()),
                                  ":Assets/warrior.png");
        }
        else if(object.value("type").toString().compare("wizard")==0) {
            character=new Wizard(object.value("name").toString().toStdString(),
                                  static_cast<unsigned int>(object.value("max_hp").toInt()),
                                  static_cast<unsigned int>(object.value("power").toInt()),
                                  static_cast<unsigned int>(object.value("level").toInt()),
                                  ":Assets/wizard.png");
        }
        else if(object.value("type").toString().compare("healer")==0) {
            character=new Healer(object.value("name").toString().toStdString(),
                                  static_cast<unsigned int>(object.value("max_hp").toInt()),
                                  static_cast<unsigned int>(object.value("power").toInt()),
                                  static_cast<unsigned int>(object.value("level").toInt()),
                                  ":Assets/healer.png");
        }
        else if(object.value("type").toString().compare("skeleton")==0) {
            character=new Skeleton(object.value("name").toString().toStdString(),
                                  static_cast<unsigned int>(object.value("max_hp").toInt()),
                                  static_cast<unsigned int>(object.value("power").toInt()),
                                  static_cast<unsigned int>(object.value("armor").toInt()),
                                  ":Assets/skeleton.png");
        }
        //else if(json_object.value("type").toString().compare("goblin")==0) {
        else {
            character=new Goblin(object.value("name").toString().toStdString(),
                                  static_cast<unsigned int>(object.value("max_hp").toInt()),
                                  static_cast<unsigned int>(object.value("power").toInt()),
                                  static_cast<unsigned int>(object.value("armor").toInt()),
                                  ":Assets/goblin.png");
        }
        team.insertBack(character);
    }
}

void Json::load(const QString& path, Team& ally_team, Team& enemy_team) {
    QFile json_file(path);
    json_file.open(QFile::ReadOnly);
    QByteArray data=json_file.readAll();
    json_file.close();

    QJsonDocument document=QJsonDocument::fromJson(data);
    QJsonArray json_items=document.array();
    QJsonArray json_ally_team=json_items[0].toArray();
    QJsonArray json_enemy_team=json_items[1].toArray();

    ally_team=Team(json_ally_team.size());
    enemy_team=Team(json_enemy_team.size());

    loadTeam(ally_team, json_ally_team);
    loadTeam(enemy_team, json_enemy_team);
}