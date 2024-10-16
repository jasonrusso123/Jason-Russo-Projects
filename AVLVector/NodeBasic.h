#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>

using namespace std;

class NodeBasic{
    public:
        NodeBasic *left;
        NodeBasic *right;
        NodeBasic *parent;
        int value;
        int leftHeight;
        int rightHeight;
        int rank;
        
        NodeBasic();
        ~NodeBasic();
        NodeBasic(int value, int rank);

};