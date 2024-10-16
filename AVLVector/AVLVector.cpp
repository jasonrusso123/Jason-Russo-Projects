#include "AVLVector.h"

AVLVector::AVLVector(){

    root = new Node;
    root -> value = -9999;
    treeSize = 1;

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
        cout << "Successful replacement" << endl;
        return (1);
    }

}

void AVLVector::RRrestructure(Node* node){
    Node* base = node;
    Node* middle = node->right;
    Node* bottom = middle->right;
    Node* above = NULL;
    if(node != root){
        above = base->parent;
    }

    if(node == root){//handles if need restructure stemming from root
        if(middle->left!=NULL) base->right = middle->left;
        middle->left = base;
        middle->right = bottom;
        bottom->parent = middle;
        base->parent = middle;
        base->right = NULL;
        root = middle;
        middle->leftSize++;
        middle->parent = NULL;
    }
    
    else if(above->right == base){
        if(middle->left!=NULL) base->right = middle->left;
        above->right = middle;
        middle->left = base;
        middle->right = bottom;
        bottom->parent = middle;
        base->parent = middle;
        base->right = NULL;
        middle->parent = above;
        middle->leftSize++;

    }
    
    else if(above->left == base){
        if(middle->left!=NULL) base->right = middle->left;
        above->left = middle;
        middle->left = base;
        middle->right = bottom;
        bottom->parent = middle;
        base->parent = middle;
        base->right = NULL;
        middle->leftSize++;
        middle->parent = above;

    }
    if (above!=NULL) above->setHeight();
    base->setHeight();
    middle->setHeight();
    bottom->setHeight();

}


void AVLVector::LLrestructure(Node* node){
    Node* base = node;
    Node* middle = node->left;
    Node* bottom = middle->left;
    Node* above = NULL;
    if(node != root){
        above = base->parent;
    }

    if(node == root){//handles if need restructure stemming from root
        if(middle->right!=NULL) base->left = middle->right;
        middle->right = base;
        middle->left = bottom;
        bottom->parent = middle;
        base->parent = middle;
        base->left = NULL;
        root = middle;
        base->leftSize -= 2;
        middle->parent = NULL;
    }
    
    else if(above->right == base){
        if(middle->right!=NULL) base->left = middle->right;
        above->right = middle;
        middle->right = base;
        middle->left = bottom;
        bottom->parent = middle;
        base->parent = middle;
        base->left = NULL;
        base->leftSize -= 2;
        middle->parent = above;


    }
    
    else if(above->left == base){
        if(middle->right!=NULL) base->left = middle->right;
        above->left = middle;
        middle->right = base;
        middle->left = bottom;
        bottom->parent = middle;
        base->parent = middle;
        base->left = NULL;
        base->leftSize -= 2;
        middle->parent = above;


    }

    if (above!=NULL) above->setHeight();
    base->setHeight();
    middle->setHeight();
    bottom->setHeight();

}

void AVLVector::RLrestructure(Node* node){

    Node* base = node;
    Node* middle = base->right;
    Node* bottom = middle->left;    

    base->right = bottom;
    bottom->parent = base;

    bottom->right = middle;
    middle->parent = bottom;

    middle->left = NULL;
    middle->leftSize--;

    RRrestructure(base);

}

void AVLVector::LRrestructure(Node* node){

    Node* base = node;
    Node* middle = base->left;
    Node* bottom = middle->right;    

    base->left = bottom;
    bottom->parent = base;

    bottom->left = middle;
    middle->parent = bottom;

    middle->right = NULL;
    bottom->leftSize++;

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
        return 0;
    }
    else if(node->value == -9999){
        node->value = val;
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
    return 1;
}


int AVLVector::removeAtRank(int r, int prior_rank, Node* node) {
    Node* temp = node;
    Node* temp1;
    Node* temp2 = temp;
    if(temp == NULL) return -1;
    while (temp2 != NULL && r != prior_rank + temp2->leftSize + 1){
        if(r > prior_rank + node->leftSize + 1){
            prior_rank += node->leftSize + 1;
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
        temp->leftSize--;
        temp1 = temp->left;
        while(temp1->right) temp1 = temp1->right;
        temp->value = temp1->value;
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
        temp->setHeight();
    }
    
    return 1;
    
    
    /*cout << "Attempting to delete node with rank " << r << endl;
    
    Node* current = find(r, prior_rank, node);
    
    if (current == NULL) return -9999;
    cout << "deleting node with value " << current->value << endl;
    
    cout << "Tree before deletion: " << endl;
    print();
    int deleteValue = current->value; // Store the value to be returned
    cout << "Step 1" << endl;
    Node* foundParent = current->parent;
    cout << "Step 2" << endl;

    
    cout << "Step 4" << endl;

    bool isLeftChild = foundParent && foundParent->left == current;

    Node* newValNode = findLeftMax(current);
    Node* trailer = NULL;

    // Case 1: Node to be removed has no children
    if (current->left == NULL && current->right == NULL) {
        trailer = current->parent;
        if (current == root) {
            root = NULL;
        } else {
            if (isLeftChild){
                foundParent->left = NULL;
                foundParent->leftSize --;
            }    
            else foundParent->right = NULL;
        }
        delete current;
        
    }
    // Case 2: Node to be removed has only one child
    else if (!current->left || !current->right) {
        trailer = current->parent;
        Node* child = current->left ? current->left : current->right;
        if (current == root) {
            root = child;
            child->parent = nullptr;
        } else {
            child->parent = foundParent;
            if (isLeftChild){
                foundParent->left = child;
                foundParent -> leftSize--;
            }
            else foundParent->right = child;
        }
        delete current; 
    }
    // Case 3: Node to be removed has two children
    else {
        
        trailer = newValNode->parent;
        int newVal = newValNode->value;

        if (newValNode->left) {
            newValNode->parent->right = newValNode->left;
            newValNode->left->parent = newValNode->parent;            
        } else {
            if (newValNode->parent->left == newValNode) {
                newValNode->parent->left = NULL;
            } else {
                newValNode->parent->right = NULL;
            }
        }
        delete newValNode;
        current->value = newVal;
        current->leftSize--;
    }
    cout << "tree before rebalance " << endl;;
    print();
    cout << "tree post print" << endl;
    cout << trailer->value << endl;
    cout << trailer->parent->value << endl;
    rebalance(trailer);
    cout << "final tree: " << endl;
    print();
    return deleteValue; // Return the value of the deleted node*/
}


int AVLVector::deleteRank(int r){
    return removeAtRank(r, 0, root);
}

void AVLVector::printAll(int prior_rank, Node* node){
    if(node != NULL){
        int rank = prior_rank + node->leftSize + 1;
        printAll(prior_rank, node->left);
        cout << "Rank: " << rank << ", value: " << node->value << endl;
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
    cout << "Entering rebalance function" << endl;
    if (node == nullptr) {
        cout << "Warning: rebalance called with null node" << endl;
        return;
    }

    Node* current = node;
    while (current) {
        cout << "Rebalancing node with value: " << current->value << endl;
        
        current->setHeight();  // Update height
        cout << current->height << endl;
        int balance = current->getBalanceFactor();
        cout << "Balance factor: " << balance << endl;

        if (balance > 1) {
            cout << "Left heavy" << endl;
            if (current->left == nullptr) {
                cout << "Error: Left child is null when balance > 1" << endl;
                return;
            }
            int leftBalance = current->left->getBalanceFactor();
            cout << "Left child balance factor: " << leftBalance << endl;

            if (leftBalance >= 0) {
                cout << "Performing LL restructure" << endl;
                LLrestructure(current);
            } else {
                cout << "Performing LR restructure" << endl;
                LRrestructure(current);
            }
        } else if (balance < -1) {
            cout << "Right heavy" << endl;
            if (current->right == nullptr) {
                cout << "Error: Right child is null when balance < -1" << endl;
                return;
            }
            int rightBalance = current->right->getBalanceFactor();
            cout << "Right child balance factor: " << rightBalance << endl;

            if (rightBalance <= 0) {
                cout << "Performing RR restructure" << endl;
                RRrestructure(current);
            } else {
                cout << "Performing RL restructure" << endl;
                RLrestructure(current);
            }
        }

        cout << "Moving to parent node" << endl;
        current = current->parent;
        
    }
    
    cout << "Rebalance complete" << endl;
}