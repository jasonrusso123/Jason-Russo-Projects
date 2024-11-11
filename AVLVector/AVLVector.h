#include "Node.cpp"

using namespace std;


class AVLVector{
    public:
        AVLVector();
        ~AVLVector();
        int elementAt(int r);
        int replaceAt(int r, int e);
        int insertAt(int r, int e);
        int deleteRank(int r);
        void print();
        Node* find(int r, int prior_rank, Node* node);
        Node* root;
        int treeSize;

    
    private:


        int elementAtRank(int r, int prior_rank, Node* node);
        int replaceAtRank(int r, int e, int prior_rank, Node* node);
        int insertAtRank(int r, int e, int prior_rank, Node* node);
        int removeAtRank(int r, int prior_rank, Node* node);


        void RRrestructure(Node* node);
        void LLrestructure(Node* node);
        void RLrestructure(Node* node);
        void LRrestructure(Node* node);
        void restructure(Node* node);
        void printAll(int prior_rank, Node* node);

        Node* findLeftMax(Node* node);

        void destroy(Node* root);

        void rebalance(Node* node);

};


class AVLBasic{
    public:
        AVLBasic();
        ~AVLBasic();
        AVLBasic(AVLVector& AVL);
        
        int rankOf(int e, AVLVector& AVL);
        int insertAt(int r, int e, AVLVector& AVL);
        int replaceAt(int r, int a, int e, AVLVector& AVL);
        //int deleteRank(int r, int e, int newVal, AVLVector& AVL);
        int removeAtRank(int r, int e, int newVal, NodeBasic* node, AVLVector& AVL);
        void print();

        NodeBasic* rankFinder(int e, int r, NodeBasic* node, AVLVector& AVL);

        NodeBasic* root;


    
    private:
        //int findPriorRank(Node* node, AVLVector& AVL);

        int treeSize;
        Node* AVLRoot;

        int rankOfElement(int e, NodeBasic* node, AVLVector& AVL);
        int replaceElement(int r, int a, int e, NodeBasic *node, AVLVector& AVL); //implemented
        int insertAtRank(int r, int e, NodeBasic* node, AVLVector& AVL);

        NodeBasic* findLeftMax(NodeBasic* node);

        NodeBasic* find(int e, NodeBasic* node);

        void RRrestructure(NodeBasic* node);
        void LLrestructure(NodeBasic* node);
        void RLrestructure(NodeBasic* node);
        void LRrestructure(NodeBasic* node);
        void rebalance(NodeBasic* node);

        void printAll(NodeBasic* node);

        void destroy(NodeBasic* root);
        int findRank(Node* node, AVLVector& AVL);

};