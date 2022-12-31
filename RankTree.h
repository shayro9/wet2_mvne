//
// Created by amida on 24/12/2022.
//

#ifndef WET2_MVNE_RANKTREE_H
#define WET2_MVNE_RANKTREE_H

template <class T>
struct node{
    T data;
    int nodes;
    int height;
    node* l;
    node* r;
};

template<class T>
class RankTree{
public:
    RankTree();
    ~RankTree();
    void DestroyRecursive(node<T>* node);
    RankTree(const RankTree& t) = default;
    RankTree& operator=(const RankTree& q)=default;

    node<T>* find(const T& t);
    int rank(const T& t);
    node<T>* select(int i);
    void insert(T& t);
    void remove(const T& t);

private:
    node<T>* m_root;

    node<T>* findNode(node<T> *root, const T& t);

    node<T>* insertNode(node<T> *root, const T& t);

    int height(node<T>* n);
    int nodesOf(node<T>* n);
    int balanceFactor(node<T> *n);
    node<T>* balance(node<T> *bad_node);

    node<T>* RR_rotate(node<T> *root);
    node<T>* LL_rotate(node<T> *root);
    node<T>* RL_rotate(node<T> *root);
    node<T>* LR_rotate(node<T> *root);

    node<T>* removeNode(node<T> *root, const T& t);
    node<T>* minValueNode(node<T> *root);
    node<T>* minValueNodeParent(node<T> *root);

    node<T>* selectRec(node<T>* root, int i);
};

static int max(int a, int b) {
    return (a > b) ? a : b;
}

template<class T>
RankTree<T>::RankTree() : m_root(nullptr)
{}

template<class T>
RankTree<T>::~RankTree() {
    if(m_root)
        DestroyRecursive(m_root);
}

template<class T>
void RankTree<T>::DestroyRecursive(node<T> *node) {
    if (node)
    {
        DestroyRecursive(node->l);
        DestroyRecursive(node->r);
        if(node == m_root)
            m_root = nullptr;
        delete(&node->data);
    }
}

template<class T>
node<T> *RankTree<T>::find(const T &t) {
    return findNode(m_root,t);
}

template<class T>
node<T> *RankTree<T>::findNode(node<T> *root, const T &t) {
    if(root != nullptr) {
        if (t == root->data)
            return root;
        if (t < root->data)
            return findNode(root->l, t);
        else
            return findNode(root->r, t);
    }
    return nullptr;
}

template<class T>
void RankTree<T>::insert(T &t) {
    m_root = insertNode(m_root,t);
}

template<class T>
node<T> *RankTree<T>::insertNode(node<T> *root, const T &t) {
    if(root == nullptr)
    {
        root = new node<T>();
        root->data = t;
        root->height = 1;
        root->nodes = 1;
        root->l = nullptr;
        root->r = nullptr;
        return root;
    }
    if(t < root->data) {
        root->l = insertNode(root->l, t);
    }
    else if(t > root->data) {
        root->r = insertNode(root->r, t);
    } else
        return root;

    root->height = max(height(root->r), height(root->l)) + 1;
    root->nodes = nodesOf(root->l) + nodesOf(root->r) + 1;
    root = balance(root);
    return root;
}

template<class T>
node<T> *RankTree<T>::balance(node<T> *bad_node) {
    int factor = balanceFactor(bad_node);
    int son_factor;
    switch (factor) {
        case 2:
            son_factor = balanceFactor(bad_node->l);
            if( son_factor >= 0)
                return LL_rotate(bad_node);
            else
                return LR_rotate(bad_node);
        case -2:
            son_factor = balanceFactor(bad_node->r);
            if( son_factor <= 0)
                return RR_rotate(bad_node);
            else
                return RL_rotate(bad_node);
        default:
            return bad_node;
    }
}

template<class T>
int RankTree<T>::balanceFactor(node<T> *n) {
    if (n == nullptr)
        return 0;
    return height(n->l) - height(n->r);
}

template<class T>
int RankTree<T>::height(node<T> *n) {
    if(n == nullptr)
        return 0;
    return n->height;
}


template<class T>
node<T>* RankTree<T>::LL_rotate(node<T> *root) {
    node<T> *temp = root->l;
    root->l = temp->r;
    temp->r = root;
    root->height = 1 + max(height(root->l), height(root->r));
    temp->height = 1 + max(height(temp->l), height(temp->r));

    root->nodes = nodesOf(root->l) + nodesOf(root->r) + 1;
    temp->nodes = nodesOf(temp->l) + nodesOf(temp->r) + 1;

    return temp;
}

template<class T>
node<T>*  RankTree<T>::RR_rotate(node<T> *root) {
    node<T> *temp = root->r;
    root->r = temp->l;
    temp->l = root;
    root->height = 1 + max(height(root->l), height(root->r));
    temp->height = 1 + max(height(temp->l), height(temp->r));

    root->nodes = nodesOf(root->l) + nodesOf(root->r) + 1;
    temp->nodes = nodesOf(temp->l) + nodesOf(temp->r) + 1;
    return temp;
}

template<class T>
node<T>*  RankTree<T>::RL_rotate(node<T> *root) {
    root->r = LL_rotate(root->r);
    return RR_rotate(root);
}

template<class T>
node<T>*  RankTree<T>::LR_rotate(node<T> *root) {
    root->l = RR_rotate(root->l);
    return LL_rotate(root);
}

template<class T>
void RankTree<T>::remove(const T &t) {
    removeNode(m_root,t);
}

template<class T>
node<T> *RankTree<T>::removeNode(node<T> *root, const T &t) {
    if(root == nullptr)
        return root;


    if(t < root->data) {
        root->l = removeNode(root->l,t);
    }

    else if(t > root->data) {
        root->r = removeNode(root->r, t);
    }

    else{
        if(root->r == nullptr && root->l == nullptr) {
            if(root == m_root)
            {
                m_root = nullptr;
            }
            delete(root);
            return nullptr;
        }
        else if (root->l == nullptr) {
            node<T>* temp = root->r;
            if(root == m_root)
                m_root = temp;
            delete(root);
            return temp;
        }
        else if (root->r == nullptr) {
            node<T>* temp = root->l;
            if(root == m_root)
                m_root = temp;
            delete(root);
            return temp;
        }

        node<T>* temp_parent = minValueNodeParent(root->r);
        node<T>* min_son = minValueNode(root->r);
        min_son->l = root->l;
        if(!temp_parent)
        {
            if(root == m_root)
                m_root = min_son;
            delete(root);
            root = min_son;
        }
        else {
            temp_parent->l = min_son->r;
            min_son->r = root->r;
            if (root == m_root)
                m_root = min_son;
            delete (root);
            root = min_son;
        }
        temp_parent->height = max(height(root->r), height(root->l)) + 1;
        temp_parent->nodes = nodesOf(root->l) + nodesOf(root->r) + 1;
    }
    int h = 0, new_h = -1;
    while(h != new_h)
    {
        h = height(root);
        if(root == m_root)
            m_root = balance(root);
        else
            root = balance(root);
        new_h = height(root);
    }
    root->height = max(height(root->r), height(root->l)) + 1;
    root->nodes = nodesOf(root->l) + nodesOf(root->r) + 1;
    return root;
}

template<class T>
node<T> *RankTree<T>::minValueNode(node<T> *root) {
    if(root == nullptr)
        return nullptr;

    if(root->l == nullptr)
        return root;

    return minValueNode(root->l);
}

template<class T>
node<T> *RankTree<T>::minValueNodeParent(node<T> *root) {
    if(root->l == nullptr)
        return nullptr;

    if(root->l->l == nullptr)
        return root;

    return minValueNodeParent(root->l);
}

template<class T>
int RankTree<T>::rank(const T& t) {
    node<T>* curr = m_root;
    int rank = 0;
    while(curr->data != t && curr)
    {
        if(t > curr->data) {
            rank += 1 + nodesOf(curr->l);
            curr = curr->r;
        }
        else
        {
            curr = curr->l;
        }
    }
    if(curr->data == t)
        return rank + 1 + nodesOf(curr->l);
    return 0;
}

template<class T>
int RankTree<T>::nodesOf(node<T> *n) {
    if(n == nullptr)
        return 0;
    return n->nodes;
}

template<class T>
node<T>* RankTree<T>::select(int i) {
    return selectRec(m_root,i);
}

template<class T>
node<T> *RankTree<T>::selectRec(node<T> *root, int i) {
    if(nodesOf(root->l) == i-1)
        return root;

    if(nodesOf(root->l) > i-1)
        return selectRec(root->l, i);

    if(nodesOf(root->l) < i-1)
        return selectRec(root->r, i - nodesOf(root->l) - 1);
}

#endif //WET2_MVNE_RANKTREE_H