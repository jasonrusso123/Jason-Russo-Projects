#include "Polynomial.h"

void Polynomial::initialize(){
    
    this->header = new Node(0, 0, NULL, NULL);
    this->tail = new Node(0, 0, NULL, NULL);
    
    this->header->next = this->tail;
    this->tail->previous = this->header;
    this->count = 0;
}

void Polynomial::zero(){
    
    this->insert(0, 0, 0);
    this->count = 1;
    this->output();
    

}

Polynomial::Polynomial()
{
    initialize();
}

Polynomial::Polynomial(int input[]){

    initialize();
    int num = input[0];
    this->count = num;
    int ndx = 0;
    Node *current = this->header->next;
    Node *second = this->header;

    for(int i = 1; i < (2 * num + 1); i += 2){
        Node *addMe = new Node(0, 0, NULL, NULL);
        
        addMe->coeff = input[i];
        addMe->exponent = input[i+1];

        addMe->next = current;
        addMe->previous = second;
        second->next = addMe;
        current->previous = addMe;

        current = this->tail;
        second = current->previous;

        
        //this->insert(ndx, input[i], input[i+1] );
    }

    this->count = num;
}


void Polynomial::arbitrary(int input[]){

    Polynomial arb(input);
    arb.output();

}

Polynomial::~Polynomial()
{
     
     Node *current = this->header;
     Node *nextNode = nullptr;


     while (current != nullptr){

        
        nextNode = current->next;
        delete current;
        current = nextNode;

        
     }

 
}


void Polynomial::insert(unsigned ndx, int coeff1, int exp1){
    Node *addMe = new Node(0, 0, NULL, NULL);
    addMe->coeff = coeff1;
    addMe->exponent = exp1;

    if (this->count == 0) {
        // Insertion into an empty list
        
        this->header->next = addMe;
        addMe->previous = this->header;
        addMe->next = this->tail;
        this->tail->previous = addMe;

    } 
    else {
        // Insertion at other positions in the list
        Node *current = this->header->next;
        Node *second = this->header;
        

        for (unsigned i = 0; i < ndx; i++) {
            second = current;
            current = current->next;
        }

        
        addMe->next = current;
        addMe->previous = second;
        second->next = addMe;
        current->previous = addMe;
    }

 
}

void Polynomial::operator+(const Polynomial& object){

    Node *here = NULL;
    here = this->header->next;
    int count1 = this->count;

    Node *current = NULL;
    current = object.header->next;

    int i = 0;

    int addArray[2 * count1 + 2 * object.count + 1];

    while(current != NULL && here != NULL){
        if(current->exponent > here->exponent){
            //Final.insert(i, current->coeff, current->exponent);
            addArray[2*i + 1] = current->coeff;
            addArray[2*i+2] = current->exponent;
            current = current->next;
            i++;
        }

        else if(current->exponent < here->exponent){
            //Final.insert(i, here->coeff, here->exponent);
            addArray[2*i + 1] = here->coeff;
            addArray[2*i+2] = here->exponent;
            here = here->next;
            i++;
        }

        else if(current->exponent == here->exponent){
            int add = here->coeff + current->coeff;

            if(add == 0){
                here = here->next;
                current = current->next;
            }

            else if(here == this->tail && current != object.tail){
                //Final.insert(i, current->coeff, current->exponent);
                addArray[2*i + 1] = current->coeff;
                addArray[2*i+2] = current->exponent;
                current = current->next;
                i++;
            }

            else if(here != this->tail && current == object.tail){
                //Final.insert(i, here->coeff, here->exponent);
                addArray[2*i + 1] = here->coeff;
                addArray[2*i+2] = here->exponent;
                here = here->next;
                i++;
            }

            else{
                //Final.insert(i, add, here->exponent);
                addArray[2*i + 1] = add;
                addArray[2*i+2] = current->exponent;
                current = current->next;
                here = here->next;
                i++;
            }
   
        }
    }

    addArray[0] = i;
    Polynomial Final(addArray);

    *this = Final;

}

Polynomial& Polynomial::operator=(const Polynomial& rhs){
    Node* current = this->tail->previous;
    Node* other = this->tail->previous;
    for(int i = 0; i < this->count; i++){
        current = current -> previous;
        current->next = this->tail;
        tail->previous = current;
        delete other;
        other = current;
    }

    int j = 0;
    Node* rhsPoint = rhs.header->next;
    /*int equalArray[2 * rhs.count + 1];
    equalArray[0] = rhs.count;




    while(j < rhs.count){
        equalArray[2*j + 1] = rhsPoint->coeff;
        equalArray[2*j + 2] = rhsPoint->exponent;
        j++;
        rhsPoint = rhsPoint->next;
    }*/

    Node *first = this->header->next;
    Node *second = this->header;

   for(int i = 1; i < (2 * rhs.count + 1); i += 2){
        Node *addMe = new Node(rhsPoint->coeff, rhsPoint->exponent, NULL, NULL);

        addMe->next = first;
        addMe->previous = second;
        second->next = addMe;
        first->previous = addMe;

        first = this->tail;
        second = first->previous;

        rhsPoint = rhsPoint->next;

        
        //this->insert(ndx, input[i], input[i+1] );
    }

    this->count = rhs.count;

    return *this;
    

}

void Polynomial::add( Polynomial& lhsObj, Polynomial& rhsObj)
{ 
    
    lhsObj.operator+(rhsObj);
    lhsObj.output();

    
}

void Polynomial::operator-(const Polynomial& object){

    Node *here = NULL;
    here = this->header->next;
    int count1 = this->count;

    Node *current = NULL;
    current = object.header->next;

    int i = 0;

    int addArray[2 * count1 + 2 * object.count + 1];

    while(current != NULL && here != NULL){
        if(current->exponent > here->exponent){
            //Final.insert(i, current->coeff, current->exponent);
            addArray[2*i + 1] = 0 - current->coeff;
            addArray[2*i+2] = current->exponent;
            current = current->next;
            i++;
        }

        else if(current->exponent < here->exponent){
            //Final.insert(i, here->coeff, here->exponent);
            addArray[2*i + 1] = here->coeff;
            addArray[2*i+2] = here->exponent;
            here = here->next;
            i++;
        }

        else if(current->exponent == here->exponent){
            int add = here->coeff - current->coeff;

            if(add == 0){
                here = here->next;
                current = current->next;
            }

            else if(here == this->tail && current != object.tail){
                //Final.insert(i, current->coeff, current->exponent);
                addArray[2*i + 1] = 0 - current->coeff;
                addArray[2*i+2] = current->exponent;
                current = current->next;
                i++;
            }

            else if(here != this->tail && current == object.tail){
                //Final.insert(i, here->coeff, here->exponent);
                addArray[2*i + 1] = here->coeff;
                addArray[2*i+2] = here->exponent;
                here = here->next;
                i++;
            }

            else{
                //Final.insert(i, add, here->exponent);
                addArray[2*i + 1] = add;
                addArray[2*i+2] = current->exponent;
                current = current->next;
                here = here->next;
                i++;
            }
   
        }
    }

    addArray[0] = i;
    Polynomial Final(addArray);

    *this = Final;

}



void Polynomial::subtract( Polynomial& lhsObj, Polynomial& rhsObj)
{ 
    
    lhsObj.operator-(rhsObj);
    lhsObj.output();
    
}


 

void Polynomial::mult( Polynomial& lhsObj, Polynomial& rhsObj){
    Node *here = NULL;
    here = lhsObj.header->next;

    Node *current = NULL;
    current = rhsObj.header->next;
    int i = 0;

    Polynomial multi;

    while(here != lhsObj.tail){

        int multArray[rhsObj.count * 2 + 1];

        multArray[0] = rhsObj.count;
        

        while(current != rhsObj.tail){
            int multiplied = here->coeff * current->coeff;
            int expFinal = here->exponent + current->exponent;

            multArray[2*i + 1] = multiplied;
            multArray[2 * i + 2] = expFinal;

            current = current->next;

            i++;

        }
        here = here->next;
        Polynomial mult2(multArray);
        /*Polynomial mult1;
        mult1 = *mult2;*/
        
        multi.operator+(mult2);
        

        current = rhsObj.header->next;
        

        i = 0;



    }
    
    
    multi.output();
    lhsObj = multi;

}

void Polynomial::mod(Polynomial& lhsObj, Polynomial& rhsObj){
    Node* lhs = NULL;
    lhs = lhsObj.header->next;
    Node* rhs = NULL;
    rhs = rhsObj.header->next;

    int divCo = 0;
    int divEx = 0;

    int modArray[rhsObj.count * 2 + 3];
    modArray[0] = rhsObj.count;
    
    while (lhs->exponent >= rhs->exponent){
        divCo = lhs->coeff / rhs->coeff;
        divEx = lhs->exponent - rhs->exponent;
        int j = 0;
        while(rhs != rhsObj.tail){

            modArray[2*j + 1] = divCo * rhs->coeff;
            modArray[2*j + 2] = divEx + rhs->exponent;

            rhs = rhs->next;
            j++;
        }
        Polynomial modPoly(modArray);
        lhsObj.subtract(lhsObj, modPoly);
        rhs = rhsObj.header->next;
        lhs = lhsObj.header->next;        
    }
    lhsObj.output();
}

void Polynomial::exponent(Polynomial& Poly, int ndx){

    int c = 1;
    int k = 1;
    while (k < (ndx / 2)){
        k *= 2;
        c++;
    }

    int* expArray = new int[c + 1];
    expArray[0] = k;

    ndx = ndx - k;

    int j = 0;


    int i = 1;

    while (ndx >= i){
        int subtracted = ndx - i;

        if(subtracted < i){
            expArray[j+1] = i;
            j++;
            ndx = subtracted;
            i = 1;
        }
        else{
            i *= 2;
        }

    }

    int in[3];
    in[0] = 1;
    in[1] = 1;
    in[2] = 0;
    Polynomial Final(in);
    
    Polynomial newPoly1;
    newPoly1.operator=(Poly);
    Polynomial newPoly2;
    newPoly2.operator=(Poly);

    for(int z = 0; z < j + 1; z++){
        int k = 1;
        while(k < expArray[z]){
            newPoly1.mult(newPoly1, newPoly1);

            newPoly2.operator=(newPoly1);

            k = 2*k;
        }

        Final.mult(Final, newPoly1);
        newPoly1 = Poly;
        newPoly2 = Poly;

    }

    delete[] expArray;

    cout << "Exponent Final Result: ";
    Final.output();

}

int Polynomial::eval(int input1[], unsigned ndx){
    Polynomial eval1(input1);
    int sum = 0;
    Node *current = eval1.tail->previous;

    int multiplier = 0;
    int tempMult = 1;
    int tempExp = 0;

    int i = 0;

    while(current != eval1.header){

        multiplier = pow(ndx, current->exponent - tempExp);//stores ndx to the power of the current exponent
                                                            //minus the previous
        tempMult *= multiplier;
        sum += current->coeff * tempMult;
        tempExp = current->exponent;
        i++;
        current = current->previous;

    }
    
    /*Node *current = eval1.header->next;
    int sum = 0;
    for(int i = 0; i < eval1.count; i++){
        sum += current->coeff * pow(ndx, current->exponent);
        current = current->next;
    }*/
    cout << sum << endl;
    return sum;

}

void Polynomial::print(int input[]){
    Polynomial Print(input);
    Print.output();
}

void Polynomial::output(){

    Node *current = this->header->next;
    cout << this->count << " ";
    while(current != this->tail){
        cout << current->coeff << "x^" << current->exponent << " ";
        current = current->next;
    }
    cout << endl;

}