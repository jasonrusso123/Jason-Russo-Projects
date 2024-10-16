#include "NodeBasic.h"

NodeBasic::NodeBasic(){
    value = 0;
    rank = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
}

NodeBasic::~NodeBasic(){}

NodeBasic::NodeBasic(int val, int rank){
    value = val;
    rank = rank;
    left = NULL;
    parent = NULL;
    right = NULL;
}

