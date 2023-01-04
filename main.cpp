#include "worldcup23a2.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

std::string str(const permutation_t &perm1)
{
    std::stringstream p1;
    p1 << perm1;
    return p1.str();
}


int main(){

    int basePerm1[5] = {1, 2, 3, 4, 0};
    permutation_t perm1(basePerm1);
    permutation_t perm2(basePerm1);
    int basePerm2[5] = {1, 0, 4, 3, 2};
    permutation_t perm3(basePerm2);

    world_cup_t *obj = new world_cup_t();
    StatusType res = obj->add_team(10);
    (res == StatusType::SUCCESS);
    res = obj->add_player(1, 10, perm1, 1, 1, 1, true);
    (res == StatusType::SUCCESS);

    output_t<permutation_t> resn1 = obj->get_partial_spirit(1);
    (resn1.status() == StatusType::SUCCESS);
    (str(resn1.ans()) == str(perm1));

    res = obj->add_player(2, 10, perm2, 1, 1, 1, false);
    (res == StatusType::SUCCESS);

    output_t<permutation_t> resn2 = obj->get_partial_spirit(2);
    (resn2.status() == StatusType::SUCCESS);
    (str(resn2.ans()) == str(perm1 * perm2));

    res = obj->add_player(3, 10, perm3, 1, 1, 1, false);
    (res == StatusType::SUCCESS);

    output_t<permutation_t> resn3 = obj->get_partial_spirit(3);
    (resn3.status() == StatusType::SUCCESS);
    (str(resn3.ans()) == str(perm1 * perm2 * perm3));

    output_t<permutation_t> resn4 = obj->get_partial_spirit(1);
    (resn4.status() == StatusType::SUCCESS);
    (str(resn4.ans()) == str(perm1));

    output_t<permutation_t> resn5 = obj->get_partial_spirit(2);
    (resn5.status() == StatusType::SUCCESS);
    (str(resn5.ans()) == str(perm1 * perm2));

    res = obj->add_team(20);
    (res == StatusType::SUCCESS);
    res = obj->add_player(4, 20, perm3 * perm2, 1, 1, 1, true);
    (res == StatusType::SUCCESS);

    output_t<permutation_t> resn6 = obj->get_partial_spirit(4);
    (resn6.status() == StatusType::SUCCESS);
    (str(resn6.ans()) == str(perm3 * perm2));

    output_t<permutation_t> resn7 = obj->get_partial_spirit(2);
    (resn7.status() == StatusType::SUCCESS);
    (str(resn7.ans()) == str(perm1 * perm2));

    delete obj;
    return 0;
}
