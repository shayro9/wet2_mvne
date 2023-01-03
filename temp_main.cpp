#include "worldcup23a2.h"
#include <iostream>

int main(){
    world_cup_t test;

    test.add_team(1);
    test.add_team(2);
    test.add_team(3);
    test.add_team(4);
    test.add_team(5);

    int a1[] = {0,1,2,3,4};
    test.add_player(1,1,a1,1,5,5, true);
    int a2[] = {1,2,3,4,0};
    test.add_player(2,1,a2,5,5,5,false);
    int a3[] = {2,3,4,0,1};
    test.add_player(3,2,a3,9,5,5, true);
    int a4[] = {3,4,0,1,2};
    test.add_player(4,2,a4,3,5,5,false);
    int a5[] = {4,0,1,2,3};
    test.add_player(5,3,a5,2,5,5, true);
    int a6[] = {0,4,2,1,3};
    test.add_player(6,3,a6,6,5,5,false);
    int a7[] = {3,2,1,4,0};
    test.add_player(7,4,a7,10,5,5,false);
    int a8[] = {4,3,2,1,0};
    test.add_player(8,4,a8,10,5,5,false);

    test.buy_team(1,2);
    test.buy_team(3,4);
    test.buy_team(1,3);

    std::cout << "1- " << test.get_partial_spirit(1).ans() << " \n";
    std::cout << "2- " << test.get_partial_spirit(2).ans() << " \n";
    std::cout << "3- " << test.get_partial_spirit(3).ans() << " \n";
    std::cout << "4- " << test.get_partial_spirit(4).ans() << " \n";
    std::cout << "5- " << test.get_partial_spirit(5).ans() << " \n";
    std::cout << "6- " << test.get_partial_spirit(6).ans() << " \n";
    std::cout << "7- " << test.get_partial_spirit(7).ans() << " \n";
    std::cout << "8- " << test.get_partial_spirit(8).ans() << " \n";
    /*
    std::cout << test.num_played_games_for_player(8).ans() << " , ";
    std::cout << test.num_played_games_for_player(9).ans() << " , ";
    std::cout << test.num_played_games_for_player(10).ans() << " , ";
    std::cout << test.num_played_games_for_player(11).ans() << " , ";
    std::cout << test.num_played_games_for_player(12).ans() << " , ";
    std::cout << test.num_played_games_for_player(13).ans() << "\n";
     */

    test.remove_team(3);
    return 0;

}