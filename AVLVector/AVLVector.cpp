#include "AVLVector.h"

AVLVector::AVLVector(){

    root = NULL;
    treeSize = 0;

}

AVLVector::~AVLVector(){

    destroy(root);

}

void AVLVector::destroy(Node* root){

    if(root != NULL){
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

}

Node* AVLVector::find(int r, int prior_rank, Node* node){
    if(node == NULL) return (NULL);
    if(prior_rank + node->leftSize + 1 == r) return node;
    if(r > prior_rank + node->leftSize + 1){
        prior_rank += node->leftSize + 1;
        return find(r, prior_rank, node->right);
    }
    else return find(r, prior_rank, node->left);
}

int AVLVector::elementAt(int r){
    return elementAtRank(r, 0, root);
}

int AVLVector::elementAtRank(int r, int prior_rank, Node* node){

    Node* current = NULL;
    current = find(r, prior_rank, node);
    if(current == NULL) {
        cout << "No element found" << endl;
        return(-9999);
    }
    else{
        cout << current->value << endl;
        return current->value;
    }

}

int AVLVector::replaceAt(int r, int e){
    return replaceAtRank(r, e, 0, root);
}

int AVLVector::replaceAtRank(int r, int e, int prior_rank, Node* node){

    Node* current = NULL;
    current = find(r, prior_rank, node);
    if(current == NULL){
        cout << "Unsuccessful replacement" << endl;
        return (-9999);
    }
    else{
        current->value = e;
        return (1);
    }

}

void AVLVector::RRrestructure(Node* node){
    Node* base = node;
    Node* middle = node->right;
    Node* above = NULL;
    if(node != root){
        above = base->parent;
    }
    middle->parent = above;
    if (above) {
        if (above->left == base)
            above->left = middle;
        else
            above->right = middle;
    } else {
        root = middle;
    }

    base->right = middle->left;
    if(base->right) base->right->parent = base;

    middle->left = base;
    base->parent = middle;
    middle->leftSize += base->leftSize + 1;
    
    if (above!=NULL) above->setHeight();
    base->setHeight();
    middle->setHeight();

}


void AVLVector::LLrestructure(Node* node){
    Node* base = node;
    Node* middle = node->left;
    Node* above = NULL;
    if(node != root){
        above = base->parent;
    }
    middle->parent = above;
    if (above) {
        if (above->left == base)
            above->left = middle;
        else
            above->right = middle;
    } else {
        root = middle;
    }

    base->left = middle->right;
    if(base->left) base->left->parent = base;

    middle->right = base;
    base->parent = middle;
    base->leftSize -= middle->leftSize + 1;
    
    if (above!=NULL) above->setHeight();
    base->setHeight();
    middle->setHeight();

}

void AVLVector::RLrestructure(Node* node){

    Node* base = node;
    Node* middle = base->right;
    Node* bottom = middle->left;    

    base->right = bottom;
    bottom->parent = base;

    middle->left = bottom->right;
    if (bottom->right) {
        bottom->right->parent = middle;
        middle->leftSize += bottom->right->leftSize + 1;
    }

    bottom->right = middle;
    middle->parent = bottom;

    middle->leftSize -= bottom->leftSize + 1;
    middle->setHeight();
    bottom->setHeight();

    RRrestructure(base);

}

void AVLVector::LRrestructure(Node* node){

    Node* base = node;
    Node* middle = base->left;
    Node* bottom = middle->right;    

    base->left = bottom;
    bottom->parent = base;

    middle->right = bottom->left;
    if (bottom->left) {
        bottom->left->parent = middle;
        bottom->leftSize += middle->right->leftSize + 1;
    }

    bottom->left = middle;
    middle->parent = bottom;

    bottom->leftSize += middle->leftSize + 1;;

    middle->setHeight();
    bottom->setHeight();

    LLrestructure(base);

}

int AVLVector::insertAt(int r, int e){
    return insertAtRank(r, e, 0, root);
}

int AVLVector::insertAtRank(int r, int val, int prior_rank, Node* node){
    if(r > treeSize + 1 || r < 1){
        cout << "Invalid insertion attempt" << endl;
        return -1;
    }
    bool done, violation;
    Node* temp;
    if(root == NULL){
        root = new Node;
        root->value = val;
        root->height = 0;
        root->left = NULL;
        root->right = NULL;
        root->parent = NULL;
        treeSize++;
        return 0;
    }
    else{
        temp = root;
        done = false;
        while(!done){
            if(prior_rank + temp->leftSize + 1 >= r){
                if(temp->left == NULL){
                    temp->left = new Node;
                    temp->left->parent = temp;
                    temp->left->value = val;
                    temp->left->height = 0;
                    temp->left->left = NULL;
                    temp->left->right = NULL;
                    temp->leftSize++;
                    done = true;
                }
                else {
                    temp->leftSize++;
                    temp = temp->left;
                }
            }
            else if(prior_rank + temp->leftSize + 1 < r){
                prior_rank += temp->leftSize + 1;
                if(temp->right == NULL){
                    temp->right = new Node;
                    temp->right->parent = temp;
                    temp->right->value = val;
                    temp->right->height = 0;
                    temp->right->left = NULL;
                    temp->right->right = NULL;
                    done = true;
                }
                else {
                    temp = temp->right;
                }
            }
        }
        temp->height = 1;
        done = (temp->parent == NULL);
        violation = false;
        while(!done){
            temp = temp->parent;
            temp->setHeight();
            if(temp->left == NULL || temp->right == NULL){
                violation = true;
            }
            else if(temp->getBalanceFactor() >1 || temp->getBalanceFactor() < -1){
                violation = true;
            }
            if(violation){
                rebalance(temp);
            }
            if(temp == root){
                done = true;
            }
        }
    }
    treeSize++;
    return 1;
}


int AVLVector::removeAtRank(int r, int prior_rank, Node* node) {
    if(r > treeSize + 1 || r < 1){
        cout << "Failed deletion attempt" << endl;
        return -1;
    }
    Node* temp = node;
    Node* temp1;
    Node* temp2 = temp;
    int tempValue = 0;
    if(temp == NULL) return -1;
    while (temp2 != NULL && r != prior_rank + temp2->leftSize + 1){
        if(r > prior_rank + temp2->leftSize + 1){
            prior_rank += temp2->leftSize + 1;
            temp2 = temp2->right;
        }
        else{
            temp2->leftSize--;
            temp2 = temp2->left;
        }
    }
    if(temp2 == NULL){
        cout << "No element to delete" << endl;
        return -1;
    }
    treeSize--;
    temp = temp2;

    /*if(!find(r, prior_rank, temp)) return -1;
    temp = find(r, prior_rank, temp);*/
    temp1 = temp;
    if(temp->left == NULL){
        if(temp == root){
            if(temp->right != NULL){
                root = root->right;
                root->parent = NULL;
                temp->elementPointer->rankPointer = NULL;
                delete temp;
            }
            else{
                root = NULL;
                temp->elementPointer->rankPointer = NULL;
                delete temp;
            }
        }
        else{
            temp1 = temp->parent;
            if(temp1->left == temp)temp1->left = temp->right;
            else temp1->right = temp->right;
            temp->elementPointer->rankPointer = NULL;
            delete temp;
            temp1->setHeight();
            temp = temp1;
        }
    }
    else{
        temp->leftSize--;
        temp1 = temp->left;
        while(temp1->right) temp1 = temp1->right;
        temp->value = temp1->value;
        tempValue = temp->value;
        temp1->elementPointer->rankPointer = temp;
        temp->elementPointer = temp1->elementPointer;
        temp = temp1->parent;
        if(temp->left == temp1)temp->left = temp1->left;
        else temp->right = temp1->left;
        temp->setHeight();    
        delete temp1;
    }
    while(temp!=NULL){
        if(temp->height >= 2){
            rebalance(temp);
        }
        temp = temp->parent;
        if(temp) temp->setHeight();
    }
    
    return tempValue;
}


int AVLVector::deleteRank(int r){
    return removeAtRank(r, 0, root);
}

void AVLVector::printAll(int prior_rank, Node* node){
    if(node != NULL){
        int rank = prior_rank + node->leftSize + 1;
        printAll(prior_rank, node->left);
        cout << "Rank: " << rank << ", value: " << node->value << endl;
        /*if (node->parent == NULL) cout << " root" << endl;
        else if(node == node->parent->left) cout << " left of " << node->parent->value << endl;
        else cout << " right of " << node->parent->value << endl;*/
        printAll(rank, node->right);
    }

}

void AVLVector::print(){
    printAll(0, root);
}



Node* AVLVector::findLeftMax(Node* node){
    Node* current = node;
    if(current->left == NULL){
        return NULL;
    }
    else{
        current = current->left;
        while(current->right){
            current = current->right;
        }
    }
    return current;
}




void AVLVector::rebalance(Node* node) {
    if (node == nullptr) {
        return;
    }

    Node* current = node;
    while (current) {
        
        current->setHeight();  // Update height
        int balance = current->getBalanceFactor();

        if (balance > 1) {
            if (current->left == nullptr) {
                return;
            }
            int leftBalance = current->left->getBalanceFactor();

            if (leftBalance >= 0) {
                LLrestructure(current);
            } else {
                LRrestructure(current);
            }
        } else if (balance < -1) {
            if (current->right == nullptr) {
                return;
            }
            int rightBalance = current->right->getBalanceFactor();

            if (rightBalance <= 0) {
                RRrestructure(current);
            } else {
                RLrestructure(current);
            }
        }

        current = current->parent;
        
    }
    
}



AVLBasic::AVLBasic(){
    root = NULL;
    treeSize = 0;

}

AVLBasic::~AVLBasic(){

    destroy(root);

}

AVLBasic::AVLBasic(AVLVector& AVL){

    root = NULL;
    treeSize = 0;
    
    if(AVL.root != NULL) {
        root = new NodeBasic();  // Use root instead of AVLRoot
        // Initialize the root node properly
        if (root) {
            root->value = AVL.root->value;
            root->height = 0;
            root->left = NULL;
            root->right = NULL;
            root->parent = NULL;
            root->rankPointer = AVL.root;
        }
    }
}

void AVLBasic::destroy(NodeBasic* root){
    if(root != NULL){
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

}

NodeBasic* AVLBasic::rankFinder(int e, int r, NodeBasic* node, AVLVector& AVL){
    if(node == NULL) return (NULL);
    if(e == node->value && findRank(node->rankPointer, AVL) == r) return node;
    if(e > node->value){
        return rankFinder(e, r, node->right, AVL);
    }
    else return rankFinder(e, r, node->left, AVL);
}


NodeBasic* AVLBasic::find(int e, NodeBasic* node){
    
    if(node == NULL) return (NULL);
    if(e == node->value) return node;
    if(e > node->value){
        return find(e, node->right);
    }
    else return find(e, node->left);
}


int AVLBasic::replaceAt(int r, int replacement, int e, AVLVector& AVL){
    return replaceElement(r, replacement, e, root, AVL);
}

int AVLBasic::replaceElement(int r, int replacement, int e, NodeBasic* node, AVLVector& AVL){
    NodeBasic* elementNode = rankFinder(e, r, node, AVL);
    if (elementNode == NULL) {
        cout << "-1" << endl;
        return -1;
    }
    
    Node* rankPtr = elementNode->rankPointer;
    
    NodeBasic* parent = elementNode->parent;
    bool isLeftChild = (parent != NULL && parent->left == elementNode);
    
    if (elementNode->left == NULL) {
        NodeBasic* rightChild = elementNode->right;
        
        if (elementNode == root) {
            root = rightChild;
            if (rightChild) rightChild->parent = NULL;
        } else {
            if (isLeftChild) {
                parent->left = rightChild;
            } else {
                parent->right = rightChild;
            }
            if (rightChild) rightChild->parent = parent;
        }
        delete elementNode;
        elementNode = NULL;
    }
    else {
        NodeBasic* predecessor = elementNode->left;
        NodeBasic* predParent = elementNode;
        
        while (predecessor->right) {
            predParent = predecessor;
            predecessor = predecessor->right;
        }
        
        elementNode->value = predecessor->value;
        elementNode->rankPointer = predecessor->rankPointer;
        predecessor->rankPointer->elementPointer = elementNode;
        
        if (predParent == elementNode) {
            predParent->left = predecessor->left;
            if (predecessor->left)
                predecessor->left->parent = predParent;
        } else {
            predParent->right = predecessor->left;
            if (predecessor->left)
                predecessor->left->parent = predParent;
        }
        
        parent = predParent;  
        delete predecessor;
        treeSize--;
    }
    
    int insert = insertAtRank(r, replacement, root, AVL);
    if (insert == -1) {
        return -1;
    }
    
    while (parent != NULL) {
        parent->setHeight();
        if (parent->getBalanceFactor() > 1 || parent->getBalanceFactor() < -1) {
            rebalance(parent);
        }
        parent = parent->parent;
    }

    return 1;

}

void AVLBasic::RRrestructure(NodeBasic* node){
    NodeBasic* base = node;
    NodeBasic* middle = node->right;
    NodeBasic* above = NULL;
    if(node != root){
        above = base->parent;
    }
    middle->parent = above;
    if (above) {
        if (above->left == base)
            above->left = middle;
        else
            above->right = middle;
    } else {
        root = middle;
    }

    base->right = middle->left;
    if(base->right) base->right->parent = base;

    middle->left = base;
    base->parent = middle;
    
    if (above!=NULL) above->setHeight();
    base->setHeight();
    middle->setHeight();

}


void AVLBasic::LLrestructure(NodeBasic* node){
    NodeBasic* base = node;
    NodeBasic* middle = node->left;
    NodeBasic* above = NULL;
    if(node != root){
        above = base->parent;
    }
    middle->parent = above;
    if (above) {
        if (above->left == base)
            above->left = middle;
        else
            above->right = middle;
    } else {
        root = middle;
    }

    base->left = middle->right;
    if(base->left) base->left->parent = base;

    middle->right = base;
    base->parent = middle;
    
    if (above!=NULL) above->setHeight();
    base->setHeight();
    middle->setHeight();

}

void AVLBasic::RLrestructure(NodeBasic* node){

    NodeBasic* base = node;
    NodeBasic* middle = base->right;
    NodeBasic* bottom = middle->left;    

    base->right = bottom;
    bottom->parent = base;

    middle->left = bottom->right;
    if (bottom->right) {
        bottom->right->parent = middle;
    }

    bottom->right = middle;
    middle->parent = bottom;

    middle->setHeight();
    bottom->setHeight();

    RRrestructure(base);

}

void AVLBasic::LRrestructure(NodeBasic* node){

    NodeBasic* base = node;
    NodeBasic* middle = base->left;
    NodeBasic* bottom = middle->right;    

    base->left = bottom;
    bottom->parent = base;

    middle->right = bottom->left;
    if (bottom->left) {
        bottom->left->parent = middle;
    }

    bottom->left = middle;
    middle->parent = bottom;

    middle->setHeight();
    bottom->setHeight();

    LLrestructure(base);

}

int AVLBasic::insertAt(int r, int e, AVLVector& AVL){
    return insertAtRank(r, e, root, AVL);
}

int AVLBasic::insertAtRank(int r, int val, NodeBasic* node, AVLVector& AVL){
    Node* rp = AVL.find(r, 0, AVL.root);
    if(r > treeSize + 1 || r < 1){
        return -1;
    }

    bool done, violation;
    NodeBasic* temp;
    if(root == NULL){
        root = new NodeBasic;
        root->value = val;
        root->height = 0;
        root->left = NULL;
        root->right = NULL;
        root->parent = NULL;
        root->rankPointer = AVL.root;
        AVL.root->elementPointer = root;
        treeSize++;
        return 0;
    }
    else{
        temp = root;
        done = false;
        while(!done){
            if(temp->value >= val){
                if(temp->left == NULL){
                    temp->left = new NodeBasic;
                    temp->left->parent = temp;
                    temp->left->value = val;
                    temp->left->height = 0;
                    temp->left->left = NULL;
                    temp->left->right = NULL;
                    temp->left->rankPointer = rp;
                    rp->elementPointer = temp->left;
                    done = true;
                }
                else {
                    temp = temp->left;
                }
            }
            else if(temp->value < val){
                if(temp->right == NULL){
                    temp->right = new NodeBasic;
                    temp->right->parent = temp;
                    temp->right->value = val;
                    temp->right->height = 0;
                    temp->right->left = NULL;
                    temp->right->right = NULL;
                    temp->right->rankPointer = rp;
                    rp->elementPointer = temp->right;
                    done = true;
                }
                else {
                    temp = temp->right;
                }
            }
        }
        temp->height = 1;
        done = (temp->parent == NULL);
        violation = false;
        while(!done){
            
            temp = temp->parent;
            temp->setHeight();
            if(temp->left == NULL || temp->right == NULL){
                violation = true;
            }
            else if(temp->getBalanceFactor() >1 || temp->getBalanceFactor() < -1){
                violation = true;
            }

            if(violation){
                rebalance(temp);
            }

            if(temp == root){
                done = true;
            }

        }

    }
    treeSize++;
    return 1;
}


int AVLBasic::removeAtRank(int r, int e, int newVal, NodeBasic* node, AVLVector& AVL) {
    NodeBasic* temp = node;
    NodeBasic* temp1;
    NodeBasic* temp2 = temp;

    /*if(newVal > 0){
        NodeBasic* current = rankFinder(newVal, r - 2, node, AVL);
        current->rankPointer = AVL.find(r-1, 0, AVL.root);
    }*/

    if(temp == NULL) return -1;
    /*while (temp2 != NULL && (e != temp2->value && findRank(temp2->rankPointer, AVL) != r)){
        if(e > temp2->value){
            temp2 = temp2->right;
        }
        else{
            temp2 = temp2->left;
        }
    }*/
    if(temp == NULL){
        cout << "No element to delete" << endl;
        return -1;
    }
    treeSize--;
    temp = temp2;

    /*if(!find(r, prior_rank, temp)) return -1;
    temp = find(r, prior_rank, temp);*/
    temp1 = temp;
    if(temp->left == NULL){
        if(temp == root){
            if(temp->right != NULL){
                root = root->right;
                root->parent = NULL;
                delete temp;
            }
            else{
                root = NULL;
                delete temp;
            }
        }
        else{
            temp1 = temp->parent;
            if(temp1->left == temp)temp1->left = temp->right;
            else temp1->right = temp->right;
            delete temp;
            temp1->setHeight();
            temp = temp1;
        }
    }
    else{
        temp1 = temp->left;
        while(temp1->right) temp1 = temp1->right;
        temp->value = temp1->value;
        temp->rankPointer = temp1->rankPointer;
        temp = temp1->parent;
        if(temp->left == temp1)temp->left = temp1->left;
        else temp->right = temp1->left;
        temp->setHeight();    
        delete temp1;
    }
    while(temp!=NULL){
        if(temp->height >= 2){
            rebalance(temp);
        }
        temp = temp->parent;
        if(temp)temp->setHeight();
    }

    return 1;    
}


/*int AVLBasic::deleteRank(int r, int e, int newVal, AVLVector& AVL){
    return removeAtRank(r, e, newVal, root, AVL);
}*/


NodeBasic* AVLBasic::findLeftMax(NodeBasic* node){
    NodeBasic* current = node;
    if(current->left == NULL){
        return NULL;
    }
    else{
        current = current->left;
        while(current->right){
            current = current->right;
        }
    }
    return current;
}




void AVLBasic::rebalance(NodeBasic* node) {
    if (node == nullptr) {
        return;
    }

    NodeBasic* current = node;
    while (current) {
        
        current->setHeight();  // Update height
        int balance = current->getBalanceFactor();

        if (balance > 1) {
            if (current->left == nullptr) {
                return;
            }
            int leftBalance = current->left->getBalanceFactor();

            if (leftBalance >= 0) {
                LLrestructure(current);
            } else {
                LRrestructure(current);
            }
        } else if (balance < -1) {
            if (current->right == nullptr) {
                return;
            }
            int rightBalance = current->right->getBalanceFactor();

            if (rightBalance <= 0) {
                RRrestructure(current);
            } else {
                RLrestructure(current);
            }
        }

        current = current->parent;
        
    }
    
}

int AVLBasic::rankOfElement(int e, NodeBasic* node, AVLVector& AVL){
    NodeBasic* current = find(e, node);
    if (current == NULL){
        cout << "Element not found" << endl;
        return -1;
    }
    else{
        int r = findRank(current->rankPointer, AVL);
        return r;
    }
}

int AVLBasic::rankOf(int e, AVLVector& AVL){
    return rankOfElement(e, root, AVL);
}

int AVLBasic::findRank(Node* node, AVLVector& AVL){
    if(node == NULL) return -1;
    Node* current = node;
    int rank = current->leftSize + 1;
    while(current->parent != NULL){
        if(current == current->parent->right){
            rank += current->parent->leftSize + 1;
            current = current->parent;
        }
        else current = current->parent;
    }
    return rank;

}

void AVLBasic::printAll(NodeBasic* node){
    if(node != NULL){
        cout << "value: " << node->value << " rankPointer: " << node->rankPointer->value;
        if(node->parent == NULL) cout << " root" << endl;
        else if(node->parent->left == node) cout << " left of " << node->parent->value << endl;
        else cout << " right of " << node->parent->value << endl;
        printAll(node->left);
        printAll(node->right);
    }

}

void AVLBasic::print(){

    printAll(root);

}