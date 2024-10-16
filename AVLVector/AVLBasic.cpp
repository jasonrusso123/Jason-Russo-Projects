#include "AVLBasic.h"

AVLBasic::AVLBasic(){

    NodeBasic* root = new NodeBasic;

}

AVLBasic::~AVLBasic(){

    destroy(root);

}

void AVLBasic::destroy(NodeBasic* root){

    if(root != NULL){
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

}

int AVLBasic::rankOf(int e){

    NodeBasic* some = root;
    bool done = false;

    int finalValue = -9999; //what the element will be returned as

    while(some != NULL){
        if(e == some->value){
            finalValue = some->rank;
            done = true;
        }
        
        else if(e > some->value){
            some = some->right;
        }

        else{
            some = some->left;
        }
    }

    if (!done){
        cout << "Error: rank out of bounds" << endl;
    }
    cout << finalValue << endl;
    return finalValue;

}