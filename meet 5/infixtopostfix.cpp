#include <iostream>
#include <stack>
#include <string>

using namespace std;

int prioritas(char op) {
    if (op == '^') {
        return 3;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    }
    return -1; 
}

int main() {
    stack<char> s;
    string infix = "A+B*C";
    string postfix = "";

    for(int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            postfix += c;
        } else {
            while(!s.empty() && prioritas(s.top()) >= prioritas(c)) {
                postfix += s.top();
                s.pop();            
            }
            s.push(c);
        }
    }

    while(!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    cout << "Infix   : " << infix << endl;
    cout << "Postfix : " << postfix << endl;

    return 0;
}