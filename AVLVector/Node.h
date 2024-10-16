#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>

using namespace std;

class Node{
    public:
        Node *left;
        Node *right;
        Node *parent;
        int value;
        int leftSize;
        int height;
        int balanceFactor;

        
        int getSize(){return leftSize;};
        int getHeight();
        int getBalanceFactor();

        void setHeight();
        Node();
        ~Node();
        Node(int value, Node *left, Node *right, Node *parent);

};