//
// Created by amida on 25/12/2022.
//
#include "DynamicHash.h"

int DynamicHash::hashFunc(int playerId) {
    return playerId % m_tableSize;
}

Player *DynamicHash::getPlayer(int playerId) {
    int index = hashFunc(playerId);
    LNode<Player>* iter = m_playersArray->getHead();
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

void DynamicHash::insert(Player player) {
    if (m_tableSize == m_currSize + 1){
        try
        {
            List<Player>* new_playersArray = new List<Player>[m_tableSize*2];
            for (int i = 0; i <= m_tableSize; i++){
                LNode<Player>* iter = m_playersArray[i].getHead();
                while (iter){
                    Player* temp = iter->m_data;
                    new_playersArray[hashFunc(temp->getId())].append(player);
                }
            }
            delete[] m_playersArray;
            m_playersArray = new_playersArray;
            m_tableSize *=2;
        }
        catch (...)
        {
            delete[] new_playersArray;
            //add
        }
    }
    int index = hashFunc(player.getId());
    m_playersArray->append(player);
    m_currSize++;
}

DynamicHash::DynamicHash() :m_tableSize(10), m_currSize(0), m_playersArray(new List<Player>[10]){

}

bool DynamicHash::doesExist(int id) {
    int index = hashFunc(id);
    if (!getPlayer(id)){
        return false;
    }
    return true;
}



