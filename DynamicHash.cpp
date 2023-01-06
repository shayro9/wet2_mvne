//
// Created by amida on 25/12/2022.
//
#include "DynamicHash.h"

int DynamicHash::hashFunc(int playerId) {
    return playerId % m_tableSize;
}

Player *DynamicHash::getPlayer(int playerId) {
    int index = hashFunc(playerId);
    LNode<Player>* iter = m_playersArray[index].getHead();
    while (iter){
        if (iter->m_data->getId() == playerId){
            return iter->m_data;
        }
        else{
            iter = iter->m_next;
        }
    }
    return nullptr;
}

void DynamicHash::insert(Player &player) {
    if (m_tableSize == m_currSize + 1){
        try
        {
            int old_tableSize = m_tableSize;
            m_tableSize = m_tableSize*2;
            List<Player>* new_playersArray = new List<Player>[m_tableSize];
            for (int i = 0; i < old_tableSize; i++){
                LNode<Player>* iter = m_playersArray[i].getHead();
                while (iter){
                    Player* temp = iter->m_data;
                    new_playersArray[hashFunc(temp->getId())].append(*temp);
                    iter = iter->m_next;
                }
            }
            ClearPastArray(old_tableSize);
            m_playersArray = new_playersArray;
        }
        catch (...)
        {
            // table_size = old_table_size
            //delete[] new_playersArray;
            //add
        }
    }
    int index = hashFunc(player.getId());
    m_playersArray[index].append(player);
    m_currSize++;
}

DynamicHash::DynamicHash() : m_playersArray(new List<Player>[10]), m_tableSize(10), m_currSize(0){

}

bool DynamicHash::doesExist(int id) {
    if (!getPlayer(id)){
        return false;
    }
    return true;
}

DynamicHash::~DynamicHash() {
    delete[] m_playersArray;
}

void DynamicHash::ClearPastArray(int past_size) {
    for (int i = 0; i < past_size; ++i) {
        if(m_playersArray[i].getHead())
            m_playersArray[i].deleteNodes();
    }
    delete[] m_playersArray;
}



