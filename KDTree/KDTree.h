/**
 * File: KDTree.h
 * Author: (your name here)
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include "Point.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>

template <size_t N, typename ElemType>
struct Node {
    Node(Point<N> point, ElemType data) {
        this->point = point;
        this->data = data;
    }

    Point<N> point;
    ElemType data;
    Node* left = nullptr;
    Node* right = nullptr;

    double levelCoord(int level){
            return point[level%N];
        }
};

// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();
    
    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();
    
    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);

    KDTree& operator=(const KDTree& rhs);
    
    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;
    
    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;
    
    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;
    
    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);
    
    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt);
    
    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;
    
    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;

private:
    // TODO: Add implementation details here.
    Node<N, ElemType>* root;
    void deleteTree(Node<N, ElemType>* node);
    Node<N, ElemType>* findNode(Point<N>) const;
    Node<N, ElemType>* insertNode(const Point<N>& p, const ElemType& data);
    void kNNHelper(const Point<N>& key, BoundedPQueue<Node<N, ElemType>*>& pqueue, Node<N, ElemType>* current, double bestDist, int level) const;
    void recCopy(Node<N, ElemType>* other, Node<N, ElemType>* newNode);

    size_t sizeT = 0;
};

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
    root = nullptr;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    deleteTree(root);

}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return N;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const {
    return sizeT;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const {
    return sizeT == 0;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const {
    return findNode(pt) != nullptr;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value) {
    insertNode(pt, value);
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt) {
    Node<N, ElemType>* node = findNode(pt);
    if (node == nullptr) {
        ElemType data;
        Node<N, ElemType>* newNode = insertNode(pt, data);
        return newNode->data;
    } else {
        return node->data;
    }
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) {
    Node<N, ElemType>* node = findNode(pt);
    if (node == nullptr) {
        throw out_of_range("Point not in tree");
    } else {
        return node->data;
    }
}

template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const {
    Node<N, ElemType>* node = findNode(pt);
    if (node == nullptr) {
        throw out_of_range("Point not in tree");
    } else {
        return node->data;
    }
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::deleteTree(Node<N, ElemType>* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

template <size_t N, typename ElemType>
Node<N, ElemType>* KDTree<N, ElemType>::findNode(Point<N> pt) const {
    if(root == nullptr) return root;
    Node<N, ElemType>* current = root;
    int level = 0;
    while(true) {
        if(current->point == pt) return current;
        if(pt[level%N] < current->levelCoord(level)) {
            if (current->left == nullptr) {
                return current->left;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == nullptr) {
                return current->right;
            } else {
                current = current->right;
            }
        }
        level++;
    }
}

template <size_t N, typename ElemType>
Node<N, ElemType>* KDTree<N, ElemType>::insertNode(const Point<N>& p, const ElemType& data) {
    if(root == nullptr) {
        root = new Node<N, ElemType>(p, data);
        sizeT++;
        return root;
    }
    Node<N, ElemType>* current = root;
    int level = 0;
    while(true) {
        if(current->point == p) {
            current->data = data;
            return current;
        }
        if(p[level%N] < current->levelCoord(level)) {
            if (current->left == nullptr) {
                current->left = new Node<N, ElemType>(p, data);
                sizeT++;
                return current->left;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == nullptr) {
                current->right = new Node<N, ElemType>(p, data);
                sizeT++;
                return current->right;
            } else {
                current = current->right;
            }
        }
        level++;
    }
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::kNNHelper(const Point<N>& key, BoundedPQueue<Node<N, ElemType>*>& pqueue , Node<N, ElemType>* current, double bestDist, int level) const {

    if(current == nullptr) {
        return;
    }

    double dist = Distance(current->point, key);
    pqueue.enqueue(current, dist);

    double curri = current->point[level%N];
    double keyi = key[level%N];

    if(keyi < curri) {
        kNNHelper(key, pqueue, current->left, bestDist, level + 1);
    } else {
        kNNHelper(key, pqueue, current->right, bestDist, level + 1);
    }

    if(abs(curri - keyi) < pqueue.worst() || pqueue.size() < pqueue.maxSize()) {
        if(keyi < curri) {
            kNNHelper(key, pqueue, current->right, bestDist, level + 1);
        } else {
            kNNHelper(key, pqueue, current->left, bestDist, level + 1);
        }
    }

}


template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const {
    double bestDist = Distance(root->point, key);
    BoundedPQueue<Node<N, ElemType>*> pqueue(k);
    kNNHelper(key, pqueue, root, bestDist, 0);


    map<ElemType, int> karta;
    while(!pqueue.empty()) {
        ElemType curr = pqueue.dequeueMin()->data;

        if(karta.count(curr)) {
            karta[curr]++;
        } else {
            karta[curr] = 1;
        }
    }

    pair<ElemType, int> biggest;
    for(auto const& elem: karta) {
        if(elem.second > biggest.second) {
            biggest = elem;
        }
    }
    return biggest.first;

}
template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree& rhs) {
    if(this == &rhs) {
        return;
    }
    this->root = new Node<N, ElemType>(rhs.root->point, rhs.root->data);
    this->sizeT = rhs.sizeT;

    recCopy(rhs.root, this->root);
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::recCopy(Node<N, ElemType>* other, Node<N, ElemType>* newNode) {

    if(other->left != nullptr) {
        newNode->left = new Node<N, ElemType>(other->left->point, other->left->data);
        recCopy(other->left, newNode->left);
    }
    if(other->right != nullptr) {
        newNode->right = new Node<N, ElemType>(other->right->point, other->right->data);
        recCopy(other->right, newNode->right);
    }
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree& rhs) {
    if(this == &rhs) {
        return *this;
    }
    deleteTree(root);

    this->root = new Node<N, ElemType>(rhs.root->point, rhs.root->data);
    this->sizeT = rhs.sizeT;

    recCopy(rhs.root, this->root);
    return *this;
}

#endif // KDTREE_INCLUDED












