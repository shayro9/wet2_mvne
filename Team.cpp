//
// Created by amida on 24/12/2022.
//
#include "Team.h"

Team::Team(int teamId): m_teamId(teamId), m_points(0), m_abilitySum(0), m_rootPlayer(nullptr), m_teamAbility(nullptr), m_isValid(
        false), m_gamesPlayed(0){

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