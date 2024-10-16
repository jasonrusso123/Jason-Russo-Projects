#include "NodeBasic.cpp"

using namespace std;


class AVLBasic{
    public:
        AVLBasic();
        ~AVLBasic();
        
        int rankOf(int e);
    
    private:
        NodeBasic* root;

        int rankOfElement(int e);
        void replaceAtRank(int r, int e);
        int insertAtRank(int r, int e);
        void removeAtRank(int r);

        void RRrestructure(NodeBasic* node);
        void LLrestructure(NodeBasic* node);
        void RLrestructure(NodeBasic* node);
        void LRrestructure(NodeBasic* node);

        void printAll();

        void destroy(NodeBasic* root);

};