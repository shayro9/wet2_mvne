//
// Created by amida on 24/12/2022.
//

#ifndef WET2_MVNE_TEAM_H
#define WET2_MVNE_TEAM_H

#endif //WET2_MVNE_TEAM_H
//#include "Player.h"

class Player;

class Team{
    int m_teamId;
    int m_points;
    int abilitySum;
    Player* m_rootPlayer;




public:
    Team(int teamId);
    ~Team();
    Player* getRootPlayer();




};