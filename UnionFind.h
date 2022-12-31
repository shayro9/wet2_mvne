//
// Created by amida on 24/12/2022.
//

#ifndef WET2_MVNE_UNIONFIND_H
#define WET2_MVNE_UNIONFIND_H

#include "Player.h"
#include "DynamicHash.h"

class UnionFind{
    DynamicHash players;
  //  Player** players;
   // int* sizes;
 //   int maxSize;
  //  int currSize;


public:
    UnionFind();
    ~UnionFind() = default;
   // void AddFirstPlayer(Player player, Team* team);     //create new set
    void AddPlayer(Player player);          //add player to existing set
    Team* FindTeam(int playerid);
    Player* findRoot(int playerId);
    void Unite(int playerid1, int playerid2);
    bool doesExist(int playerId);
    Player* getPlayer(int playerId);


};

#endif //WET2_MVNE_UNIONFIND_H