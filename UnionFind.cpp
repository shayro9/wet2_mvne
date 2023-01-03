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
    /*int index = hash(player.getId());
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
        team1->addPlayers(size2);
    }
    else{
        root1->setTeam(nullptr);
        root1->setFather(root2);
        team2->addPlayers(size1);
    }
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
    int sum_team_played_before = 0;
    permutation_t route_spirit_sum = permutation_t().neutral();
    while (currPlayer->getFather()){
        currPlayer = currPlayer->getFather();
        sum_team_played_before += currPlayer->getTeamPlayed();

       // route_spirit_sum = permutation_t(route_spirit_sum * currPlayer->getPrevSpirit());
        route_spirit_sum = route_spirit_sum * currPlayer->getPrevSpirit();
    } 
    Player* root = currPlayer;
    int new_games_played_before = currPlayer->getGamesPlayed() - sum_team_played_before;
    currPlayer = players.getPlayer(playerId);
    while (currPlayer->getFather() != root && currPlayer->getFather() != nullptr){
        currPlayer->setTeamPlayedBefore(new_games_played_before);
        currPlayer->setTeamPlayed(0);
        new_games_played_before -= currPlayer->getTeamPlayed();

        currPlayer->setPrevSpirits(route_spirit_sum);
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

