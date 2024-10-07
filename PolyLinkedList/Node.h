#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>

using namespace std;

class Node
{
    public:
        int coeff;
        int exponent;
        Node *next;
        Node *previous;
        Node(int coeff = 0, int exponent = 0, Node *next = NULL, Node *previous = NULL);
        
};