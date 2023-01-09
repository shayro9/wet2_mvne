//
// Created by amida on 25/12/2022.
//

#ifndef WET2_MVNE_LIST_H
#define WET2_MVNE_LIST_H

template<class T>
struct LNode {
    T* m_data;
    LNode *m_next;
    LNode *m_prev;
};


template<class T>
class List{
private:
    LNode<T>* m_head;
    LNode<T>* m_tail;
    int m_size;
public:
    List();
    ~List();
    void deleteNodes();
    List<T>& operator=(const List<T>& l) = delete;

    LNode<T>* getHead();
    void append(T& data);

};

template<class T>
List<T>::List() : m_size(0) {
    m_tail = nullptr;
    m_head = nullptr;
}

template<class T>
List<T>::~List() {
    if(m_head) {
        LNode<T> *curr_node = m_head->m_next;
        while (curr_node) {
            delete (curr_node->m_prev->m_data);
            delete(curr_node->m_prev);
            curr_node = curr_node->m_next;
        }
        delete(m_tail->m_data);
        delete(m_tail);
    }
}

template<class T>
LNode<T> *List<T>::getHead() {
    return m_head;
}

template<class T>
void List<T>::append(T& data) {
    LNode<T>* temp = new LNode<T>();
    temp->m_data = &data;
    temp->m_next = nullptr;
    if(m_tail != nullptr)
        m_tail->m_next = temp;
    else
        m_head = temp;
    temp->m_prev = m_tail;
    m_tail = temp;
    m_size++;
}

template<class T>
void List<T>::deleteNodes() {
    if(m_head) {
        LNode<T> *curr_node = m_head->m_next;
        while (curr_node) {
            delete(curr_node->m_prev);
            curr_node = curr_node->m_next;
        }
        delete(m_tail);
    }
    m_head = nullptr;
}

#endif //WET2_MVNE_LIST_H