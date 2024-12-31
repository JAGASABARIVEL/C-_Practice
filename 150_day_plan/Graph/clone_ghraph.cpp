#include "iostream"
#include<vector>
#include<unordered_map>
#include <queue>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

void bfs(Node * node, unordered_map<int, Node*> & node_map) {
    queue<Node *> q;
    if (node_map.find(node->val) == node_map.end()) {
        node_map[node->val] = node;
        q.push(node);
    }

    while (!q.empty()) {
        Node * temp = q.front();
        q.pop();
        vector<Node *> neighbors = temp->neighbors;

        for (auto neighbor : neighbors) {
            if (node_map.find(neighbor->val) == node_map.end()) {
                node_map[neighbor->val] = neighbor;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    Node n1(1), n2(2), n3(3), n4(4);
    n1.neighbors = {&n2, &n4};
    n2.neighbors = {&n1, &n3};
    n3.neighbors = {&n2, &n4};
    n4.neighbors = {&n1, &n3};
    Node * node = &n1;

    if (node == 0) {
        return nullptr;
    }

    if (!node->neighbors.size()) {
        return new Node(node->val);
    }

    unordered_map<int, Node*> node_map, new_node_map;
    bfs(node, node_map);

    for (auto map : node_map) {
        Node * new_node = new Node(map.first);
        new_node_map[map.first] = new_node;
    }

    for (auto map : node_map) {
        vector<Node *> neighbors;
        for (auto neighbor : map.second->neighbors) {
            neighbors.push_back(new_node_map[neighbor->val]);
        }
        new_node_map[map.first]->neighbors = neighbors;
    }

    bfs(new_node_map[1], node_map);

    

    return 0;
}