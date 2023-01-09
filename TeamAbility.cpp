//
// Created by amida on 24/12/2022.
//


#include "TeamAbility.h"

TeamAbility::TeamAbility(int teamid): m_teamId(teamid), m_abilitySum(0){

}

bool operator==(const TeamAbility &team1, const TeamAbility &team2) {
    if (team1.m_teamId == team2.m_teamId){
        return true;
    }
    return false;
}

bool operator<(const TeamAbility &team1, const TeamAbility &team2) {
    if (team1.m_abilitySum < team2.m_abilitySum){
        return true;
    }
    else if (team1.m_abilitySum > team2.m_abilitySum){
        return false;
    }
    else{
        if (team1.m_teamId < team2.m_teamId){
            return true;
        }
        return false;
    }
}

void TeamAbility::addAbility(int amount) {
    m_abilitySum += amount;
}

int TeamAbility::getId() {
    return m_teamId;
}

bool operator!=(const TeamAbility &team1, const TeamAbility &team2) {
    return !(team1 == team2);
}

bool operator>(const TeamAbility &team1, const TeamAbility &team2) {
    return team2 < team1;
}

bool operator<=(const TeamAbility &team1, const TeamAbility &team2) {
    return team1 < team2 || team1 == team2;
}

bool operator>=(const TeamAbility &team1, const TeamAbility &team2) {
    return team2 <= team1;
}

