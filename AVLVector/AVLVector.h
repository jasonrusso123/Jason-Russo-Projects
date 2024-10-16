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
    
    private:
        Node* root;

        int treeSize;

        int elementAtRank(int r, int prior_rank, Node* node);
        int replaceAtRank(int r, int e, int prior_rank, Node* node);
        int insertAtRank(int r, int e, int prior_rank, Node* node);
        int removeAtRank(int r, int prior_rank, Node* node);

        Node* find(int r, int prior_rank, Node* node);

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