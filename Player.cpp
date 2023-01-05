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

Player::Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper):
    m_playerId(playerId), m_teamId(teamId),
    m_cards(cards), m_goalKeeper(goalKeeper), m_ability(ability), m_gamesPlayed(gamesPlayed),
    m_teamPlayedBefore(0), m_teamPlayed(0), m_team(nullptr), m_father(nullptr),
    m_sum_spirit(spirit), m_prev_spirit(nullptr)
{
    m_spirit = new permutation_t(spirit);
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

void Player::setTeamPlayedBefore(int num) {
    m_teamPlayedBefore = num;
}

void Player::setTeamPlayed(int num) {
    m_teamPlayed = num;
}

int Player::getGamesPlayed() {
    return m_gamesPlayed;
}

int Player::getTeamPlayedBefore() {
    return m_teamPlayedBefore;
}

int Player::getTeamPlayed() {
    return m_teamPlayed;
}

void Player::addCards(int amount) {
    m_cards += amount;
}

int Player::getCards() {
    return m_cards;
}

permutation_t Player::getSpirit() {
    return *m_spirit;
}

permutation_t Player::getSpiritSum() {
    return m_sum_spirit;
}

void Player::setPrevSpirits(const permutation_t &sum_prev_spirits) {
    delete(m_prev_spirit);
    m_prev_spirit = new permutation_t(sum_prev_spirits);
}

void Player::increaseSpiritSum(const permutation_t &sons_spirit) {
    permutation_t* temp = new permutation_t(m_sum_spirit * sons_spirit);
    m_sum_spirit = permutation_t(*temp);
    delete(temp);
}

permutation_t Player::getPrevSpirit() {
    return *m_prev_spirit;
}

void Player::increaseGamesPlayed(int amount) {
    m_gamesPlayed += amount;
}



