#include "AVLVector.cpp"

int main(){
    AVLVector avl;
    AVLBasic avlb(avl);

/*avl.insertAt(1, 23);    // INSERT 1 23
avlb.insertAt(1, 23, avl);

avl.insertAt(2, 12);    // INSERT 2 12
avlb.insertAt(2, 12, avl);

avl.insertAt(1, 45);    // INSERT 1 45
avlb.insertAt(1, 45, avl);

avl.insertAt(4, 10);    // INSERT 4 10
avlb.insertAt(4, 10, avl);

avl.insertAt(5, 55);    // INSERT 5 55
avlb.insertAt(5, 55, avl);

avl.insertAt(3, 16);    // INSERT 3 16
avlb.insertAt(3, 16, avl);

avl.insertAt(4, 77);    // INSERT 4 77
avlb.insertAt(4, 77, avl);

avl.insertAt(6, 108);   // INSERT 6 108
avlb.insertAt(6, 108, avl);

avl.insertAt(4, 123);    // INSERT 4 123
avlb.insertAt(4, 123, avl);

avl.insertAt(8, 128);    // INSERT 8 128
avlb.insertAt(8, 128, avl);

avl.insertAt(5, 451);    // INSERT 5 451
avlb.insertAt(5, 451, avl);

avl.insertAt(7, 109);    // INSERT 7 109
avlb.insertAt(7, 109, avl);

avl.insertAt(10, 525);   // INSERT 10 525
avlb.insertAt(10, 525, avl);

avl.insertAt(13, 136);   // INSERT 13 136
avlb.insertAt(13, 136, avl);

avl.insertAt(2, 727);    // INSERT 2 727
avlb.insertAt(2, 727, avl);

avl.insertAt(5, 128);    // INSERT 5 128
avlb.insertAt(5, 128, avl);

avl.replaceAt(4, 102);
avlb.replaceAt(4, 102, 16, avl);*/


    string command;
    cin >> command;
    while(command!="QUIT"){
    if(command == "INSERT"){
        int r;
        int e;
        cin >> r;
        cin >> e;
        avl.insertAt(r, e);
        avlb.insertAt(r, e, avl);
        
    }
    else if(command == "DELETE"){
        int r;
        cin >> r;
        Node* current = avl.find(r, 0, avl.root);
        int e = -1;
        if(current != NULL){
            e = current->value;
        }
        if(e != -1){
        
        NodeBasic* find = avlb.rankFinder(e, r, avlb.root, avl);

        int newVal = avl.deleteRank(r);
        
        avlb.removeAtRank(r, e, newVal, find, avl);}

        else{
            cout << "Failed deletion attempt." << endl;
        }


        //avlb.deleteRank(avlb.elementAt(r), avl);
    }
    else if(command == "REPLACE"){

        int r;
        int e;
        cin >> r >> e;
        Node* base = avl.find(r, 0, avl.root);
        if(base == NULL) cout << "-1" << endl;
        else if( base != NULL){
        int old = base->value;
        
        if(avlb.replaceAt(r, e, old, avl) != -1) avl.replaceAt(r, e);}
        

    }
    else if(command == "ELEMENT-AT"){
        int r;
        cin >> r;
        avl.elementAt(r);
    }
    else if(command == "PRINT"){
        avl.print();
        //cout << "------------------" << endl;
        //avlb.print();
        //avlb.print();
    }
    else if(command == "RANKOF"){
        int e;
        cin >> e;
        cout << avlb.rankOf(e, avl) << endl;
    }
    cin >> command;
    }
    
}
