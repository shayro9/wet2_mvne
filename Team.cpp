//
// Created by amida on 24/12/2022.
//
#include "Team.h"

Team::Team(int teamId): m_teamId(teamId), m_points(0), m_abilitySum(0), m_rootPlayer(nullptr), m_teamAbility(nullptr),
    m_isValid(false), m_gamesPlayed(0), m_numOfPlayers(0), m_teamSpirit(permutation_t().neutral()){

}

bool operator== (const Team& t1, const Team& t2){
    if(t1.m_teamId == t2.m_teamId)
        return true;
    return false;
}

bool operator< (const Team& t1, const Team& t2){
    if(t1.m_teamId < t2.m_teamId)
        return true;
    return false;
}

void Team::SetTeamAbilityPointer(TeamAbility *teamAbility) {
    m_teamAbility = teamAbility;
}

TeamAbility *Team::getTeamAbilityPointer() {
    return m_teamAbility;
}

void Team::setRootPlayer(Player *player) {
    m_rootPlayer = player;
}

void Team::addAbility(int amount) {
    m_abilitySum += amount;
}

void Team::makeValid() {
    m_isValid = true;
}

bool Team::isValid() {
    return m_isValid;
}

int Team::getPoints() {
    return m_points;
}

int Team::getAbility() {
    return m_abilitySum;
}

int Team::getTeamPlayed() {
    return m_gamesPlayed;
}

Player *Team::getRootPlayer() {
    return m_rootPlayer;
}

void Team::addPlayers(int amount) {
    m_numOfPlayers += amount;
}

permutation_t Team::getTeamSpirit() {
    return m_teamSpirit;
}

void Team::setTeamSpirit(const permutation_t& spirit) {
    m_teamSpirit = m_teamSpirit * spirit;
}

void Team::addGamesPlayed(int amount) {
    m_gamesPlayed += amount;
}

void Team::addPoints(int amount) {
    m_points += amount;
}

int Team::getSize() {
    return m_numOfPlayers;
}

void Team::BuyWhenEmpty(Team *bought) {
    m_points = bought->m_points;
    m_abilitySum = bought->m_abilitySum;
    m_rootPlayer = bought->m_rootPlayer;
    m_isValid = bought->m_isValid;
    m_gamesPlayed = bought->m_gamesPlayed;
    m_numOfPlayers = bought->m_numOfPlayers;
    //m_teamAbility->addAbility(bought->m_abilitySum);
}

int Team::getId() {
    return m_teamId;
}


bool operator> (const Team& t1, const Team& t2){
    return t2 < t1;
}

bool operator!= (const Team& t1, const Team& t2)
{
    return !(t1==t2);
}

bool operator<=(const Team& t1, const Team& t2)
{
    return t1 < t2 || t1 == t2;
}

bool operator>=(const Team& t1, const Team& t2)
{
    return t2 <= t1;
}