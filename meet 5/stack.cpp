#include <iostream>
using namespace std;

#define MAX 5

class Stack {
private:
    int arr[MAX];
    int top;

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX - 1;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow\n";
        } else {
            arr[++top] = x;
            cout << x << " ditambahkan ke stack\n";
        }
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
        } else {
            cout << arr[top--] << " dihapus dari stack\n";
        }
    }

    void peek() {
        if (isEmpty()) {
            cout << "Stack kosong\n";
        } else {
            cout << "Elemen teratas: " << arr[top] << endl;
        }
    }
};

int main() {
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    s.peek();

    s.pop();
    s.peek();

    return 0;
}