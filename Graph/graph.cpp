#include "iostream"
#include <list>
#include <vector>
#include <iterator>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class Edge {
    public:
        int destination;
        int distance;

        Edge(): destination(0), distance(0) { }

        Edge(int destination, int distance) {
            this->destination = destination;
            this->distance = distance;
        }
};

class Vertex {
    public:
        int id;
        string name;
        list<Edge> edges;

        Vertex(): id(0), name("") { }

        Vertex(int id, string name) {
            this->id = id;
            this->name = name;
        }
};

class Graph {
    public:
        vector<Vertex> vertices;

        

        void addVertex(Vertex vertex) {
            for (auto present_vertex = vertices.begin(); present_vertex != vertices.end(); present_vertex++) {
                if (present_vertex->id == vertex.id) {
                    return;
                }
            }
            vertices.push_back(vertex);
        }

        bool isEdgesAlreadyAdded(vector<Vertex>::iterator vertex, int from_node, int to_node) {
            auto edges=vertex->edges;
            for (auto edge = edges.begin(); edge != edges.end(); edge++) {
                if (edge->destination == to_node || edge ->destination == from_node) {
                    return true;
                }
            }
            return false;
        }

        void addEdge(Vertex from_vertex, Vertex to_vertex, int distance) {
            int from_node = from_vertex.id, to_node = to_vertex.id;
            for (auto vertex = vertices.begin(); vertex != vertices.end(); vertex++) {
                if (!isEdgesAlreadyAdded(vertex, from_node, to_node)) {
                    if (vertex->id == from_node) {
                        vertex->edges.push_back(Edge(to_node, distance));
                    }
                    else if (vertex->id == to_node) {
                        vertex->edges.push_back(Edge(from_node, distance));
                    }
                }
            }
        }

        void displayGraph() {
            for (auto vertex = vertices.begin(); vertex != vertices.end(); vertex++) {
                cout << vertex->id << " -> [";
                auto edges=vertex->edges;
                for (auto edge = edges.begin(); edge != edges.end(); edge++) {
                    cout << edge->destination << ",";
                }
                cout << "]" << endl;
            }
        }

        void dijkstra(int start_id) {
            // Distance map to store shortest distance from start to each vertex
            unordered_map<int, int> distances;
            for (auto& vertex : vertices) {
                distances[vertex.id] = numeric_limits<int>::max(); // Set to infinity
            }
            distances[start_id] = 0;

            // Priority queue to select the vertex with the smallest distance
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            pq.push({0, start_id});

            while (!pq.empty()) {
                int current_distance = pq.top().first;
                int current_id = pq.top().second;
                pq.pop();

                // Get the current vertex by ID
                auto current_vertex = find_if(vertices.begin(), vertices.end(),
                    [current_id](const Vertex& v) { return v.id == current_id; });
                if (current_vertex == vertices.end()) continue;

                // Traverse all adjacent edges
                for (const auto& edge : current_vertex->edges) {
                    int new_distance = current_distance + edge.distance;
                    if (new_distance < distances[edge.destination]) {
                        distances[edge.destination] = new_distance;
                        pq.push({new_distance, edge.destination});
                    }
                }
            }

            // Display shortest distances
            cout << "Shortest distances from vertex " << start_id << ":\n";
            for (const auto& [vertex_id, distance] : distances) {
                cout << "Vertex " << vertex_id << " -> Distance: " << (distance == numeric_limits<int>::max() ? -1 : distance) << endl;
            }
        }
};

int main() {

    /**
     * V1 = Yercaud
     * V2 = Salem
     * V3 = Dharmapuri
     * v4 = Harur
     * 
     * [V3]------(25)------[V1]------(40)------- [V2]
     *                      |
     *                      |
     *                     (50)
     *                      |
     *                      |
     *                     [V4]
     * **/

    Graph g;
    Vertex v1(1, "Yercaud"), v2(2, "Salem"), v3(3, "Dharmapuri"), v4(4, "Harur");
    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addVertex(v4);

    g.addEdge(v1, v2, 40);
    g.addEdge(v1, v3, 25);
    g.addEdge(v1, v4, 50);


    g.displayGraph();
    g.dijkstra(3);

    return 0;
}