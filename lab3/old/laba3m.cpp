#include <iostream>
//
using namespace std;
using std::cout;
using std::endl;
//
//Stack code
#define MAX_STACK 100
float _stack[MAX_STACK];
int tos = 0;

bool full(){
    return tos >= MAX_STACK - 1;
}

bool empty(){
    return tos == 0;
}

void push(float value){
    if (full()){
        return;
    }
    tos++;
    _stack[tos] = value;
}

float pop(){
    float t = _stack[tos];
    tos--;
    return t;
}
//Enf of stack code

bool is_operator(char c){
    //Check for operators.
    switch (c){
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

double reverse_notation(string expression){
    unsigned i = 0;
    float v1 = 0, v2 = 0, ret = 0;
    string tok = "";

    while (i < expression.length()){
        //Skip white space
        while (isspace(expression[i])){
            i++;
        }
        //Check for digits and .
        if (isdigit(expression[i]) || expression[i] == '.'){
            while (isdigit(expression[i]) || expression[i] == '.'){
                tok += expression[i];
                i++;
            }
            //Push on stack number.
            push(atof(tok.c_str()));
            tok = "";
        }
        //Check for operator
        else if (is_operator(expression[i])){
            if (expression[i] == '+'){
                v1 = pop();
                v2 = pop();
                ret = (v1 + v2);
            }
            if (expression[i] == '-'){
                v1 = pop();
                v2 = pop();
                ret = v2 - v1;
            }
            if (expression[i] == '*'){
                v1 = pop();
                v2 = pop();
                ret = (v1 * v2);
            }
            if (expression[i] == '/'){
                v1 = pop();
                v2 = pop();
                ret = (v2 / v1);
            }
            //INC Counter
            i++;
            //Push result onto stack
            push(ret);
        }
        else{
            cout << "Invaild Expression." << endl;
            break;
        }
    }
    //Return answer
    return pop();
}

int main(){
    string expr = "4 12 3 + * 2 / 5 5 + * 100 2 * - 2 /";
    cout << "Expression  : " << expr.c_str() << endl;
    cout << "Answer      : " << reverse_notation(expr) << endl;
    return 0;
}