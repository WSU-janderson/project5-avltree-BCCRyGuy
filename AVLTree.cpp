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
#include <iostream>

// default constructor
AVLTree::AVLTree() : root(nullptr), nodeCount(0) {

}

// copy constructor
AVLTree::AVLTree(const AVLTree& other) : root(nullptr), nodeCount(other.nodeCount) {

}

// destructor. delete nodes, set root to null, set nodeCount to 0
AVLTree::~AVLTree() {
    deleteNodes(root);
    root = nullptr;
    nodeCount = 0;
}

AVLTree::AVLNode* AVLTree::copyNode(const AVLNode *current) {
    if (current == nullptr) {
        return nullptr;
    }

    AVLNode* newNode = new AVLNode{current->key, current->value, current->height, nullptr, nullptr};
    newNode->left = copyNode(current->left);
    newNode->right = copyNode(current->right);
    return newNode;
}

void AVLTree::deleteNodes(AVLNode *current) {
    if (current == nullptr) {
        return;
    }
    deleteNodes(current->left);
    deleteNodes(current->right);
    delete current;
}

// return number of children of node (left and right are child nodes)
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
int AVLTree::AVLNode::getBalance(const AVLNode *current) const {
    int leftHeight = -1;
    if (current->left != nullptr) {
        leftHeight = static_cast<int>(current->left->getHeight());
    }
    int rightHeight = -1;
    if (current->right != nullptr) {
        rightHeight = static_cast<int>(current->right->getHeight());
    }
    return leftHeight - rightHeight;
}

// update height
void AVLTree::updateHeight(AVLNode* node) {
    int leftHeight = -1;
    if (node->left != nullptr) {
        leftHeight = static_cast<int>(node->left->getHeight());
    }
    int rightHeight = -1;
    if (node->right != nullptr) {
        rightHeight = static_cast<int>(node->right->getHeight());
    }

    node->height = std::max(leftHeight, rightHeight) + 1;
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



// recursive remove helper. Referenced zybooks BST Recursion and Removal, and AVL removals
bool AVLTree::remove(AVLNode *&current, KeyType key) {
    // base case, if current node is null return false
    if (current == nullptr) {
        return false;
    }

    // storing bool value again to allow for balancing and updating height
    bool removed;
    // if the key is found, remove the node and decrease nodeCount
    if (current->key == key) {
        removed = removeNode(current);
        if (removed) {
            nodeCount--;
        }
    // if the key passed is less than, recursive call on the left child node
    } else if (key < current->key) {
        removed = remove(current->left, key);
    // if not, recursive call on right child node
    } else {
        removed = remove(current->right, key);
    }

    // if node was removed update height and balance
    if (removed) {
        updateHeight(current);
        balanceNode(current);
    }

    // return bool value returned from removeNode
    return removed;
}

// rebalance node if unbalanced. Directly referenced Figure 11.2.2 in zybooks
void AVLTree::balanceNode(AVLNode *&current) {
    updateHeight(current);

    // right heavy rotations
    if (current->getBalance(current) == -2) {
        if (current->getBalance(current->right) == 1) {
            // double rotation case
            current->right = rotateRight(current->right);
        }
        current = rotateLeft(current);
    // left heavy rotations
    } else if (current->getBalance(current) == 2) {
        if (current->getBalance(current->left) == -1) {
            // double rotation case
            current->left = rotateLeft(current->left);
        }
        current = rotateRight(current);
    }
}

// rotate right
AVLTree::AVLNode* AVLTree::rotateRight(AVLNode* problemNode) {
    // hook node = left child of problem node
    AVLNode* hookNode = problemNode->left;
    // leftRightChild = right child of hook node to be moved
    AVLNode* leftRightChild = hookNode->right;

    // if the problem node is the root, update root
    if (problemNode == root) {
        root = hookNode;
    }

    hookNode->right = problemNode;
    problemNode->left = leftRightChild;

    // update heights of both problem and hook
    updateHeight(problemNode);
    updateHeight(hookNode);

    // return new root of subtree (hookNode)
    return hookNode;
}

// rotate left
AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode* problemNode) {
    // hook node = right child of problem node
    AVLNode* hookNode = problemNode->right;
    // leftRightChild = left child of hook node to be moved
    AVLNode* rightLeftChild = hookNode->left;

    // if the problem node is the root, update root
    if (problemNode == root) {
        root = hookNode;
    }

    hookNode->left = problemNode;
    problemNode->right = rightLeftChild;

    // update heights of both problem and hook
    updateHeight(problemNode);
    updateHeight(hookNode);

    // return new root of subtree (hookNode)
    return hookNode;
}

// insert new key-value pair. Referenced 10.11.1 zybooks
bool AVLTree::insert(const std::string& key, size_t value) {
    return insertRecursive(root, key, value);
}

// recursive insert function. Referenced zybooks BST Recursion and AVL insertions
bool AVLTree::insertRecursive(AVLNode *&current, const std::string& key, size_t value) {
    // creating variable to store values of recursive calls
    // instead of returning directly like in zybooks
    bool inserted;

    // if the node is null create a new node, increment the count and return true
    if (current == nullptr) {
        current = new AVLNode{key, value, 0, nullptr, nullptr};
        nodeCount++;
        return true;
    // if the node already exists (duplicate) return false
    } else if (current->key == key) {
        return false;
    // recursive call on left node if key parameter is less than current node's key
    } else if (key < current->key) {
        inserted = insertRecursive(current->left, key, value);
    } else {
        inserted = insertRecursive(current->right, key, value);
    }

    // update the height and balance of tree
    updateHeight(current);
    balanceNode(current);

    // return stored inserted bool value from recursive call
    return inserted;
}

// remove key-value pair. Referenced 10.11.1 zybooks
bool AVLTree::remove(const std::string& key) {
    return remove(root, key);
}

// check if key exists. Referenced 10.11.1 zybooks
bool AVLTree::contains(const std::string& key) const {
    return containsRecursive(root, key);
}

// recursive contains function. Referenced 10.11.1 zybooks
bool AVLTree::containsRecursive(AVLNode* node, const std::string& key) const {
    if (node != nullptr) {
        if (node->key == key) {
            return true;
        } else if (key < node->key) {
            return containsRecursive(node->left, key);
        } else {
            return containsRecursive(node->right, key);
        }
    }
    return false;

}

// get value for key. Referenced 10.11.1 zybooks
std::optional<size_t> AVLTree::get(const std::string& key) const {
    return getRecursive(root, key);
}

// recursive get function. Referenced 10.11.1 zybooks
std::optional<size_t> AVLTree::getRecursive(AVLNode* node, const std::string& key) const {
    if (node != nullptr) {
        if (node->key == key) {
            return node->value;
        } else if (key < node->key) {
            return getRecursive(node->left, key);
        } else {
            return getRecursive(node->right, key);
        }
    }
    return std::nullopt;
}

// access value by key
size_t& AVLTree::operator[](const std::string& key) {
    return operatorRecursive(root, key);
}

size_t& AVLTree::operatorRecursive(AVLNode*& opNode, const std::string& key) {
    if (opNode->key == key) {
        return opNode->value;
    } else if (key < opNode->key) {
        return operatorRecursive(opNode->left, key);
    } else {
        return operatorRecursive(opNode->right, key);
    }
}

// return key in range
vector<std::string> AVLTree::findRange( const std::string& lowKey, const std::string& highKey) const {

}

// return all keys
std::vector<std::string> AVLTree::keys() const {
    std::vector<std::string> keys;
    keysRecursive(root, keys);
    return keys;
}

void AVLTree::keysRecursive(const AVLNode *node, std::vector<std::string> &key) const {
    if (node == nullptr) {
        return;
    }
    keysRecursive(node->left, key);
    key.push_back(node->key);
    keysRecursive(node->right, key);
}

// return number of nodes
size_t AVLTree::size() const {
    return nodeCount;
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

void AVLTree::printTreeRecursive(std::ostream &os, const AVLNode *node, int depth) const {
    if (node == nullptr) {
        return;
    }
    // go as far right as possible before printing
    printTreeRecursive(os, node->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        os << "    ";
    }
    os << "{" << node->key << ": " << node->value << "}" << std::endl;
    // print left nodes next
    printTreeRecursive(os, node->left, depth + 1);
}

// friend function definition
std::ostream & operator<<(ostream &os, const AVLTree &avlTree) {
    // call recursive function starting from root
    avlTree.printTreeRecursive(os, avlTree.root, 0);
    return os;
}
