#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class BPTree{

    public:
        BPTree(int keyLength, int recordLength);
        ~BPTree();

        void printAllPublic();
        int insertPublic(string record);
        void deletePublic(string key);
        bool searchAllPublic(string key);
        void printSectorPublic(int sectorAddress);
        void printRoot();

    private:
        int root;
        int m;
        int n;
        int keyLength;
        int recordLength;
        char sectors[4000][300];
        vector<int> freeNodeVector;

        int insert(string record);
        bool deleteBP(string key);
        void print(int index);
        void printLeaf(int address);
        bool search(string key);
        bool find(string key);

        void printSector(int address);

        bool checkFirstGreater(string key1, string key2);

        int getPointer(int index, int arrayValue);
        void setPointer(int index, int arrayValue, int pointer);

        int getNumKeys(int index);
        void setNumKeys(int index, int numKeys);

        string getKey(int index, int arrayValue);
        void setKey(int index, int arrayValue, string key);

        string getRecord(int index, int arrayValue);
        void setRecord(int index, int arrayValue, string record);

        int asciiConvert(char character);
        string asciiIntConvert(int integer, int count);

        int splitLeaf(int index, string newRecord);
        int splitInternal(int index, string newKey, int originalPointer, int newPointer);

        string getKeyFromRecord(string record);

        int getNewNode();

        int createNewRoot(int oldRoot, string key, int newNode);

        int findIndex(string key);

        void caseLeafOpenDelete(int index, string key);
        void caseInternalOpenDelete(int index, int child);
        bool caseRedistributeLeaf(int index, string key);
        bool caseMergeLeaf(int index, string key);
        void balanceInternal(int index, int child);
        void replaceKey(int index ,string key);
        bool caseRedistributeInternal(int parent, int child);
        void caseMergeInternal(int parent, int child);



};