#include "BPTree.cpp"

int main(){
    
    cout << "Enter keyLength: ";
    int key;
    int record;
    cin >> key;
    cout << "Enter recordLength: ";
    cin >> record;
    BPTree BP(key, record);

    char command;
    cin >> command;
    while(command != 'Q'){
        if (command == 'I'){
            string record1;
            cin.ignore(); 
            getline(cin, record1); 
            BP.insertPublic(record1);
        }
        else if(command == 'S'){
            string key1;
            cin >> key1;
            BP.searchAllPublic(key1);
        }
        else if(command == 'P'){
            BP.printAllPublic();
        }
        else if(command == 'R'){
            int address;
            cin >> address;
            BP.printRoot();
            BP.printSectorPublic(address);
        }
        else if(command == 'D'){
            string key1;
            cin >> key1;
            BP.deletePublic(key1);
        }
        cin >> command;
    }
    return 0;

}