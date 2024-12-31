/*
Key words: 
    front,
    rear,
    isFull() = rear + 1 % sizeof(QUEUE_SIZE) == front
    isEmpty() = front == rear == -1
*/

#include "iostream"

using namespace std;

#define QUEUE_SIZE 5

class Queue {
    private:
        int front, rear, queue[QUEUE_SIZE];
    public:
        Queue();
        void enqueue(int number);
        int dequeue();
        bool isEmpty();
        bool isFull();
};

Queue::Queue() {
    front = rear = -1;
    for (int queue_index=0; queue_index < QUEUE_SIZE; queue_index++) {
        queue[queue_index] = 0;
    }
}

bool Queue::isEmpty() {
    if (rear == -1 && front == -1) {
        return true;
    }
    return false;
}

bool Queue::isFull() {
    if (((rear + 1) % QUEUE_SIZE) == front) {                 // Condition would change for simple queue
        return true;
    }
    return false;
}

void Queue::enqueue(int number) {
    if (isEmpty()) {
        rear = front = 0;
        queue[rear] = number;
    }
    else if (isFull()) {
        cout << "Queue is full for number" << number << endl;
    }
    else {
        rear = (rear + 1) % QUEUE_SIZE;
        queue[rear] = number;
    }
}

int Queue::dequeue() {
    int temp;
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return -1;
    }
    else if (front == rear) {
        temp = queue[front];
        front = rear = -1;
    }
    else{
        temp = queue[front];
        front = (front + 1) % QUEUE_SIZE;
    }
    return temp;
}

int main() {
    Queue q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(4);
    q1.enqueue(5);
    q1.enqueue(6);
    cout << q1.dequeue() << endl;
    q1.enqueue(6);
    cout << q1.dequeue() << endl;
    cout << q1.dequeue() << endl;
    cout << q1.dequeue() << endl;
    cout << q1.dequeue() << endl;
    cout << q1.dequeue() << endl;
    cout << q1.dequeue() << endl;
    return 0;
}