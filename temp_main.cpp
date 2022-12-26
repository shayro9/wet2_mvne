#include "RankTree.h"

int main(){
    RankTree<int> tree;
    for (int i = 1; i <= 100; ++i) {
        tree.insert(i);
    }
    for (int i = 1; i <= 100; ++i) {
        if(i % 10 == 0)
            continue;
        tree.remove(i);
    }
    return 0;
}