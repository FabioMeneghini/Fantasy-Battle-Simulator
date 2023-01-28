#ifndef TEAM_OBSERVER_H
#define TEAM_OBSERVER_H

#include "Team.h"
class Team;

class TeamObserver {
public:
    virtual ~TeamObserver()=default;
    virtual void notify(Team& team)=0;
};

#endif