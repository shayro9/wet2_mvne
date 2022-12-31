//
// Created by amida on 25/12/2022.
//

#ifndef WET2_MVNE_DYNAMICHASH_H
#define WET2_MVNE_DYNAMICHASH_H

#include "Player.h"
#include "List.h"


class DynamicHash{

    List<Player>* m_playersArray;
    int m_tableSize;
    int m_currSize;


public:
    DynamicHash();
    ~DynamicHash();
    int hashFunc(int num);
    Player* getPlayer(int num);
    void insert(Player player);
    bool doesExist(int id);



};

#endif //WET2_MVNE_DYNAMICHASH_H