#include "Node.cpp"

class Polynomial{
    
    private:
        Node *header;
        Node *tail;
    
    public:
        Polynomial();
        Polynomial(int input1[]);
        ~Polynomial();

        void add(Polynomial&, Polynomial&);
        void subtract(Polynomial&, Polynomial&);
        void mult(Polynomial&, Polynomial&);
        void mod(Polynomial&, Polynomial&);

        void insert(unsigned ndx, int uno, int dos);
        void initialize();

        void zero();
        void arbitrary(int input[]);

        void operator+(const Polynomial&);
        void operator-(const Polynomial&);
        Polynomial& operator=(const Polynomial& rhs);

        void exponent(Polynomial&, int ndx);
        void print(int input[]);
        void output();
        int eval(int input[], unsigned ndx);


        unsigned count;


};

