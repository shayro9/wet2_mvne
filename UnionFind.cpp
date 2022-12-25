//
// Created by amida on 24/12/2022.
//
#include "UnionFind.h"
#define X 2

UnionFind::UnionFind(): players(new Player*[X]), sizes(new int[X]), currSize(0), maxSize(X) {

}

void UnionFind::AddFirstPlayer(Player player, Team* team) {
    if (currSize == maxSize){

    }
    int index = hash(player.getId());
    player.setTeam(team);
    sizes[index] = 1;
    players[index] = &player;

}

void UnionFind::AddPlayer(Player player, Team* team) {
    if (currSize == maxSize){

    }
    int index = hash(player.getId());
    Player* father = team->getRootPlayer();
    player.setFather(father);
    sizes[index]++;
    players[index] = &player;
}

Team *UnionFind::FindTeam(int playerid) {
    int index = hash(playerid);
    //check if exist
    Player* currPlayer = players[index];
    while (currPlayer->getFather()){
        currPlayer = currPlayer->getFather();
    }
    Player* root = currPlayer;
    currPlayer = players[index];
    while (currPlayer->getFather()){
        currPlayer->setFather(root);
    }
    return root->getTeam();

}

void UnionFind::Unite(int playerid1, int playerid2) {
    int index1 = hash(playerid1);
    int index2 = hash(playerid2);
    Player* root1 = players[playerid1];
    Player* root2 = players[playerid2];
    if (sizes[index1] >= sizes[index2]){ // if id1 is bigger than id2
        root2->setTeam(nullptr);
        root2->setFather(root1);
        sizes[index1] += sizes[index2];
    }
    else{
        root1->setTeam(nullptr);
        root1->setFather(root2);
        sizes[index2] += sizes[index1];
    }
}

bool UnionFind::doesExist(int playerId) {
    int index = hash(playerId);
    Player* temp = dynamic_cast<Player*>(players[index]);
    if (temp == nullptr){
        return false;
    }
    return true;
}

Player* UnionFind::getPlayer(int playerId) {
    int index = hash(playerId);
    Player* temp = players[index];
    return temp;
}

Player *UnionFind::findRoot(int playerId) {
    int index = hash(playerId);
    //check if exist
    Player* currPlayer = players[index];
    while (currPlayer->getFather()){
        currPlayer = currPlayer->getFather();
    }
    Player* root = currPlayer;
    currPlayer = players[index];
    while (currPlayer->getFather()){
        currPlayer->setFather(root);
    }
    return root;
}

