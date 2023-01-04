//
// Created by amida on 24/12/2022.
//

#ifndef WET2_MVNE_TEAMABILITY_H
#define WET2_MVNE_TEAMABILITY_H

class TeamAbility{

    int m_teamId;
    int m_abilitySum;


public:
    TeamAbility(int teamid);
    TeamAbility() = default;
    TeamAbility(const TeamAbility& p1) = default;
    ~TeamAbility() = default;
    void addAbility(int amount);
    int getId();

    friend bool operator== (const TeamAbility&, const TeamAbility&);
    friend bool operator< (const TeamAbility&, const TeamAbility&);

};

bool operator!= (const TeamAbility&, const TeamAbility&);
bool operator> (const TeamAbility&, const TeamAbility&);
bool operator<= (const TeamAbility&, const TeamAbility&);
bool operator>= (const TeamAbility&, const TeamAbility&);

#endif //WET2_MVNE_TEAMABILITY_H