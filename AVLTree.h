/**
 * AVLTree.h
 *
 * Project 5 AVLTree
 *
 * Rylan Cheetham
 *
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
        // return balance (left height - right height)
        int getBalance(const AVLNode* node) const;

    };

public:

    // default constructor
    AVLTree();

    // copy constructor
    AVLTree(const AVLTree &other);

    // destructor
    ~AVLTree();

    // insert key-value pair
    bool insert(const std::string &key, size_t value);

    // recursive insert function
    bool insertRecursive(AVLNode *&node, const std::string &key, size_t value);

    // remove key-value pair
    bool remove(const std::string &key);

    // check if key exists
    bool contains(const std::string &key) const;

    // recursive contains function
    bool containsRecursive(AVLNode *node, const std::string &key) const;

    // get key's value
    std::optional<size_t> get(const std::string &key) const;

    // recursive get function
    std::optional<size_t> getRecursive(AVLNode *node, const std::string &key) const;

    // access value by key
    size_t &operator[](const std::string &key);

    // recursive funciton for operator
    size_t &operatorRecursive(AVLNode *&opNode, const std::string &key);

    // get keys within range
    vector<std::string> findRange(const std::string &lowKey, const std::string &highKey) const;

    // return all keys in tree
    std::vector<std::string> keys() const;

    // return number of nodes
    size_t size() const;

    // return height of tree
    size_t getHeight() const;

    // copy assignment
    void operator=(const AVLTree &other);

    // overloaded << operator for printing tree
    friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree);

    private:
    AVLNode* root;
    size_t nodeCount;

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);

    // update height of node
    void updateHeight(AVLNode *node);

    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);


};

#endif //AVLTREE_H
