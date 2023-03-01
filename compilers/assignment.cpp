#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//fuction to check if the length of a string item is greater than 1
//used to check if it is needed to split the item into individual items
void PrintStack(stack<string> s)
{
    // If stack is empty then return
    if (s.empty())
        return;


    string x = s.top();

    // Pop the top element of the stack
    s.pop();

    // Recursively call the function PrintStack
    PrintStack(s);

    // Print the stack element starting
    // from the bottom
    cout << x << "";

    // Push the same element onto the stack
    // to preserve the order
    s.push(x);
}

bool Length(string ss){
    int len = ss.length();
    if(len!=1){
        return true;
        
    }
    else{
        return false;
    }
}

//function to examine if the string is syntactically correct
//ss stands for symbol string

bool syntaxExaminer(string ss){ //the parameter is the string to be examined
        
        int stringLength = ss.length(); //length of the given string
        
        string op = "+-*|"; //the operators included in our syntax 
        
        //the output to main
        bool iss = true; //iss --> is symbol string

        if (!(((ss[0] == '(')) && (ss[stringLength-1] == ')'))){ //is the string contained in brackets?

                iss = false;
                return iss; //string is not syntactically correct; immediate stop of the function

        }
        else{
                for (int i = 0; i < stringLength; i++){

                       if (isdigit(ss[i])){ //are digits included in the string?

                               iss = false;
                               return iss; //string is not syntactically correct; immediate stop of the function
                               
                       }
                       else if (i != (stringLength - 1)){ //if ss[i] is not the last item of the string array

                               for (int j = 0; j < 4; j++){

                                       if ((!(((ss[i]) != (op[j])) || ((ss[i + 1]) != (op[j]))))){ //checking for sequentially symbols

                                               iss = false;
                                               return iss; //string is not syntactically correct; immediate stop of the function

                                       }
                               }
                       }
                       else{
                                for (int j = 0; j < 4; j++){

                                        if (!((ss[i]) != (op[j]))){ //checking if the string includes only letters; not a symbol string

                                                iss = false;
                                                return iss; //string is not syntactically correct; immediate stop of the function
                                        }

                                }
                               return iss; //string is syntactically correct; return true

                       }
                }
        }
        return iss; //string is syntactically correct; return true
}

int main(){

        string symbolString;  
        cout << "Enter a string"; //message to the user
        cin >> symbolString; //getting the user's input

        //the example symbol string
        symbolString = "((b-a)*(a+b))";

        //calling syntaxExaminer function to check if the string input is a syntactically correct symbol string
        bool isCorrect = syntaxExaminer(symbolString); 

        while(!(isCorrect)){ //if not

                cout << "This string is not the requested symbol string \n"; //message to the user
                cout << "Enter a string"; //message to the user
                cin >> symbolString; //getting the user's input
                isCorrect = syntaxExaminer(symbolString); 
        }

        vector<string> stringArray;
        int stringLength = symbolString.length(); //length of the given string
        string stringItem;
        for (int i = 0; i < stringLength; i++){
                stringItem = symbolString[i];
                stringArray.push_back(stringItem);
        }
        
        string termSymbols [8] = {"(",")","a","b","ε","+","-","*"}; //terminal symbols
        string nontSymbols [4] = {"S","X","Y","Z"}; //non terminal symbols

        vector<string> x;
    
        //insterting the beggining symbol (S) into the x
        x.push_back("(");
        x.push_back("X");
        x.push_back(")");

        //the given production rules
        string prodRules [4][5] = {"S","(X)","0","0","0",
                                  "X","YZ","0","0","0",
                                  "Y","a","b","S","0",
                                  "Z","*X","-X","+X","ε"
                                  }; 
        
        int vectorSize;
        int strArlen = stringArray.size(); //size of stringArray
        while (strArlen != 0){

                int flag1; //holds the value of j (x pointer)
                int flag2; //holds the value of i (nontSymbols pointer)
                int k = 1; //pointer used later in while loop
                int zeros = 0; //total zeros in a prodRules line
                //helps to understand whether a symbol has more than one possible replacements

                bool found = false; //found a non terminal symbol in vector x
                bool replaced = false; //replaced a symbol in vector x
                
                string pvalue; //parameter value to parse the string item through the function
                string temp1; //temporary value 1
                string temp2; //temporary value 2

                vectorSize = x.size(); //declaring the vector size

                for (int i = 0; i < 4; i++){
                        for(int j = 0; j < vectorSize; j++){
                                //found the desired non terminal symbol
                                if ((x[j] == nontSymbols[i]) && found == false){
                                        flag1 = j;
                                        flag2 = i;
                                        found = true;
                                        break; //break the loop
                                }
                        }
                }
                
                //how many 0's ?
                for (int j = 0; j < 5; j++){
                        if (prodRules[flag2][j] == "0"){
                                zeros++;
                        }
                }
                //if zeros == 3 --> one possible replacement
                if (zeros == 3){
                        stringItem = prodRules[flag2][1];
                        int lenSI = stringItem.length(); //length of stringItem

                        if (Length(stringItem)){ //if length != 1 --> true
                        //item needs to be splitted
                            while (k < ( stringItem.length())){ //while k in range of stringItem
                                pvalue = stringItem[k]; //item to insert into x
                                x[flag1] = stringItem[0]; //replacing x[flag1] with the new value

                                flag1++;

                                x.insert(x.begin() + (flag1), pvalue); //inserting the new items from pointer flag1 and after (not from the back)                                
                                k++;
                                replaced = true; //symbol is replaced
                            }
                        }
                        else{ //if length != 1 --> false

                            x[flag1] = prodRules[flag2][1]; //replacing with the only option
                            replaced = true; //symbol is replaced
                        }
                }
                else{
                        for (int i = 0; i < strArlen; i++){
                                for (int j = 0; j < 4; j++){

                                        temp1 = prodRules[flag2][j];
                                        temp2 = stringArray[i];

                                        if ((temp1 == temp2)&&(replaced != true)){ 
                                                x[flag1] = prodRules[flag2][j]; 
                                                replaced = true; //symbol is replaced

                                                break; //break loop
                                        }

                                }
                        }
                        found = false; //redeclaring value found
                        while (!(replaced)){ //while symbl is not replaced
                                if (prodRules[flag2][0] == "Z"){ //if procedure rule = Z
                                        for (int i = 0; i < stringLength; i++){
                                                if (((stringArray[i] == "*")|(stringArray[i] == "+")|(stringArray[i] == "-"))&& found == false){ //which operator is the next symbol?
                                                        x[flag1] = stringArray[i]; //replacing x[flag1] with the operator
                                                        x.insert(x.begin() + (flag1+1), "X"); //inserting X (not from the back)                               
                                                        found = true; //operator found
                                                        replaced = true; //symbol is replaced
                                                }

                                        }
                                        if (!found){ //next symbol is not an operator
                                                x.insert(x.begin() + (flag1+1), "E"); //replace with blank symbol string
                                                replaced = true; //symbol is replaced
                                        }
                                }
                                else{ //symbol is not a or b nor Z
                                        x.insert(x.begin() + (flag1+1), "S");
                                        replaced = true; //symbol is replaced 
                                }


                        }
                }
                strArlen = stringArray.size(); //size of stringArray
                vectorSize = x.size(); //redeclaring vectorSize
                 int i = 0;
                int j = 0;

                while(j < strArlen){
                        if (x[i] == stringArray[j]){
                                stringArray.erase(stringArray.begin());
                                break;
                        j++;
                        }
                        i++;
                        
                        strArlen = stringArray.size();
                }

    // given production rules
    string prodtable[5][9] = {" ", "(", ")", "*", "-", "+", "a", "b", "$",
                              "S", "(X)", " ", " ", " ", " ", " ", " ", " ",
                              "X", "YZ", " ", " ", " ", "", "YZ", "YZ", " ",
                              "Y", "S", " ", " ", " ", " ", "a", "b",   " ",
                              "Z", " ", "^", "*X", "-X", "+X", " ", " ", " ",
    };

    stack<string> stack;

    stack.push("$");
    stack.push("S");


    vector<string> expression = {"(", "(", "b", "-", "a", ")", "*", "(", "a", "+", "b", ")", ")",
                                 "$"}; //given symbol string
     i = 0;
    while (expression.size() != 0) {
            if ((stack.top() == expression[i]) && (expression[i] != "$")) {
                //cout << "recognition!" << endl;
                //cout << "stack top is: " << stack.top();
                stack.pop();
                expression.erase(expression.begin());
                cout << "Stack: ", PrintStack(stack);
                cout<<" Input: ";
                for (int i = 0; i < expression.size(); i++) { cout << expression[i]; }
                cout <<" Table element: -"<<endl;


            } else if ((stack.top() == expression[i]) && (expression[i] == "$")) {
                cout << "THIS IS THE END!!\n" << endl;
                cout << "Stack: ", PrintStack(stack);
                cout<<" Input: ";
                for (int i = 0; i < expression.size(); i++) { cout << expression[i]; }
                cout <<" Table element: -"<<endl;

                break;
            } else { //go to the table
                //cout<<"i am here"<<endl;
                int row;
                int column;
                for (int i = 0; i < 4; i++) {
                    if (prodtable[i][0] == stack.top()) {
                        row = i;
                    }
                }
                for (int j = 0; j < 8; j++) {
                    if (prodtable[0][j] == expression[j]) {
                        column = j;
                    }
                }
                if ((prodtable[row][column] != "") || (prodtable[row][column] != "^")) {
                    //cout<<"yesss"<<endl;

                    string cell = prodtable[row][column];
                    vector<string> r_replace;
                    //int stringLength = symbolString.length(); //length of the given string
                    string symbol;
                    //cout<<"cell is:"<<cell;
                    if (cell.length() > 1) {
                        for (int i = 0; i < cell.length(); i++) {
                            symbol = cell[i];
                            r_replace.push_back(symbol);
                            //cout<<"\npush back: "<<symbol<<endl;
                        }

                        cout << "Stack: ", PrintStack(stack);
                        cout<<" Input: ";
                        for (int i = 0; i < expression.size(); i++) { cout << expression[i]; }
                        cout <<" Table element: M("<<stack.top()<<","<<expression[0]<<")"<<endl;


                        stack.pop();

                        for (int i = r_replace.size() - 1; i >= 0; i--) {
                            string item = r_replace[i];
                            //cout<<item<<endl;
                            stack.push(item);
                            //cout  <<"stack pop is: "<< stack.top();
                        }

                    } else {
                        stack.pop();
                        stack.push(cell);
                    }
                    cout << "Stack: ", PrintStack(stack);
                    cout<<" Input: ";
                    for (int i = 0; i < expression.size(); i++) { cout << expression[i]; }
                    cout <<" Table element: M("<<stack.top()<<","<<expression[0]<<")"<<endl;

                } else if (prodtable[row][column] == "^") {
                    stack.pop();

                    cout << "Stack: ", PrintStack(stack);
                    cout<<"Input: ";
                    for (int i = 0; i < expression.size(); i++) { cout << expression[i]; }
                    cout <<" Table element: -"<<endl;
                }
            }
            i++;
    }    }
}