/*
 * AVLTree.cpp
 *
 * Project 5 AVLTree
 *
 * Rylan Cheetham
 *
 */


#include "AVLTree.h"

#include <optional>
#include <vector>
#include <string>

// default constructor
AVLTree::AVLTree() : root(nullptr) {

}

// copy constructor
AVLTree::AVLTree(const AVLTree& other) : root(nullptr) {

}

// destructor
AVLTree::~AVLTree() {

}

// return number of children of node
size_t AVLTree::AVLNode::numChildren() const {
    size_t count = 0;
    if (left != nullptr) {
        count++;
    }
    if (right != nullptr) {
        count++;
    }
    return count;
}

// check if node is a leaf
bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr) {
        return true;
    } else {
        return false;
    }
}

// return height of node
size_t AVLTree::AVLNode::getHeight() const {
    return height;
}

// calculate balance of node
int AVLTree::AVLNode::getBalance(const AVLNode *node) const {
    int leftHeight = -1;
    if (node->left != nullptr) {
        leftHeight = static_cast<int>(node->left->getHeight());
    }
    int rightHeight = -1;
    if (node->right != nullptr) {
        rightHeight = static_cast<int>(node->right->getHeight());
    }
    return leftHeight - rightHeight;
}

// update height
void AVLTree::updateHeight(AVLNode* node) {

}

// remove node
bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

// recursive remove helper
bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

// rebalance node if unbalanced
void AVLTree::balanceNode(AVLNode *&node) {
}

// insert new key-value pair
bool AVLTree::insert(const std::string& key, size_t value) {
    return false;
}

// remove key-value pair
bool AVLTree::remove(const std::string& key) {
    return false;
}

// check if key exists
bool AVLTree::contains(const std::string& key) const {
    AVLNode* current = root;
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

// get value for key
std::optional<size_t> AVLTree::get(const std::string& key) const {
    AVLNode* current = root;

    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return std::nullopt;
}

// access value by key
size_t& AVLTree::operator[](const std::string& key) {

}

// return key in range
vector<std::string> AVLTree::findRange( const std::string& lowKey, const std::string& highKey) const {

}

// return all keys
std::vector<std::string> AVLTree::keys() const {

}

// return number of nodes
size_t AVLTree::size() const {
    return 0;
}

// return height of tree
size_t AVLTree::getHeight() const {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

// copy assignment
void AVLTree::operator=(const AVLTree& other) {

}