//
// Created by amida on 24/12/2022.
//
#include "UnionFind.h"
#define X 2

UnionFind::UnionFind(): players(DynamicHash()) {

}
/*
void UnionFind::AddFirstPlayer(Player player, Team* team) {
    if (currSize == maxSize){

    }
    players.insert(player);
    int index = hash(player.getId());
    player.setTeam(team);
    sizes[index] = 1;
    players[index] = &player;

}
*/
void UnionFind::AddPlayer(Player& player) {
    //if (currSize == maxSize){

    //}
    players.insert(player);
    /*
    int index = hash(player.getId());
    Player* father = team->getRootPlayer();
    player.setFather(father);
    sizes[index]++;
    players[index] = &player;*/
}

Team *UnionFind::FindTeam(int playerid) {

    Player* root = findRoot(playerid);
    if (!root){
        return nullptr;
    }
    return root->getTeam();

    /*
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
*/
}

void UnionFind::Unite(int playerid1, int playerid2) {
    Player* root1 = players.getPlayer(playerid1);
    Player* root2 = players.getPlayer(playerid2);
    Team* team1 = root1->getTeam();
    Team* team2 = root2->getTeam();
    int size1 = team1->getSize();
    int size2 = team2->getSize();
    if (size1 >= size2){
        root2->setTeam(nullptr);
        root2->setFather(root1);
        root2->setTeamPlayedBefore(root1->getGamesPlayed());
        root2->setPrevSpirits(root1->getSpiritSum() * root2->getPrevSpirit().inv());
        root1->increaseSpiritSum(root2->getSpiritSum());
    }
    else{
        root1->setTeam(nullptr);
        root1->setFather(root2);
        root2->setTeam(team1);
        team1->setRootPlayer(root2);
        root1->setTeamPlayedBefore(root2->getGamesPlayed());

        root2->setPrevSpirits(root1->getSpiritSum() * root2->getPrevSpirit());
        root1->setPrevSpirits(root2->getPrevSpirit().inv());
        root2->increaseSpiritSumFromLeft(root1->getSpiritSum());
    }
    team2->setRootPlayer(nullptr);
    team1->addPlayers(size2);
    /*
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
    }*/
}

bool UnionFind::doesExist(int playerId) {
    return players.doesExist(playerId);
    /*int index = hash(playerId);
    Player* temp = dynamic_cast<Player*>(players[index]);
    if (temp == nullptr){
        return false;
    }
    return true;*/
}

Player* UnionFind::getPlayer(int playerId) {
    return players.getPlayer(playerId);
    /*
    int index = hash(playerId);
    Player* temp = players[index];
    return temp;*/
     }

Player *UnionFind::findRoot(int playerId) {
    if (!players.doesExist(playerId)){
        return nullptr;
    }
    Player* currPlayer = players.getPlayer(playerId);
    int sum_player_played = currPlayer->getGamesPlayed() - currPlayer->getTeamPlayedBefore();
    permutation_t route_spirit_sum = currPlayer->getPrevSpirit();
    while (currPlayer->getFather()){
        currPlayer = currPlayer->getFather();
        sum_player_played += currPlayer->getGamesPlayed() - currPlayer->getTeamPlayedBefore();

        route_spirit_sum = currPlayer->getPrevSpirit() * route_spirit_sum ;
    } 
    Player* root = currPlayer;
    //route_spirit_sum = permutation_t(route_spirit_sum * root->getPrevSpirit().inv());
    currPlayer = players.getPlayer(playerId);
    while (currPlayer->getFather() != root && currPlayer->getFather() != nullptr){
        currPlayer->increaseGamesPlayed(sum_player_played - currPlayer->getGamesPlayed());
        currPlayer->setTeamPlayedBefore(root->getGamesPlayed());

        currPlayer->setPrevSpirits(root->getPrevSpirit().inv() * route_spirit_sum);
        route_spirit_sum = permutation_t(route_spirit_sum * (currPlayer->getPrevSpirit().inv()));

        Player* temp = currPlayer->getFather();
        currPlayer->setFather(root);
        currPlayer = temp;
    }
    return root;
    /*
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
     */
}

