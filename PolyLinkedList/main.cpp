#include "Polynomial.cpp"

int main(){

    /*int array1[3];
    array1[0] = 1;
    array1[1] = 2;
    array1[2] = 0;

    int array2[5];
    array2[0] = 2;
    array2[1] = 3;
    array2[2] = 2;
    array2[3] = 1;
    array2[4] = 1;

    Polynomial One(array1);
    One.output();

    Polynomial Two(array2);
    Two.output();

    Two = One;
    Two.output();*/
    
    string input = "";
    
    cin >> input;

    while(input != "QUIT"){
        if(input == "ZERO"){
            Polynomial Final;
            Final.zero();
        }
        if(input == "ARBITRARY"){
            int counter;
            cin >> counter;
            int multCounter = 2 * counter + 1;
            int* inArray = new int[multCounter];

            inArray[0] = counter;

            for (int i = 1; i < multCounter; i++){
                int j;
                cin >> j;
                inArray[i] = j;
            }

            Polynomial Test;
            Test.arbitrary(inArray);
            delete[] inArray;
        }

        if(input == "PRINT"){
            int counter;
            cin >> counter;
            int multCounter = 2 * counter + 1;
            int* inArray = new int[multCounter];

            inArray[0] = counter;

            for (int i = 1; i < multCounter; i++){
                int j;
                cin >> j;
                inArray[i] = j;
            }

            Polynomial Test;
            Test.print(inArray);
            delete[] inArray;
        }

        if(input == "EVAL"){
            int counter;
            cin >> counter;
            int multCounter = 2 * counter + 1;
            int* inArray = new int[multCounter];

            inArray[0] = counter;

            for (int i = 1; i < multCounter; i++){
                int j;
                cin >> j;
                inArray[i] = j;
            }

            Polynomial Test;
            int evalCoeff;
            cin >> evalCoeff;

            Test.eval(inArray, evalCoeff);
            delete[] inArray;
        }

        if (input == "ADD"){
            int counter;
            cin >> counter;
            int multCounter = 2 * counter + 1;
            int* inArray = new int[multCounter];

            inArray[0] = counter;

            for (int i = 1; i < multCounter; i++){
                int j;
                cin >> j;
                inArray[i] = j;
            }

            Polynomial add1(inArray);

            int counter2;
            cin >> counter2;
            int multCounter2 = 2 * counter2 + 1;
            int* inArray2 = new int[multCounter2];

            inArray2[0] = counter2;

            for (int i = 1; i < multCounter2; i++){
                int j;
                cin >> j;
                inArray2[i] = j;
            }

            Polynomial add2(inArray2);
            add1.add(add1, add2);
            delete[] inArray;
            delete[] inArray2;
        
        }
        if (input == "SUB"){
            int counter;
            cin >> counter;
            int multCounter = 2 * counter + 1;
            int* inArray = new int[multCounter];

            inArray[0] = counter;

            for (int i = 1; i < multCounter; i++){
                int j;
                cin >> j;
                inArray[i] = j;
            }

            int counter2;
            cin >> counter2;
            int multCounter2 = 2 * counter2 + 1;
            int* inArray2 = new int[multCounter2];

            inArray2[0] = counter2;

            for (int i = 1; i < multCounter2; i++){
                int j;
                cin >> j;
                inArray2[i] = j;
            }

            Polynomial subtract1(inArray);
            Polynomial subtract2(inArray2);
            subtract1.subtract(subtract1, subtract2);
            delete[] inArray;
            delete[] inArray2;
        
        }

        if(input == "MULT"){
            int counter;
            cin >> counter;
            int multCounter = 2 * counter + 1;
            int* inArray = new int[multCounter];

            inArray[0] = counter;

            for (int i = 1; i < multCounter; i++){
                int j;
                cin >> j;
                inArray[i] = j;
            }

            Polynomial mult1(inArray);

            int counter2;
            cin >> counter2;
            int multCounter2 = 2 * counter2 + 1;
            int* inArray2 = new int[multCounter2];

            inArray2[0] = counter2;

            for (int i = 1; i < multCounter2; i++){
                int j;
                cin >> j;
                inArray2[i] = j;
            }

            Polynomial mult2(inArray2);

            mult1.mult(mult1, mult2);
            delete[] inArray;
            delete[] inArray2;


        }

        if(input == "MOD"){
            int counter;
            cin >> counter;
            int multCounter = 2 * counter + 1;
            int* inArray = new int[multCounter];

            inArray[0] = counter;

            for (int i = 1; i < multCounter; i++){
                int j;
                cin >> j;
                inArray[i] = j;
            }

            Polynomial mult1(inArray);

            int counter2;
            cin >> counter2;
            int multCounter2 = 2 * counter2 + 1;
            int* inArray2 = new int[multCounter2];

            inArray2[0] = counter2;

            for (int i = 1; i < multCounter2; i++){
                int j;
                cin >> j;
                inArray2[i] = j;
            }

            Polynomial mult2(inArray2);

            mult1.mod(mult1, mult2);
            delete[] inArray;
            delete[] inArray2;


        }

        if(input == "EXP"){
            int counter;
            cin >> counter;
            int multCounter = 2 * counter + 1;
            int* inArray = new int[multCounter];

            inArray[0] = counter;

            for (int i = 1; i < multCounter; i++){
                int j;
                cin >> j;
                inArray[i] = j;
            }

            Polynomial Test(inArray);
            int expCoeff;
            cin >> expCoeff;

            Test.exponent(Test, expCoeff);
            delete[] inArray;
        }


        cin >> input;

    }
    return 0;
}