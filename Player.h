 //
// Created by amida on 24/12/2022.
//

#ifndef WET2_MVNE_PLAYER_H
#define WET2_MVNE_PLAYER_H

#include "Team.h"
#include "wet2util.h"


class Player{
    int m_playerId;
    int m_teamId;
    int m_gamesPlayed;
    int m_cards;
    bool m_goalKeeper;
    int m_ability;
    int m_teamPlayedBefore;
    int m_teamPlayed;
    Team* m_team;
    Player* m_father;
    int extra;

    const permutation_t* m_spirit;
    permutation_t m_sum_spirit;
    permutation_t* m_prev_spirit;




public:
    Player(int playerId, int teamId,
           const permutation_t &spirit, int gamesPlayed,
           int ability, int cards, bool goalKeeper);
    ~Player() = default;
    int getId();
    void setTeam(Team* team);
    void setFather(Player* player);
    void setTeamPlayedBefore(int num);
    void setTeamPlayed(int num);
    void setPrevSpirits(const permutation_t &sum_prev_spirits);
    void increaseSpiritSum(const permutation_t &sons_spirit);

    permutation_t getSpirit();
    permutation_t getSpiritSum();
    permutation_t getPrevSpirit();
    void addCards(int amount);
    Player* getFather();
    Team* getTeam();
    int getGamesPlayed();
    int getTeamPlayedBefore();
    int getTeamPlayed();
    int getCards();
};

#endif //WET2_MVNE_PLAYER_H