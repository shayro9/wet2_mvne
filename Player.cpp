//
// Created by amida on 24/12/2022.
//
#include "Player.h"

int Player::getId() {
    return m_playerId;
}

void Player::setTeam(Team* team) {
    m_team = team;
}

Player::Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards,
               bool goalKeeper): m_playerId(playerId), m_teamId(teamId), m_spirit(spirit), m_gamesPlayed(gamesPlayed), m_ability(ability), m_cards(cards), m_goalKeeper(goalKeeper),
               m_team(nullptr), m_father(nullptr){

}

void Player::setFather(Player *player) {
    m_father = player;
}

Player *Player::getFather() {
    return m_father;
}

Team *Player::getTeam() {
    return m_team;
}

