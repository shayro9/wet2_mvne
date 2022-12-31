#include "worldcup23a2.h"

int main(){
    world_cup_t test;
    test.add_team(1);
    test.add_team(2);
    test.add_team(3);
    test.add_team(4);
    test.add_team(5);



    for (int i = 0; i < 19; ++i) {
        int a[5] = {i%5,(i+1)%5,(i+2)%5,(i+3)%5,(i+4)%5};
        test.add_player(i,i%5 + 1,permutation_t(a),i*7,i*i,4*i, false);
    }

    int b[5] = {0, 1, 2, 3, 4};
    int x = test.get_ith_pointless_ability(4).ans();
    //test.remove_team(2);
    test.add_player(30, 3, permutation_t(b), 6, 5, 5, true);
    int y = test.get_player_cards(10).ans();
    int y2 = test.get_player_cards(30).ans();
    test.add_player_cards(30, 5);
    int y3 = test.get_player_cards(30).ans();
    return 0;

}