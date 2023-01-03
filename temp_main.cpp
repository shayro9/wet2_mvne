#include "worldcup23a2.h"
#include <iostream>

int main(){
    world_cup_t test;

    test.add_team(1);
    test.add_team(2);
    test.add_team(3);
    test.add_team(4);
    test.add_team(5);

    int a[] = {0,1,2,3,4};
    test.add_player(1,1,a,1,5,5, true);
    test.add_player(2,1,a,5,5,5,false);
    test.add_player(3,2,a,9,5,5, true);
    test.add_player(4,2,a,3,5,5,false);
    test.add_player(5,3,a,2,5,5, true);
    test.add_player(6,3,a,6,5,5,false);
    test.add_player(7,3,a,10,5,5,false);
    test.add_player(8,4,a,1,5,5,true);
    test.add_player(9,4,a,2,5,5,false);
    test.add_player(10,4,a,3,5,5,false);
    test.add_player(11,5,a,4,5,5,true);
    test.add_player(12,5,a,5,5,5,false);
    test.add_player(13,5,a,6,5,5,false);

    test.play_match(1,3);
    test.play_match(1,3);
    test.play_match(1,3);
    test.play_match(1,3);
    test.play_match(1,3);

    test.play_match(2,3);
    test.play_match(2,3);

    test.play_match(4,5);
    test.play_match(4,5);
    test.play_match(4,5);

    test.play_match(2,5);
    test.play_match(2,5);
    test.play_match(2,5);
    test.play_match(2,5);

    test.buy_team(1,2);
    test.buy_team(2,3);

    test.play_match(1,3);
    test.play_match(1,3);
    test.play_match(1,4);
    test.play_match(1,4);
    test.play_match(1,5);
    test.play_match(1,5);

    test.buy_team(3,1);
    test.buy_team(4,5);

    test.play_match(3,4);
    test.play_match(3,4);

    test.buy_team(3,4);

    std::cout << test.num_played_games_for_player(1).ans() << " , ";
    std::cout << test.num_played_games_for_player(2).ans() << " , ";
    std::cout << test.num_played_games_for_player(3).ans() << " , ";
    std::cout << test.num_played_games_for_player(4).ans() << " , ";
    std::cout << test.num_played_games_for_player(5).ans() << " , ";
    std::cout << test.num_played_games_for_player(6).ans() << " , ";
    std::cout << test.num_played_games_for_player(7).ans() << " , ";
    std::cout << test.num_played_games_for_player(8).ans() << " , ";
    std::cout << test.num_played_games_for_player(9).ans() << " , ";
    std::cout << test.num_played_games_for_player(10).ans() << " , ";
    std::cout << test.num_played_games_for_player(11).ans() << " , ";
    std::cout << test.num_played_games_for_player(12).ans() << " , ";
    std::cout << test.num_played_games_for_player(13).ans() << "\n";

    test.remove_team(3);


    /*
    for (int i = 0; i < 19; ++i) {
        int a[5] = {i%5,(i+1)%5,(i+2)%5,(i+3)%5,(i+4)%5};
        test.add_player(i,i%5 + 1,permutation_t(a),i*7,i*i,4*i, false);
    }

    int b[5] = {0, 1, 2, 3, 4};
    int x = test.get_ith_pointless_ability(4).ans();
    test.remove_team(2);


    test.add_player(30, 3, permutation_t(b), 6, 5, 5, true);
    int y = test.get_player_cards(10).ans();
    int y2 = test.get_player_cards(30).ans();
    test.add_player_cards(30, 5);
    int y3 = test.get_player_cards(30).ans();*/
    return 0;

}