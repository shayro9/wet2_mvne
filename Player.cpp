//
// Created by amida on 24/12/2022.
//
#include "Player.h"

Player::Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper):
    m_playerId(playerId), m_teamId(teamId),
    m_cards(cards), m_goalKeeper(goalKeeper), m_ability(ability), m_gamesPlayed(gamesPlayed),
    m_teamPlayedBefore(0), m_teamPlayed(0), m_team(nullptr), m_father(nullptr),
    m_sum_spirit(spirit), m_prev_spirit(nullptr)
{
    m_spirit = new permutation_t(spirit);
}

int Player::getId() {
    return m_playerId;
}

void Player::setTeam(Team* team) {
    m_team = team;
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

Player::~Player() {
    delete(m_spirit);
    delete(m_prev_spirit);
}

Player::Player(const Player &p1) {
    m_playerId = p1.m_playerId;
    m_teamId = p1.m_teamId;
    m_cards = p1.m_cards;
    m_goalKeeper = p1.m_goalKeeper;
    m_ability = p1.m_ability;
    m_gamesPlayed = p1.m_gamesPlayed;
    m_teamPlayedBefore = p1.m_teamPlayedBefore;
    m_teamPlayed = p1.m_teamPlayed;
    m_team = p1.m_team;
    m_father = p1.m_father;

    m_spirit = new permutation_t(*p1.m_spirit);
    m_sum_spirit = p1.m_sum_spirit;
    m_prev_spirit = new permutation_t(*p1.m_prev_spirit);
}

void Player::increaseSpiritSumFromLeft(const permutation_t &sons_spirit) {
    permutation_t* temp = new permutation_t(sons_spirit * m_sum_spirit);
    m_sum_spirit = permutation_t(*temp);
    delete(temp);
}



