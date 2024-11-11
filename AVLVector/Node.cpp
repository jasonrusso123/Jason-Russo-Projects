#include "Node.h"

Node::Node(){
    value = 0;
    leftSize = 0;
    height = 0;
    balanceFactor = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
    elementPointer = NULL;
}

Node::~Node(){}

Node::Node(int val, Node *lef, Node *rig, Node *par){
    value = val;
    leftSize = 0;
    height = 0;
    balanceFactor = 0;
    left = lef;
    right = rig;
    parent = par;
}

int Node::getHeight() {
    if (this == nullptr) {
        return -1;  // Height of a null node is -1
    }
    
    return this->height;
}

void Node::setHeight() {
    if (this == nullptr) {
        return;
    }
    
    int leftHeight = (this->left != nullptr) ? this->left->getHeight() : -1;
    int rightHeight = (this->right != nullptr) ? this->right->getHeight() : -1;
    
    this->height = 1 + max(leftHeight, rightHeight);
}

int Node::getBalanceFactor() {
    if (this == nullptr) {
        return 0;  // Balance factor of a null node is 0
    }
    
    int leftHeight = (left != nullptr) ? left->getHeight() : -1;
    int rightHeight = (right != nullptr) ? right->getHeight() : -1;
    
    return leftHeight - rightHeight;
}


NodeBasic::NodeBasic(){
    value = 0;
    height = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
    rankPointer = NULL;
}

NodeBasic::~NodeBasic(){}

NodeBasic::NodeBasic(int val){
    value = val;
    left = NULL;
    parent = NULL;
    right = NULL;
    rankPointer = NULL;
}

int NodeBasic::getHeight() {
    if (this == nullptr) {
        return -1;  // Height of a null node is -1
    }
    
    return this->height;
}

void NodeBasic::setHeight() {
    if (this == nullptr) {
        return;
    }
    
    int leftHeight = (this->left != nullptr) ? this->left->getHeight() : -1;
    int rightHeight = (this->right != nullptr) ? this->right->getHeight() : -1;
    
    this->height = 1 + max(leftHeight, rightHeight);
}

int NodeBasic::getBalanceFactor() {
    if (this == nullptr) {
        return 0;  // Balance factor of a null node is 0
    }
    
    int leftHeight = (left != nullptr) ? left->getHeight() : -1;
    int rightHeight = (right != nullptr) ? right->getHeight() : -1;
    
    return leftHeight - rightHeight;
}

