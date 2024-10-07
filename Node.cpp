#include "Node.h"

Node::Node(int coef, int exp, Node* nex, Node* prev){
    coeff = coef;
    exponent = exp;
    next = nex;
    previous = prev;
}