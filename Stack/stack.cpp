#include "iostream"

using namespace std;

class Stack {
    private:
        static constexpr int STACK_SIZE = 10;
        int top;
        int arr[STACK_SIZE];
    
    public:
        Stack() {
            top = -1;
            for (int index=0; index < STACK_SIZE; index++) {
                arr[index] = 0;
            }
        }
        bool isFull();
        bool isEmpty();
        void push(int);
        int pop();
        void display();
};



bool Stack::isEmpty() {
    return (top == -1);
}

bool Stack::isFull() {
    return (top == STACK_SIZE - 1);
}

void Stack::push(int number) {
    if (isFull()) {
        cout << "Stack is full" << endl;
    }
    else {
        top += 1;
        arr[top] = number;
    }
}

int Stack::pop() {
    if (isEmpty()) {
        cout << "Stack is empty" << endl;
        return 0;
    }
    int temp = arr[top];
    top -= 1;
    arr[top] = 0;
    return temp;
}

void Stack::display() {
    for (int index=0; index < STACK_SIZE; index++) {
        cout << arr[index] << endl;
    }
}

int main() {
    Stack s1;
    s1.display();
    return 0;
}
