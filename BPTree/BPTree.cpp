#include "BPTree.h"


BPTree::BPTree(int key, int record){
    keyLength = key;
    recordLength = record;
    root = 0;
    m = (292 + keyLength)/(4 + keyLength);
    if(m % 2 == 0) m -= 1;
    n = 292/recordLength;
    if(n % 2 == 0) n -= 1;
    sectors[0][0] = 'L';
    setNumKeys(root, 0);
    setPointer(root, 4, -1);

    freeNodeVector.resize(4000);
    for(int i = 1; i < 4000; i++){
        freeNodeVector[i] = 4000 - i;
    }
    cout << "m: " << m << endl;
    cout << "n: " << n << endl;

    /*insert("16592743805637291460123456789012345678901234567890123456789012345678901234567890123456789012");

    insert("23845672901234567890123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("27596134850362917485901234567890123456789012345678901234567890123456789012345678901234567890");
    insert("29054618273045912836457890123456789012345678901234567890123456789012345678901234567890123456");

    insert("32741596803625417950123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("36785412097856231408901234567890123456789012345678901234567890123456789012345678901234567890");
    insert("382450916723584061728901234567890123456789012345678901234567890123456789012345R6789012345678");
    insert("41678290345617823045612378901234567890123456789012345678901234567890123456789012345678901234");
    insert("43867259016234578920123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("45817092635418290357689012345678901234567890123456789012345678901234567890123456789012345678");
    insert("47216583092745361890123456789012345678901234567890123456789012345678901234567890123456789034");
    insert("51936274803562914720123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("52768930416275839056789012345678901234567890123456789012345678901234567890123456789012345678");
    insert("54621890347562918034567890123456789012345678901234567890123456789012345678901234567890123456");
    insert("58729034561290347651234567890123456789012345678901234567890123456789012345678901234567890123");
    insert("61859023746512937850123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("63819425706192384570123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("65012384756291035476823901234567890123456789012345678901234567890123456789012345678901234567");
    insert("67192384056721943850123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("69214537082936415720123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("76234590812347650923145678901234567890123456789012345678901234567890123456789012345678901245");
    insert("79234516082974356120123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("81273056492817365024567890123456789012345678901234567890123456789012345678901234567890123456");
    insert("84267039512683745960123456789012345678901234567890123456789012345678901234567890123456789012");
    insert("85629043712568297401234567890123456789012345678901234567890123456789012345678901234567890123");
    insert("92746051823795402156789012345678901234567890123456789012345678901234567890123456789012345678");
    insert("94653281067392845126789012345678901234567890123456789012345678901234567890123456789012345678");
    insert("97615384270592164030123456789012345678901234567890123456789012345678901234567890123456789012");*/
    //caseLeafOpenDelete(findIndex("1659274380563729146012345678901234567890123456789012345678901234567890123456789012345678901"),"1659274380563729146012345678901234567890123456789012345678901234567890123456789012345678901");
    //caseLeafOpenDelete(findIndex("3274159680362541795012345678901234567890123456789012345678901234567890123456789012345678901"), "32741596803625417950123456789012345678901234567890123456789012345678901234567890123456789012");
    //caseRedistributeLeaf(findIndex("2384567290123456789012345678901234567890123456789012345678901234567890123456789012345678901"), "2384567290123456789012345678901234567890123456789012345678901234567890123456789012345678901");
    //replaceKey(3, "3274159680362541795012345678901234567890123456789012345678901234567890123456789012345678901");
    //caseMergeLeaf(findIndex("2759613485036291748590123456789012345678901234567890123456789012345678901234567890123456789"), "2759613485036291748590123456789012345678901234567890123456789012345678901234567890123456789");
    //deleteBP("4581709263541829035768901234567890123456789012345678901234567890123456789012345678901234567");
    //insert("29054618273045912836457890123456789012345678901234567890123456789012345678901234567890123456");
    /*deleteBP("1659274380563729146012345678901234567890123456789012345678901234567890123456789012345678901");
    deleteBP("2905461827304591283645789012345678901234567890123456789012345678901234567890123456789012345");
    deleteBP("2384567290123456789012345678901234567890123456789012345678901234567890123456789012345678901");
    deleteBP("2759613485036291748590123456789012345678901234567890123456789012345678901234567890123456789");*/

}

BPTree::~BPTree(){}

/***********************************************
*                                              *
*           Helper Functions                   *
*                                              *
***********************************************/

int BPTree::getPointer(int index, int arrayValue){
    if(arrayValue + 4 >= 300) return -1;
    int pointerValue = asciiConvert(sectors[index][arrayValue]) * 1000 +
                       asciiConvert(sectors[index][arrayValue + 1]) * 100 +
                       asciiConvert(sectors[index][arrayValue + 2]) * 10 +
                       asciiConvert(sectors[index][arrayValue + 3]);
    return pointerValue;

}

void BPTree::setPointer(int index, int arrayValue, int pointer){

    string pointerValue = asciiIntConvert(pointer, 4);
    for(int i = 0; i < 4; i++){
        sectors[index][arrayValue + i] = pointerValue[i];
    }
    return;

}
        
int BPTree::getNumKeys(int index){

    int numKeys = asciiConvert(sectors[index][1]) * 100 +
                  asciiConvert(sectors[index][2]) * 10 +
                  asciiConvert(sectors[index][3]);
    return numKeys;

}  
        
void BPTree::setNumKeys(int index, int numKeys){
    string numKeysValue = asciiIntConvert(numKeys, 3);
    for(int i = 0; i < 3; i++){
        sectors[index][1 + i] = numKeysValue[i];
    }
    return;
    
}

string BPTree::getKey(int index, int arrayValue){
    string keyValue = "";
    for(int j = 0; j < keyLength; j++){
        keyValue += sectors[index][arrayValue + j];
    }
    return keyValue;
}

void BPTree::setKey(int index, int arrayValue, string key){
    
    for(int i = 0; i < keyLength; i++){
        sectors[index][arrayValue + i] = key[i];
    }
    return;
    
}

string BPTree::getRecord(int index, int arrayValue){

    string record = "";
    for(int j = 0; j < recordLength; j++){
        record += sectors[index][arrayValue + j];
    }
    return record;

}

void BPTree::setRecord(int index, int arrayValue, string record){

    for(int i = 0; i < recordLength; i++){
        sectors[index][arrayValue + i] = record[i];
    }
    return;
    
}        

int BPTree::asciiConvert(char character){
    int returnValue = static_cast<int>(character) - 48;
    //-48 as this is the conversion factor for numerical digits and ascii characters.                                                       
    return returnValue;
}

string BPTree::asciiIntConvert(int integer , int count){

    string returnValue = "";
    for(int i = 1; i <= count; i++){
        int newInt = integer / pow(10, count - i);
        integer = integer - newInt * pow(10, count - i);
        char newChar = static_cast<char>(newInt + 48);
        returnValue += newChar;
    }
    return returnValue;

}

string BPTree::getKeyFromRecord(string record){
    string key = "";
    for(int i = 0; i < keyLength; i++){
        key += record[i];
    }
    return key;
}

bool BPTree::checkFirstGreater(string key1, string key2){
    for(int i = 0; i < keyLength; i++){
        if(key1[i] > key2[i]) return true;
        else if(key1[i] < key2[i]) return false;
    }
    return false;
}

int BPTree::getNewNode(){
    int newNode = freeNodeVector.back();
    freeNodeVector.pop_back();
    return newNode;
}

int BPTree::createNewRoot(int oldRoot, string key, int newNode){
    // Allocate new node
    int newRoot = getNewNode();
    
    // Set up node type and counts
    sectors[newRoot][0] = 'I';  // Internal node
    setNumKeys(newRoot, 1);    // One key initially (using first 3 bytes for numKeys)
    setPointer(newRoot, 4, -1);   // No parent for root (bytes 4-7)
    
    // Set up pointers and key
    setPointer(newRoot, 8, oldRoot);        // First pointer to old root
    setKey(newRoot, 12, key);               // Middle key
    setPointer(newRoot, 12 + keyLength, newNode);       // Second pointer to new node
    
    // Update children's parent pointers
    setPointer(oldRoot, 4, newRoot);        // Update old root's parent
    setPointer(newNode, 4, newRoot);        // Update new node's parent
    
    // Update tree's root pointer
    root = newRoot; 
    return root;
}

/***********************************************
*                                              *
*           Print Functions                    *
*                                              *
***********************************************/
void BPTree::print(int index){
    if(index < 0) return;

    if(sectors[index][0] == 'L') {
        printLeaf(index);
        return;
    }


    int arrayValue = 8;
    int numKeys = getNumKeys(index);
    for(int i = 0; i < numKeys + 1; i++){
        int newIndex = getPointer(index, arrayValue);
        print(newIndex);
        arrayValue += 4 + keyLength;
    }

}

void BPTree::printRoot(){
    cout << "Root: " << root << endl;
}

void BPTree::printLeaf(int address){
    int numRecord = getNumKeys(address);
    int arrayValue = 8;
    for(int i = 1; i < numRecord + 1; i++){
        cout << address << " record " << i << ": ";
        for(int j = 0; j < recordLength; j++){
            cout << sectors[address][j + arrayValue];
        }
        arrayValue += recordLength;
        cout << endl;
    }
}//Finds relevant address, prints that sector

void BPTree::printSector(int address){
    for(int i = 0; i < 300; i++){
        cout << sectors[address][i];
    }
    cout << endl;
}

void BPTree::printAllPublic(){

    print(root);
}

void BPTree::printSectorPublic(int address){
    printSector(address);
}


/***********************************************
*                                              *
*           Search Functions                   *
*                                              *
***********************************************/

int BPTree::findIndex(string key){
    int index = root;

    while(sectors[index][0] != 'L'){ // while
        int numKeys = getNumKeys(index);
        int i = 0; //Used to track number of keys checked
        int arrayValue = 12; //Used to check position in array, first key at 12 for all arrays
        string keyValueAbove = "";

        while (i < numKeys && !checkFirstGreater(keyValueAbove, key))
        {
            keyValueAbove = getKey(index, arrayValue);
            arrayValue += keyLength;
            
            i++;
            arrayValue += 4;
        }
        if(i < numKeys || checkFirstGreater(keyValueAbove, key)){
            arrayValue -= keyLength;
            if(i > 0) arrayValue -= 4;
            arrayValue -= 4;
            index = getPointer(index, arrayValue);
        }
        else{
            arrayValue -=4;
            index = getPointer(index, arrayValue);
        }

               
    }
    return index;
}

bool BPTree::search(string key){
    if(key.length() != keyLength){
        cout << "Invalid key entered" << endl;
        return false;
    }
    
    int index = findIndex(key);

    int arrayValue = 8;
    int numKeys = getNumKeys(index);
    int i = 0;
    string keyVal = "";
    for(int i = 0; i < numKeys; i++){
        keyVal = getKey(index, arrayValue);
        arrayValue += recordLength;
        if(keyVal == key){
            cout << "found" << endl;
            return true;
        }
    }
    cout << "Not found" << endl;
    return false;
    
}

bool BPTree::find(string key){
        
    int index = findIndex(key);

    int arrayValue = 8;
    int numKeys = getNumKeys(index);
    int i = 0;
    string keyVal = "";
    for(int i = 0; i < numKeys; i++){
        keyVal = getKey(index, arrayValue);
        arrayValue += recordLength;
        if(keyVal == key){
            return true;
        }
    }
    return false;
}

bool BPTree::searchAllPublic(string key){

    return search(key);

}


/***********************************************
*                                              *
*           Insert Functions                   *
*                                              *
***********************************************/

int BPTree::splitLeaf(int index, string newRecord){ // used if leaf is too large
    if(freeNodeVector.empty()) return -9999;
    int newIndex = getNewNode();

    int numKeys = getNumKeys(index);
    string newKey = getKeyFromRecord(newRecord);

    string* recordArray = new string[numKeys + 1];
    string* keyArray = new string[numKeys + 1];
    
    int arrayValue = 8;
    string record1 = getRecord(index, arrayValue);
    string i = getKeyFromRecord(record1);
    int j = 0;

    while(checkFirstGreater(newKey, i) && j < numKeys){
        recordArray[j] = record1;
        keyArray[j] = i; 

        j++;
        arrayValue += recordLength;
        if(arrayValue + recordLength < 300){
            record1 = getRecord(index, arrayValue);
            i = getKeyFromRecord(record1);  
        }  
    }
    recordArray[j] = newRecord;
    keyArray[j] = newKey;

    for(int k = j + 1; k < numKeys + 1; k++){
        recordArray[k] = record1;
        keyArray[k] = i;

        arrayValue += recordLength;
        if(arrayValue + recordLength < 300){
            record1 = getRecord(index, arrayValue);
            i = getKeyFromRecord(record1);  
        } 
    }

    //Loading into original array:
    arrayValue = 8;
    for(int w = 0; w < (n/2) + 1; w++){

        setRecord(index, arrayValue, recordArray[w]);
        arrayValue += recordLength;

    }

    sectors[newIndex][0] = 'L';
    setNumKeys(index, (n/2) + 1);
    setNumKeys(newIndex, (n/2) + 1);

    setPointer(newIndex, 4, getPointer(index, 4));
    
    arrayValue = 8;
    for(int w = (n/2) + 1; w < n + 1; w++){
        setRecord(newIndex, arrayValue, recordArray[w]);
        arrayValue += recordLength;
    }

    //arrays are properly loaded
    delete[] recordArray;
    delete[] keyArray;

    if(index == root){
        if(freeNodeVector.empty()) return -9999;

        /*int newRoot = freeNodeVector.back();
        freeNodeVector.pop_back();

        sectors[newRoot][0] = 'I';
        setNumKeys(newRoot, 1);
        setPointer(newRoot, 4, -1);
        setPointer(newRoot, 8, index);
        setPointer(newRoot, 12 + keyLength, newIndex);
        setKey(newRoot, 12, getKeyFromRecord(getRecord(newIndex, 8)));
        
        setPointer(index, 4, newRoot);
        setPointer(newIndex, 4, newRoot);

        root = newRoot;
        return -1;*/

        createNewRoot(root, getKeyFromRecord(getRecord(newIndex, 8)), newIndex);
        return (-1);
    }

    else{
        return newIndex;
    }


}

int BPTree::splitInternal(int index, string newKey, int originalPointer, int newPointer) {
    if(freeNodeVector.empty()) return -1;
    int newIndex = getNewNode();

    int numKeys = getNumKeys(index);
    

    string* keyArray = new string[numKeys + 1];
    int* pointerArray = new int[numKeys + 2];

    
    int j = 0;
    string key1 = getKey(index, 12);
    int keyValue = 12;
    int pointer1 = getPointer(index, 8);
    int pointerValue = 8;
    while(pointer1 != index && j < numKeys){
        pointerArray[j] = pointer1;
        keyArray[j] = key1;
        
        keyValue += keyLength + 4;
        pointerValue += keyLength + 4;
        j++;

        if(j < numKeys){
            key1 = getKey(index, keyValue);
        }
        pointer1 = getPointer(index, pointerValue);

    }

    pointerArray[j] = pointer1;
    keyArray[j] = newKey;

    j++;
    pointer1 = newPointer;
    while(j < numKeys + 1){
        pointerArray[j] = pointer1;
        keyArray[j] = key1;
        
        keyValue += keyLength + 4;
        pointerValue += keyLength + 4;
        j++;

        if(j < numKeys){
            key1 = getKey(index, keyValue);
        }
        pointer1 = getPointer(index, pointerValue);
    }
    pointerArray[j] = pointer1;//Arrays now fully loaded

    int arrayValue = 8;
    int i;
    for(i = 0; i < (m/2) + 1; i++){
        setPointer(index, arrayValue, pointerArray[i]);
        arrayValue += 4;
        setKey(index, arrayValue, keyArray[i]);
        arrayValue += keyLength;
    }
    setPointer(index, arrayValue, pointerArray[i]);
    

    string finalKey = keyArray[i];
    i++;
    arrayValue = 8;
    for(int k = 0; k < m/2; k++){
        setPointer(newIndex, arrayValue, pointerArray[i]);
        arrayValue += 4;
        if(i < numKeys+1) setKey(newIndex, arrayValue, keyArray[i]);
        arrayValue += keyLength;   
        i++;
    }
    setPointer(newIndex, arrayValue, pointerArray[i]);
    sectors[newIndex][0] = 'I';
    setNumKeys(newIndex, (m/2));
    setNumKeys(index, (m/2) + 1);
    setPointer(newIndex, 4, getPointer(index, 4));
    delete[] pointerArray;
    delete[] keyArray;

    int newValue = 8;
    for(int i = 0; i < (m/2) + 1; i++){
        setPointer(getPointer(newIndex, newValue), 4, newIndex);
        newValue += keyLength + 4;
    }
    
    
    if(index == root){
        if(freeNodeVector.empty()) return -9999;

        /*int newRoot = freeNodeVector.back();
        freeNodeVector.pop_back();

        sectors[newRoot][0] = 'I';
        setNumKeys(newRoot, 1);
        setPointer(newRoot, 4, -1);
        setPointer(newRoot, 8, index);
        setPointer(newRoot, 12 + keyLength, newIndex);
        setKey(newRoot, 12, finalKey);
        
        setPointer(index, 4, newRoot);
        setPointer(newIndex, 4, newRoot);

        root = newRoot;
        return "root";*/
        createNewRoot(root, finalKey, newIndex);
        
        return -1;
    }

    else{
        return newIndex;
    }

    return 1;

}


int BPTree::insert(string record){
    if(record.length() != recordLength){
        cout << "Invalid record entered" << endl;
        return -9999;
    }

    string key = getKeyFromRecord(record);
    int index = findIndex(key);

    //Case 1: Leaf node not full:
    int numKeysLeaf = getNumKeys(index);
    if(numKeysLeaf == 0){
        setRecord(index, 8, record);
        setNumKeys(index, 1);
    }
    else if (numKeysLeaf < n){
        int arrayValue = 8;
        string record1 = getRecord(index, arrayValue);
        int i = 0;
        string* recordArray = new string[numKeysLeaf + 1];
        while(i < numKeysLeaf && checkFirstGreater(key, getKeyFromRecord(record1))){
            recordArray[i] = record1;
            arrayValue += recordLength;
            i++;
            record1 = getRecord(index, arrayValue);
        }
        recordArray[i] = record;
        i++;
        for(int k = i; k < numKeysLeaf + 1; k++){
            recordArray[k] = record1;
            arrayValue += recordLength;
            i++;
            if(i < numKeysLeaf + 1) record1 = getRecord(index, arrayValue);
        }

        arrayValue = 8;
        numKeysLeaf++;
        setNumKeys(index, numKeysLeaf);


        for(int j = 0; j < numKeysLeaf; j++){
            setRecord(index, arrayValue, recordArray[j]);
            arrayValue += recordLength;
        }
        delete[] recordArray;

    }
    else if(numKeysLeaf == n){
        int newIndex = splitLeaf(index, record);
        string newKey = getKeyFromRecord(getRecord(newIndex, 8));
        int parentPointer = getPointer(index, 4);
        
        while(getNumKeys(parentPointer) == m){
            newIndex = splitInternal(parentPointer, newKey, index, newIndex);
            int temp = newIndex;

            index = parentPointer;
            parentPointer = getPointer(index, 4);
            if(temp != -1){
                while(sectors[temp][0] != 'L'){
                    temp = getPointer(temp, 8);
                }
            }
            newKey = getKey(temp, 8);
        }
        if(newIndex == -1){//this case is handled in splitLeaf/splitInternal
            return 1;
        }
        else{
            int numKeys = getNumKeys(parentPointer);

            string* keyArray = new string[numKeys + 1];
            int* pointerArray = new int[numKeys + 2];

            int j = 0;
            string key1 = getKey(parentPointer, 12);
            int keyValue = 12;
            int pointer1 = getPointer(parentPointer, 8);
            int pointerValue = 8;
            while(pointer1 != index && j < numKeys){
                pointerArray[j] = pointer1;
                keyArray[j] = key1;

                keyValue += keyLength + 4;
                pointerValue += keyLength + 4;
                j++;

                if(j < numKeys){
                    key1 = getKey(parentPointer, keyValue);
                }
                pointer1 = getPointer(parentPointer, pointerValue);

            }

            pointerArray[j] = pointer1;
            keyArray[j] = newKey;

            j++;
            pointer1 = newIndex;

            while(j < numKeys + 1){
                pointerArray[j] = pointer1;
                keyArray[j] = key1;

                keyValue += keyLength + 4;
                pointerValue += keyLength + 4;
                j++;

                if(j < numKeys){
                    key1 = getKey(parentPointer, keyValue);
                }
                pointer1 = getPointer(index, pointerValue);
            }
            pointerArray[j] = pointer1;//loaded
            

            keyValue = 12;
            pointerValue = 8;
            for(int i = 0; i < numKeys + 1; i++){
                setKey(parentPointer, keyValue, keyArray[i]);
                setPointer(parentPointer, pointerValue, pointerArray[i]);

                keyValue += keyLength + 4;
                pointerValue += keyLength + 4;
            }
            setPointer(parentPointer, pointerValue, pointerArray[numKeys + 1]);
            numKeys++;
            setNumKeys(parentPointer, numKeys);
            
            delete[] pointerArray;
            delete[] keyArray;
        }
    }   
    
    return 1; 

}

int BPTree::insertPublic(string record){
    return insert(record);
}


/***********************************************
*                                              *
*           Delete Functions                   *
*                                              *
***********************************************/
void BPTree::replaceKey(int index, string key){
    string replaceKey;
   

    if(sectors[index][0] == 'L') replaceKey = getKey(index, 8);
    else replaceKey = getKey(index, 12);
    int arrayValue = 12;
    bool continueLoop = true;
        
    int parentPointer = getPointer(index, 4);
    if(index != root){
        while(continueLoop){
            arrayValue = 12;
            for(int i = 0; i < getNumKeys(parentPointer); i++){
                    
                if(getKey(parentPointer, arrayValue) == key){
                    setKey(parentPointer, arrayValue, replaceKey);
                }
                arrayValue += 4 + keyLength;
            } 
            if(parentPointer == root) continueLoop = false;
            else parentPointer = getPointer(parentPointer, 4); 
        }
        /*arrayValue = 12;
        for(int i = 0; i < getNumKeys(parentPointer); i++){
            if(getPointer(parentPointer, arrayValue) == index){
                arrayValue -= keyLength;
                setKey(parentPointer, arrayValue, replaceKey);
                arrayValue += keyLength;
            }
            arrayValue += 4 + keyLength;
        } */
            
    }
}

void BPTree::caseLeafOpenDelete(int index, string key){
    int numRecords = getNumKeys(index);
    string* recordArray = new string[numRecords];

    int arrayValue = 8;
    int stay = -1;

    for(int i = 0; i < numRecords; i++){
        if(getKeyFromRecord(getRecord(index, arrayValue)) != key){
            recordArray[i] = getRecord(index, arrayValue);
        }
        else{
            stay = i;
        }
        arrayValue += recordLength;
    }

    arrayValue = 8;
    for(int i = 0; i < stay; i++){
        setRecord(index, arrayValue, recordArray[i]);
        arrayValue += recordLength;
    }
    for(int i = stay + 1; i < numRecords; i++){
        setRecord(index, arrayValue, recordArray[i]);
        arrayValue += recordLength;
    }
    if(stay == 0) replaceKey(index, key);
    
    
    numRecords--;
    setNumKeys(index, numRecords);
    delete[] recordArray;
}
    
bool BPTree::caseRedistributeLeaf(int index, string key){
    int parentPointer = getPointer(index, 4);
    
    int numKeys = getNumKeys(index);
    int arrayValue = 8;
    int sib1 = -1;
    int sib2 = -1;
    int i = 0;
    bool sib1Bool = true;
    bool sib2Bool = true;

    while(getPointer(parentPointer, arrayValue) != index){
        i++;
        arrayValue += 4 + keyLength;
    }
   

    if(i == 0){
        sib1 = getPointer(parentPointer, arrayValue + 4 + keyLength);
    }
    else if(i == getNumKeys(parentPointer)){
        sib2 = getPointer(parentPointer,arrayValue - 4 - keyLength);
    }
    else{
        sib1 = getPointer(parentPointer, arrayValue + 4 + keyLength);
        sib2 = getPointer(parentPointer,arrayValue - 4 - keyLength); 
    }

    if(sib1 == -1){
        sib1Bool = false;
    }
    else if(getNumKeys(sib1) == numKeys){
        sib1Bool = false;
    }
    if(sib2 == -1){
        sib2Bool = false;
    }
    else if(getNumKeys(sib2) == numKeys){
        sib2Bool = false;
    }

    if(!sib1Bool && !sib2Bool){
        return false;
    }
    int sibling;
    string kept = getKey(index, 8);
    caseLeafOpenDelete(index, key);
    numKeys--;
    if(sib1Bool){//adding to the end
        int arrayValue = 8;
        string addedPointer = getKey(sib1, arrayValue);
        int stay = -1;
        int j = 0;
        for(int i = 0; i < numKeys; i++){
            arrayValue += recordLength;
        }
        setRecord(index, arrayValue, addedPointer);
        arrayValue = 8;
        
        replaceKey(index, key);
        

        int numKeysSib = getNumKeys(sib1);
        int arrayValueSib = 8;
        string replaced = getKey(sib1, 8);
        for(int i = 0; i < numKeysSib - 1; i++){
            setRecord(sib1, arrayValueSib, getRecord(sib1, arrayValueSib + recordLength));
        }
        numKeysSib--;
        setNumKeys(sib1, numKeysSib);
        

        replaceKey(sib1, addedPointer);
        
        
        

    }
    else if(sib2Bool){//adding to front
        int arrayValue = 8;
        for(int i = 0; i < getNumKeys(sib2) - 1; i++){
            arrayValue += recordLength;
        }
        string replaceRecord = getRecord(sib2, arrayValue);
        arrayValue = 8;
        string replaced = getRecord(index, arrayValue);
        string stay = replaced;
        

        string temp = "";
        setRecord(index, 8, replaceRecord);
        while(getKeyFromRecord(replaced) != key){//pretty sure this is wrong
            arrayValue += recordLength;
            temp = getRecord(index, arrayValue);
            setRecord(index, arrayValue, replaced);
            replaced = temp;
        }
        replaceKey(index, stay);
        
        int numKeysSib2 = getNumKeys(sib2);
        numKeysSib2--;
        setNumKeys(sib2, numKeysSib2);
        replaceKey(index, kept);


    }
    setNumKeys(index, getNumKeys(index) + 1);

    return true;



}

bool BPTree::caseMergeLeaf(int index, string key){
    string firstIndex = getKey(index, 8);

    int parent = getPointer(index, 4);
    int sib = -1;
    int arrayValue = 8;
    bool one = false;
    if(getPointer(parent, 8) == index){
        sib = getPointer(parent, 12 + keyLength);
        one = true;
    }
    else{
        while(getPointer(parent, arrayValue) != index){
            arrayValue += 4 + keyLength;
        }
        sib = getPointer(parent, arrayValue - 4 - keyLength);
    }
    string replacedKey = getKey(sib, 8);
    caseLeafOpenDelete(index, key);
    if(one){//sib is bigger

        int arrayValue = 8;

        for(int i = 0; i < getNumKeys(index); i++){
            arrayValue += recordLength;
        }
        
        int sibValue = 8;
        for(int i = 0; i < getNumKeys(sib) + 1; i++){
            setRecord(index, arrayValue, getRecord(sib, sibValue));
            arrayValue += recordLength;
            sibValue += recordLength;
        }
        
    }
    else{//sib is smaller
        int arrayValue = 8;
        for(int i = 0; i < getNumKeys(sib); i++){
            arrayValue += recordLength;
        }
        int newKey = getPointer(index, 8);
        int sibValue = 8;
        for(int i = 0; i < getNumKeys(index) + 1; i++){
            setRecord(sib, arrayValue, getRecord(index, sibValue));
            arrayValue += recordLength;
            sibValue += recordLength;
        }
        int temp = index;
        index = sib;
        sib = temp;
    }
    
    

    setNumKeys(sib, 0);
    setNumKeys(index, 2*(n/2) - 1);

    parent = getPointer(index, 4);

    if(parent == root && getNumKeys(parent) == 1){
        root = index;
    }
    else balanceInternal(parent, sib);

    return true;

}

void BPTree::balanceInternal(int index, int child){

    if(getNumKeys(index) >= (m/2) + 1){
        caseInternalOpenDelete(index, child);
    }

    else{
        if(!caseRedistributeInternal(index, child)){
            caseMergeInternal(index, child);
        }
    }

}

void BPTree::caseInternalOpenDelete(int index, int child){
    int numKeys = getNumKeys(index);
    bool first = false;
    int arrayValue = 8;
    int j = 0;

    while(getPointer(index, arrayValue) != child){
        arrayValue += keyLength + 4;
        j++;
    }
    if(j != 0) arrayValue -= keyLength;
    else{
        setPointer(index, arrayValue, getPointer(index, arrayValue + keyLength + 4));
        arrayValue += 4;
    }
    if(j != 0){
        for(int i = j; i < numKeys; i++){
            setKey(index, arrayValue, getKey(index, arrayValue + keyLength + 4));
            arrayValue += keyLength;
            setPointer(index, arrayValue, getPointer(index, arrayValue + keyLength + 4));
            arrayValue += 4;
        }
    }
    else{
        for(int i = j; i < numKeys - 1; i++){
        setKey(index, arrayValue, getKey(index, arrayValue + keyLength + 4));
        arrayValue += keyLength;
        setPointer(index, arrayValue, getPointer(index, arrayValue + keyLength + 4));
        arrayValue += 4;
    }
    }
    numKeys--;
    setNumKeys(index, numKeys);

}

bool BPTree::caseRedistributeInternal(int parent, int child){
    int parentPointer = getPointer(parent, 4);
    int numKeys = getNumKeys(parent);
    int arrayValue = 8;
    int sib1 = -1;
    int sib2 = -1;
    int i = 0;
    bool sib1Bool = true;
    bool sib2Bool = true;

    while(getPointer(parentPointer, arrayValue) != parent){
        i++;
        arrayValue += 4 + keyLength;
    }
   

    if(i == 0){
        sib1 = getPointer(parentPointer, arrayValue + 4 + keyLength);
    }
    else if(i == getNumKeys(parentPointer)){
        sib2 = getPointer(parentPointer,arrayValue - 4 - keyLength);
    }
    else{
        sib1 = getPointer(parentPointer, arrayValue + 4 + keyLength);
        sib2 = getPointer(parentPointer,arrayValue - 4 - keyLength); 
    }

    if(sib1 == -1){
        sib1Bool = false;
    }
    else if(getNumKeys(sib1) == numKeys){
        sib1Bool = false;
    }
    if(sib2 == -1){
        sib2Bool = false;
    }
    else if(getNumKeys(sib2) == numKeys){
        sib2Bool = false;
    }

    if(!sib1Bool && !sib2Bool){
        return false;
    }
    int sibling;

    //sib1 is bigger, sib2 is smaller
    if(sib1Bool){
        string newRootKey = getKey(sib1, 12);
        int redistributedPointer = getPointer(sib1, 8);
        setPointer(redistributedPointer, 4, parent);
        setPointer(redistributedPointer, 4, parent);

        int arrayValue = 8;
        for(int i = 0; i < getNumKeys(sib1) - 1; i++){
            setPointer(sib1, arrayValue, getPointer(sib1, arrayValue + keyLength + 4));
            arrayValue += 4;
            setKey(sib1, arrayValue, getKey(sib1, arrayValue + 4 + keyLength));
            arrayValue += keyLength;
        }
        setPointer(sib1, arrayValue, getPointer(sib1, arrayValue + 4 + keyLength));

        int newIndex = getPointer(sib1, 8);
        while(sectors[newIndex][0] != 'L'){
            newIndex = getPointer(newIndex, 8);
        }

        int redistributeIndex = redistributedPointer;
        while(sectors[redistributeIndex][0] != 'L'){
            redistributeIndex = getPointer(redistributeIndex, 8);
        }
        replaceKey(newIndex, getKey(redistributeIndex, 8));

        arrayValue = 8;
        replaceKey(sib1, newRootKey);
        caseInternalOpenDelete(parent, child);
        arrayValue = 12;
        for(int i = 0; i < getNumKeys(parent); i++){
            arrayValue += 4 + keyLength;
        }
        setKey(parent, arrayValue, getKey(redistributedPointer, 8));
        setPointer(parent, arrayValue + keyLength, redistributedPointer);
        setNumKeys(parent, getNumKeys(parent) + 1);
        setNumKeys(sib1, getNumKeys(sib1) - 1);
    }
    else{

        caseInternalOpenDelete(parent, child);

        int arrayValue = 8;
        for(int i = 0; i < getNumKeys(sib2); i++){
            arrayValue += keyLength + 4;
        }
        int movedPointer = getPointer(sib2, arrayValue);
        setPointer(movedPointer, 4, parent);
        setPointer(movedPointer, 4, parent);
        setNumKeys(sib2, getNumKeys(sib2) - 1);
        string replacedKey = getKey(parent, 12);
        int movedChild = movedPointer;
        while(sectors[movedChild][0] != 'L'){
            movedChild = getPointer(movedChild, 8);
        }
        string replacement = getKey(movedChild, 8);
        arrayValue = 12;
        for(int i = 0; i < getNumKeys(parent); i++){
            arrayValue += 4 + keyLength;
        }
        arrayValue += keyLength;
        for(int i = 0; i < getNumKeys(parent); i++){
            setPointer(parent, arrayValue, getPointer(parent, arrayValue - 4 - keyLength));
            arrayValue -= keyLength;
            setKey(parent, arrayValue, getKey(parent, arrayValue - 4 - keyLength));
            arrayValue -= 4;
        }
        int finalPointer = getPointer(parent, 8);
        setPointer(parent, arrayValue, finalPointer);
        setPointer(parent, 8, movedPointer);
        while(sectors[finalPointer][0] != 'L'){
            finalPointer = getPointer(finalPointer, 8);
        }
        replacement = getKey(finalPointer, 8);
        replaceKey(movedChild, replacement);
        setKey(parent, 12, replacement);
        setNumKeys(parent, getNumKeys(parent) + 1);
        setNumKeys(sib1, getNumKeys(sib1) - 1);


    }
    return true;
}

void BPTree::caseMergeInternal(int index, int child){
    string firstIndex = getKey(index, 8);

    int parent = getPointer(index, 4);
    int sib = -1;
    int arrayValue = 8;
    bool one = false;
    if(getPointer(parent, 8) == index){
        sib = getPointer(parent, 12 + keyLength);
        one = true;
    }
    else{
        while(getPointer(parent, arrayValue) != index){
            arrayValue += 4 + keyLength;
        }
        sib = getPointer(parent, arrayValue - 4 - keyLength);
    }
    string replacedKey = getKey(sib, 8);

    caseInternalOpenDelete(index, child);
    if(one){//sib is bigger
        int arrayValue = 12;

        for(int i = 0; i < getNumKeys(index); i++){
            arrayValue += 4 + keyLength;
        }
        int newKey = getPointer(sib, 8);
        while(sectors[newKey][0] != 'L'){
            newKey = getPointer(newKey, 8);
        }
        string newPointer = getKey(newKey, 8);
        int sibValue = 8;
        for(int i = 0; i < getNumKeys(sib) + 1; i++){
            setKey(index, arrayValue, newPointer);
            arrayValue += keyLength;
            setPointer(index, arrayValue, getPointer(sib, sibValue));
            setPointer(getPointer(index, arrayValue), 4, index);
            arrayValue += 4;
            sibValue += 4;
            if(sibValue + keyLength < 300) newPointer = getKey(sib, sibValue);
            sibValue += keyLength;
        }
        
    }
    else{//sib is smaller
        int arrayValue = 12;

        for(int i = 0; i < getNumKeys(sib); i++){
            arrayValue += 4 + keyLength;
        }
        int newKey = getPointer(index, 8);
        while(sectors[newKey][0] != 'L'){
            newKey = getPointer(newKey, 8);
        }
        string newPointer = getKey(newKey, 8);
        int sibValue = 8;
        for(int i = 0; i < getNumKeys(index) + 1; i++){
            setKey(sib, arrayValue, newPointer);
            arrayValue += keyLength;
            setPointer(sib, arrayValue, getPointer(index, sibValue));
            setPointer(getPointer(sib, arrayValue), 4, sib);
            arrayValue += 4;
            sibValue += 4;
            if(sibValue + keyLength < 300) newPointer = getKey(index, sibValue);
            sibValue += keyLength;
        }
        int temp = index;
        index = sib;
        sib = temp;
    }

    setNumKeys(sib, 0);
    setNumKeys(index, n - 1);

    
    parent = getPointer(sib, 4);
    if(parent == root && getNumKeys(parent) == 1){
        root = index;
    }
    else balanceInternal(parent, sib);

}

bool BPTree::deleteBP(string key){
    if(key.length() != keyLength || !find(key)){
        cout << "Invalid Key entered" << endl;
        return false;
    }
    int index = findIndex(key);
    if(getNumKeys(index) >= (n/2) + 1){
        caseLeafOpenDelete(index, key);
    }
    else{
        if(!caseRedistributeLeaf(index, key)){
            caseMergeLeaf(index, key);
        }
    }
    return true;
}

void BPTree::deletePublic(string key){
    deleteBP(key);
}
