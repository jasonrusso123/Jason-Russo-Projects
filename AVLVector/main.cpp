#include "AVLVector.cpp"

int main(){
    AVLVector avl;
    
    string command;
    cin >> command;
    while(command!="QUIT"){
    if(command == "INSERT"){
        int r;
        int e;
        cin >> r >> e;
        avl.insertAt(r, e);
    }
    else if(command == "DELETE"){
        int r;
        cin >> r;
        avl.deleteRank(r);
    }
    else if(command == "REPLACE"){

        int r;
        int e;
        cin >> r >> e;
        avl.replaceAt(r, e);

    }
    else if(command == "ELEMENT-AT"){
        int r;
        cin >> r;
        avl.elementAt(r);
    }
    else if(command == "PRINT"){
        avl.print();
    }
    cin >> command;
    }
    
}