//
// Created by amida on 24/12/2022.
//
#include "UnionFind.h"
#define X 2

UnionFind::UnionFind(): players(DynamicHash()) {

}

void UnionFind::AddPlayer(Player& player) {
    players.insert(player);
}

Team *UnionFind::FindTeam(int playerid) {

    Player* root = findRoot(playerid);
    if (!root){
        return nullptr;
    }
    return root->getTeam();
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

        root2->setPrevSpirits(root1->getPrevSpirit().inv() * root1->getSpiritSum() * root2->getPrevSpirit());
        root1->increaseSpiritSum(root2->getSpiritSum());
    }
    else{
        root1->setTeam(nullptr);
        root1->setFather(root2);
        root2->setTeam(team1);
        team1->setRootPlayer(root2);
        root1->setTeamPlayedBefore(root2->getGamesPlayed());

        root2->setPrevSpirits(root1->getSpiritSum() * root2->getPrevSpirit());
        root1->setPrevSpirits(root2->getPrevSpirit().inv() * root1->getPrevSpirit());
        root2->increaseSpiritSumFromLeft(root1->getSpiritSum());
    }
    team2->setRootPlayer(nullptr);
    team1->addPlayers(size2);
}

bool UnionFind::doesExist(int playerId) {
    return players.doesExist(playerId);
}

Player* UnionFind::getPlayer(int playerId) {
    return players.getPlayer(playerId);
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
    currPlayer = players.getPlayer(playerId);
    while (currPlayer->getFather() != root && currPlayer->getFather() != nullptr){
        int temp_game_sum = currPlayer->getGamesPlayed();
        currPlayer->increaseGamesPlayed(sum_player_played - currPlayer->getGamesPlayed());
        sum_player_played -= temp_game_sum - currPlayer->getTeamPlayedBefore();
        currPlayer->setTeamPlayedBefore(root->getGamesPlayed());

        permutation_t temp_prev_spirits = currPlayer->getPrevSpirit();
        currPlayer->setPrevSpirits(root->getPrevSpirit().inv() * route_spirit_sum);
        route_spirit_sum = route_spirit_sum * temp_prev_spirits.inv();

        Player* temp = currPlayer->getFather();
        currPlayer->setFather(root);
        currPlayer = temp;
    }
    return root;
}

