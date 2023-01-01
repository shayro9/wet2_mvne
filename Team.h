//
// Created by amida on 24/12/2022.
//

#ifndef WET2_MVNE_TEAM_H
#define WET2_MVNE_TEAM_H

//#include "Player.h"
#include "TeamAbility.h"

class Player;

class Team{
    int m_teamId;
    int m_points;
    int m_abilitySum;
    Player* m_rootPlayer;
    TeamAbility* m_teamAbility;
    bool m_isValid;
    int m_gamesPlayed;
    int m_numOfPlayers;



public:
    Team(int teamId);
    Team() = default;
    ~Team() = default;
    Player* getRootPlayer();
    void setRootPlayer(Player* player);
    void addAbility(int amount);
    void SetTeamAbilityPointer(TeamAbility* teamAbility);
    void PlayGame(int points);
    TeamAbility* getTeamAbilityPointer();
    void makeValid();
    bool isValid();
    int getPoints();
    int getAbility();
    int getTeamPlayed();
    void addPlayers(int amount);

    friend bool operator== (const Team&, const Team&);
    friend bool operator< (const Team&, const Team&);


};



bool operator!= (const Team&, const Team&);
bool operator>= (const Team&, const Team&);
bool operator> (const Team&, const Team&);
bool operator<= (const Team&, const Team&);

#endif //WET2_MVNE_TEAM_H