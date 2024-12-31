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
    if (rear == QUEUE_SIZE -1) {                     // Condition would change to "(rear + 1) % QUEUE_SIZE == front" for circular queue
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
        rear = rear + 1;      // It would change to "rear = (rear + 1) % QUEUE_SIZE;"" for curcular queue
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
        front = front + 1;     // It would change to "(front + 1) % QUEUE_SIZE" for circular queue.
    }
    return temp;
}

int main() {
    cout << "Simple Queue" << endl;
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
    q1.enqueue(6);
    cout << q1.dequeue() << endl;
    return 0;
}