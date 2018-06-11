#include <iostream>

using namespace std;

class Stack{
public:
    char *base;
    char *top;
    char data[100];
}OpStack, NumStack;

bool IsOp(char);
bool IsNum(char);

int main() {
    char c[100];
    int i = 0;
    OpStack.base = OpStack.top = OpStack.data;
    NumStack.base = NumStack.top = NumStack.data;
    cin >> c[0];
    while(c[i] != '='){
        if(IsOp(c[i])){
            
        }
        else if(IsNum(c[i])){
            
        }
        else{
            cout << "ERROR" << endl;
            return 0;
        }
        cin >> c[++i];
    }
    return 0;
}

bool IsOp(char c){
    if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')'))
        return true;
    return false;
}

bool IsNum(char c){
    if (c >= '0' && c <= '9')
        return true;
    return false;
}
