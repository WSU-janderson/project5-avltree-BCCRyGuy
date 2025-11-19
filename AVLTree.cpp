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


AVLTree::AVLTree() : root(nullptr) {

}

AVLTree::AVLTree(const AVLTree& other) : root(nullptr) {

}

AVLTree::~AVLTree() {

}

size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return height;
}

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

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}

bool AVLTree::insert(const std::string& key, size_t value) {
    return false;
}

bool AVLTree::remove(const std::string& key) {
    return false;
}

bool AVLTree::contains(const std::string& key) const {
    return false;
}

std::optional<size_t> AVLTree::get(const std::string& key) const {
    return std::nullopt;
}

size_t& AVLTree::operator[](const std::string& key) {

}

vector<std::string> AVLTree::findRange( const std::string& lowKey, const std::string& highKey) const {

}

std::vector<std::string> AVLTree::keys() const {

}

size_t AVLTree::size() const {
    return 0;
}

size_t AVLTree::getHeight() const {
    return 0;
}

void AVLTree::operator=(const AVLTree& other) {

}