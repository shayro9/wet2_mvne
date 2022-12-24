//
// Created by amida on 24/12/2022.
//

#ifndef WET2_MVNE_PLAYER_H
#define WET2_MVNE_PLAYER_H

#endif //WET2_MVNE_PLAYER_H

#include "Team.h"
#include "wet2util.h"


class Player{
    int m_playerId;
    int m_teamId;
    int m_gamesPlayed;
    int m_cards;
    bool m_goalKeeper;
    int m_ability;
    Team* m_team;
    Player* m_father;
    int extra;
    const permutation_t& m_spirit;



public:
    Player(int playerId, int teamId,
           const permutation_t &spirit, int gamesPlayed,
           int ability, int cards, bool goalKeeper);
    ~Player();
    int getId();
    void setTeam(Team* team);
    void setFather(Player* player);
    Player* getFather();
    Team* getTeam();
};