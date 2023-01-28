#ifndef JSON_H
#define JSON_H

#include <QString>
#include "../Team/Team.h"

class Json {
private:
    static void loadTeam(Team& team, const QJsonArray& json_team);
public:
    Json()=delete;
    Json(const Json&)=delete;
    static void save(const QString& path, const Team& ally_team, const Team& enemy_team);
    static void load(const QString& path, Team& ally_team, Team& enemy_team);
};

#endif