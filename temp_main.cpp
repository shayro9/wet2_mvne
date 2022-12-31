#include "worldcup23a2.h"

int main(){
    world_cup_t test;
    test.add_team(1);
    test.add_team(2);
    test.add_team(3);
    test.add_team(4);
    test.add_team(5);



    for (int i = 0; i < 20; ++i) {
        int a[5] = {i%5,(i+1)%5,(i+2)%5,(i+3)%5,(i+4)%5};
        test.add_player(i,i%5 + 1,permutation_t(a),i*7,i*i,4*i, false);
    }

    test.remove_team(2);

    return 0;
}