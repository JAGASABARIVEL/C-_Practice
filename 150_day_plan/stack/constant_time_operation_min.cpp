#include "iostream"
#include <vector>

using namespace std;

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

class MinStack {
public:
    /*
    [
        [-1, -4]
        [-4, -4]
        [0, 0],
        [1, 1],

    ]
    */
    vector<vector<int>> stack;
    MinStack() {
        
    }
    
    void push(int val) {
        int min_val = getMin() > val ? val : getMin();
        if (!stack.size()) {
            stack.push_back({val, val});
            return;
        }
        stack.push_back({val, min_val});
    }
    
    void pop() {
        stack.pop_back();
    }
    
    int top() {
        return !stack.size() ? -1 : stack.back()[0];
    }
    
    int getMin() {
        return !stack.size() ? -1 : stack.back()[1];
    }
};

int main() {
    MinStack * obj = new MinStack();
    obj->push(1);
    obj->push(0);
    obj->push(-4);
    obj->push(-1);
    cout << obj->getMin() << endl;

    return 0;
}
