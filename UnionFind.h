//
// Created by amida on 24/12/2022.
//

#ifndef WET2_MVNE_UNIONFIND_H
#define WET2_MVNE_UNIONFIND_H

#endif //WET2_MVNE_UNIONFIND_H

#include "Player.h"

class UnionFind{
    Player** players;
    int* sizes;
    int maxSize;
    int currSize;


public:
    UnionFind();
    ~UnionFind();
    void AddFirstPlayer(Player player, Team* team);     //create new set
    void AddPlayer(Player player, Team* team);          //add player to existing set
    Team* FindTeam(int playerid);
    Player* findRoot(int playerId);
    void Unite(int playerid1, int playerid2);
    bool doesExist(int playerId);
    Player* getPlayer(int playerId);


};